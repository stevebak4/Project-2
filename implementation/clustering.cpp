
#include <cfloat>
#include <cstddef>
#include <limits.h>
#include <algorithm>
#include <unistd.h>

#include "grid_functions.h"
#include "k_means_node.h"
#include "lsh_frechet.h"
#include "mean_curves.h"


Bucket_node& choose_randomly_uniform_centroid(vector<vector<Bucket_node>> &struct1,int val){

    int bucket,bucket_node;
    int random1, random2;
	random_device generator;
	uniform_int_distribution<int> distribution (0,val);
	
    while (1){
        
        random1 = distribution(generator); /* Generate a new int */
        random2 = distribution(generator); /* Generate a new int */

        bucket = random1 % struct1.size();
        if (struct1[bucket].size()!=0 ){
            bucket_node = random2 % struct1[bucket].size();
            break;
        }
    }

    return struct1[bucket][bucket_node];


}

struct find_p : std::unary_function<Bucket_node, bool> {
    vector<double> p;
    find_p(vector<double> p):p(p) { }
    
    bool operator()(Bucket_node & m) const {
        //m.print();
        return m.get_p() == p;
    }
};



double min_distance_to_centroid(vector<double> &point,const vector<Bucket_node> &centroids){

    double min_dist = DBL_MAX;
    double dist;

    for(int i = 0; i < centroids.size(); i++){
        
        dist = euclidean_distance_2(centroids[i].get_p(),point);

       if (dist < min_dist)
            min_dist = dist;
    }
    //cout<<"returning min distance "<<min_dist<<endl;
    return min_dist;
}


/*function to compare distances in std::sort() */
struct less_than_key
{
    inline bool operator() (const Info_node& struct1, const Info_node& struct2)
    {
        return (struct1.get_distance() < struct2.get_distance());
    }
};

Bucket_node* return_second_nearest_centroid(vector<double> &point,const vector<Bucket_node> &centroids,int data_dimension,double(*metric)(vector<double>,vector<double>,int)){

    double min_dist = DBL_MAX;
    double dist;
    Bucket_node *c = NULL;
    double second_best = 0;
    vector<double> distances;
    int best_i = -1;
    int second_best_i;
    vector<Info_node> info_nodes;

    for(int i = 0; i < centroids.size(); i++){
        
        dist = metric(centroids[i].get_p(),point,data_dimension);
        info_nodes.push_back(Info_node(centroids[i].get_p(),dist,centroids[i].get_itemID()));
    }

    sort(info_nodes.begin(), info_nodes.end(), less_than_key());

    vector<double> second_best_point = info_nodes[1].get_p();

    for (int i = 0; i < centroids.size(); i++){
        
        vector<double> p =  centroids[i].get_p();

        if (second_best_point == p){
            c = new Bucket_node(centroids[i]);
            break;

        }
    }

    cout<<"\nreturning second nearest cenntroid "<<endl;
    return c;
}


Bucket_node* return_nearest_centroid(vector<double> &point,const vector<Bucket_node> &centroids,int data_dimension,double(*metric)(vector<double>,vector<double>,int)){

    double min_dist = DBL_MAX;
    double dist;
    Bucket_node *c = NULL;

    cout<<"Returning nearest centroid"<<endl;
    for(int i = 0; i < centroids.size(); i++){
        
        dist = metric(centroids[i].get_p(),point,data_dimension);

       if (dist < min_dist){
            min_dist = dist;
            if (c != NULL){
                delete c;
            }
            c = new Bucket_node(centroids[i]);


       }
    }
    //cout<<"returning min distance "<<min_dist<<endl;
    return c;
}



void print_vector(vector<double> vec){
    for(int i = 0; i < vec.size(); i++)
        cout<<vec[i] <<" "<<endl;
}

bool search_centroids(vector<Bucket_node> centroids,vector<double> point){

    for(int i = 0; i < centroids.size(); i++){
        if (centroids[i].get_p() == point )
            return true;
    }

    return false;
}


bool compareByProb(const k_means_node &a, const k_means_node &b)
{
    return a.prob < b.prob;
}



vector<Bucket_node>  Initialize_k_centers_bucket(vector<vector<Bucket_node>> &struct1,int N){

    vector<Bucket_node> centroids;
    vector<double> point;
    double sum_of_Di_s = 0.0;
    int index_i,index_j;
    double max_prob = 0.0;
    double max_D = 0.0;
    vector<k_means_node> vec;
    

    //Randomly choose first centroid
    cout<<"Initializing Centroids"<<endl;
    centroids.push_back( choose_randomly_uniform_centroid(struct1,INT_MAX));

    
    //Choose N-1 remaining centroids
    for (int k = 1; k < N; k++){
        
       
        for (int i = 0; i < struct1.size(); i++){
            for (int j = 0; j < struct1[i].size(); j++){

         
    
                /*if current point is not a centroid */
                
                k_means_node node( &(struct1[i][j]),0.0,0.0);

                if (search_centroids(centroids,struct1[i][j].get_p()) == false){
                    
                    point = struct1[i][j].get_p();    
                    node.D = min_distance_to_centroid(point, centroids);
                    
                    if (node.D > max_D)
                        max_D = node.D;

                    sum_of_Di_s += node.D;    //watch for overflow here
                    node.prob = sum_of_Di_s;


                    vec.push_back(node);

                }
   
            }

        }

        /*Calculate exact probability of each point*/
        max_prob = 0;
        //cout <<"Sum of D's = "<<sum_of_Di_s<<endl;

        for (int i = 0; i < vec.size(); i++){
            
                vec[i].prob = vec[i].prob/max_D;
            
        }

        /*sort the vectors*/
        std::sort(vec.begin(), vec.end(), compareByProb);

        double prob = create_t_for_hash_function(vec[vec.size()-1].prob);

        double cumulativeProbability = 0.0;
        for (int i = 0; i< vec.size(); i++) {
            cumulativeProbability += vec[i].prob*vec[i].prob;  //Take D(i)^2
            if (prob <= cumulativeProbability) {
                
                centroids.push_back(*(vec[i].pointer));
                break;
            }
        }

    }

    vec.clear();
    return centroids;
}



int search_centroids_index(vector<Bucket_node> centroids,vector<double> point){


    for(int i = 0; i < centroids.size(); i++){

        vector<double> p = centroids[i].get_p();       
        if ( p == point ){
           return i;
        }   
    }

    return -1;
}


/*Function used for the updade step */
vector<double> calculate_mean_vector(vector<Bucket_node> bucket){

    vector<double> mean_vector;
    int dimension = bucket[0].get_p().size();
    double sum = 0.0;
    

    for(int i = 0; i < dimension; i++){
        sum = 0;
        for (int j = 0 ;j < bucket.size(); j++){

            vector<double> point = bucket[j].get_p();
            sum += point[i];
        }
        mean_vector.push_back(sum/bucket.size());
    }    


    return mean_vector;

}

vector<double> calculate_mean_vector(vector<Info_node> bucket){

    vector<double> mean_vector;
    int dimension = bucket[0].get_p().size();
    double sum = 0.0;

    for(int i = 0; i < dimension; i++){
        sum = 0;
        for (int j = 0 ;j < bucket.size(); j++){

            vector<double> point = bucket[j].get_p();
            sum += point[i];
        }
        mean_vector.push_back(sum/bucket.size());
    }    


    return mean_vector;

}

/*Print the final result */
void print_final_matrix(const vector<vector<Bucket_node>> matrix){

    for(int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
           
           if(j == 0){
               cout<<"\n\n\nCentroid["<<i<<"] :";
           }

           vector<double> point = matrix[i][j].get_p();
            for (int x = 0; x < point.size(); x++){
                cout<<point[x]<<" ";
            }
            
            cout<<"-> ";
           

        }
    }
}

void print_final_matrix(const vector<vector<Info_node>> matrix){

    for(int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
           
           if(j == 0){
               cout<<"\n\n\nCentroid["<<i<<"] :";
           }

           vector<double> point = matrix[i][j].get_p();
            for (int x = 0; x < point.size(); x++){
                cout<<point[x]<<" ";
            }
            
            cout<<"-> ";
           

        }
    }
}

vector<double> silhouette(vector<vector<Info_node>>& clusters,int data_dimension,double e,string metric_name,double(*metric)(vector<double>,vector<double>,int)){
    
    vector<double> silhouette_for_each_cluster;
    double c = 0; // keeps the sum of (b-a)/ min(a,b) of each point
    double sil = 0; // the final silhuette number for the cluster
    double a;
    double b;
    Bucket_node* first_centroid;
    Bucket_node* second_centroid;
    vector<Bucket_node> centroids;

    for (unsigned int i = 0; i < clusters.size(); i++){
        centroids.push_back(Bucket_node(clusters[i][0].get_p(),clusters[i][0].get_distance(),clusters[i][0].get_itemID() ) );
         /*
         if(metric_name.compare("Frechet") == 0 ){
            vector<double> p = centroids[i].get_p();
            centroids[i].set_p( e_filtering(p,data_dimension,e));
        }
        */
    }
    for (unsigned int i=0; i<clusters.size(); i++){ // for every cluster
        c = 0;
        sil = 0;
        for (int j=1; j<clusters[i].size(); j++){ // for every point in cluster
            vector<double> point = clusters[i][j].get_p();
           /*
            if(metric_name.compare("Frechet") == 0 ){
                point = e_filtering(point,data_dimension,e);
            }
            */
            first_centroid = return_nearest_centroid(point, centroids,data_dimension,metric); // get the centroid
            a = metric(point,first_centroid->get_p(),data_dimension); // calculate distance between the point and its centroid
            second_centroid = return_second_nearest_centroid(point, centroids,data_dimension,metric); // get the centroid of the nearest cluster
            b = metric(point,second_centroid->get_p(),data_dimension); // calculate distance between the point and the second nearest centroid
            c = c + ((b-a)/ max(a,b));
            sil =  (double)c / (double)clusters[i].size(); // calculate the number for this cluster
        }
       
        silhouette_for_each_cluster.push_back(sil);
    
    }

    centroids.clear();
    return silhouette_for_each_cluster; // return 
}


/*Return Loyd's method. The first vector of each row corresponds to the centroid */
vector<vector<Info_node>> Exact_Loyd(vector<vector<Bucket_node>> &struct1,vector<Bucket_node> &centroids,int reps,int data_dimension,double e,string method,double(*metric)(vector<double>,vector<double>,int)){



    int number_of_centroids = centroids.size();
    int rep = 0;
    Bucket_node *node = NULL;
    vector<vector<Info_node>> clusters;
    int data_length = centroids[0].get_p().size();

    cout<<"INSIDE EXACT LOYD = "<<rep<<endl;
    
    for(int z = 0; z < reps; z++){
       
        for (int i = 0; i < number_of_centroids; i++){
        
            vector<Info_node> v;
            clusters.push_back(v);
        }

        if(method.compare("LSH_Frechet") == 0){
            
            for (int i = 0; i < number_of_centroids; i++){
                vector<double> p = centroids[i].get_p();
                centroids[i].set_p(e_filtering(p,data_dimension,e));

            }
            for (int i = 0; i < struct1.size(); i++) {
                for(int j = 0; j<struct1[i].size(); j++) {
                    vector<double> p = struct1[i][j].get_p();
                    struct1[i][j].set_p(e_filtering(p,data_dimension,e));

                }
            }            
        }

        for (int i = 0; i < struct1.size(); i++) {
            for(int j = 0; j<struct1[i].size(); j++) {

                if (search_centroids(centroids,struct1[i][j].get_p()) == false){
                        
                        vector<double> point = struct1[i][j].get_p();
                        node = return_nearest_centroid(point,centroids,data_dimension,metric);
                        int index = search_centroids_index(centroids,node->get_p());
                       

                        Info_node bucket(point,-1,struct1[i][j].get_itemID());

                        clusters[index].push_back(bucket);
                        

                }        
            }   

        }
        /*If we are not at the last probe */  
        if (z < reps -1){

            for (int i=0; i<clusters.size(); i++)
                cout <<"clusters["<<i<<"]: = "<<clusters[i].size()<<endl;    

            clustering_update_step(centroids,clusters,data_dimension,data_length,e,method);

            clusters.clear();

            cout<<"Out of rep \n\n"<<endl;

        
        }else{

            /* Push the centroids into the first position of each row of clusters  and return */
            for (int i = 0; i < centroids.size(); i++){
                clusters[i].insert(clusters[i].begin(),Info_node(centroids[i].get_p(),-1,centroids[i].get_itemID() ) );

            }
            return clusters;

        }


    }

    cout<<"================================";
    return clusters;

}

void print_vector_2(vector<vector<bool>> &vec1){

    for (int j = 0; j < vec1.size(); j++){
            
            cout <<"Printing bucket "<<j<<endl;

            for (int k = 0; k < vec1[j].size(); k++){
                
                cout<<vec1[j][k]<<" "<<endl;
            }
    }

}


void print_vector_3(vector<bool> &vec1){
   
            
            cout <<"Printing bv1 "<<endl;

            for (int k = 0; k < vec1.size(); k++){
                
                cout<<vec1[k]<<" "<<endl;
            
    }

}

void initialize_flag_matrix(vector<vector<bool>> &flag_matrix,vector<vector<Bucket_node>> &hashtable ){
        
        for (int j = 0; j < hashtable.size(); j++){
        
            vector<bool> vec2;
            
            for (int k = 0; k < hashtable[j].size(); k++){
                //cout<<"size  = "<<hashtable[j].size()<<endl; 
                char p = 0;
                vec2.push_back(p);
            }
        
            flag_matrix.push_back(vec2);

        }
            
}



void print_flag_matrix(vector<vector<bool>> &flag_matrix){

    for (int i = 0; i < flag_matrix.size(); i++){
        
       cout <<"PRINTINT FOR HASHTABLE "<<i<<"size =  "<<flag_matrix.size()<<endl;
        
        for (int j = 0; j < flag_matrix[i].size(); j++){
            cout<<flag_matrix[i][j]<<" "<<endl;
        }
    }
    
}


bool search_for_unnasigned_flag_matrix(vector<vector<bool>> &flag_matrix){

    for(int i = 0; i < flag_matrix.size(); i++){
        for (int j = 0; j < flag_matrix[i].size(); j++){

            if(flag_matrix[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

bool search_cluster(vector<Info_node> &cluster,vector<double> &p){


    for(int i = 0; i < cluster.size(); i++){
            
        if(cluster[i].get_p() == p)
                return 1;
        
    }
    return 0;

}


vector<Info_node> search_clusters_for_common_points(vector<vector<Info_node> > &clusters){

    vector<Info_node> common_points;
    for (int i = 0; i < clusters.size(); i++) {

        for(int j = 0; j < clusters[i].size(); j++){

            vector<double> p = clusters[i][j].get_p();

            if(search_cluster(clusters[i],p ) == 1){

                common_points.push_back(clusters[i][j]);

            }
        }
    }

    return common_points;
}

void remove_point_from_cluster(std::vector<Info_node> & clusters, vector<double> &point) {
    clusters.erase(
        std::remove_if(clusters.begin(), clusters.end(), [&](Info_node const & cluster) {
            return cluster.get_p() == point;
        }),
        clusters.end());
}


vector<vector<Bucket_node>> return_unassigned_points(vector<vector<Bucket_node> > &hashtable,vector<vector<bool>> &flag_matrix){

    vector<vector<Bucket_node>> unassigned_points;
    for (int i  = 0; i < hashtable.size(); i++){
        vector<Bucket_node> bucket;
        unassigned_points.push_back(bucket);
    }

    for (int i = 0; i < hashtable.size(); i++){
        for (int j = 0; j < hashtable[i].size(); j++){

            if(flag_matrix[i][j] == 0){
                
                unassigned_points[i].push_back(Bucket_node(hashtable[i][j].get_p(),hashtable[i][j].get_ID(),hashtable[i][j].get_itemID()) );

            }
        }

    }

    return unassigned_points;
}

vector<vector<Info_node>> lsh_for_reverse_approach(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<Bucket_node> &centroids,vector<vector<Info_node>> &clusters

,vector<vector<bool>> &flag_matrix,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,int w,int k,int TableSize,double range,int max_iterations,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int)){


    for(int i = 0; i < L_hash_tables.size(); i++){
        for (int j = 0; j < centroids.size(); j++){

            vector<double> q = centroids[j].get_p();

            long long int ID = ID_func(q,v[i],t[i],r,w,k,TableSize);
            long long int hash_result = g_func(ID,  TableSize);

            vector <Info_node> best =  (Range_Search_for_Reverse_Approach(L_hash_tables[i],L_hash_tables[0],q,flag_matrix,range,hash_result,M,count,data_dimension,metric));

            clusters[j] = combine_k_results(best,clusters[j],INT_MAX,0);
        
        }

    }
    return clusters;

}

vector<vector<Info_node>> lsh_frechet_for_reverse_approach(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<Bucket_node> &centroids,vector<vector<Info_node>> &clusters

,vector<vector<bool>> &flag_matrix,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet,int w,int k,int TableSize,double range,int max_iterations,long int M,long long unsigned int &count,int data_dimension,double delta,bool discrete_or_continuous,double(*metric)(vector<double>,vector<double>,int)){


    for(int i = 0; i < L_hash_tables.size(); i++){
        for (int j = 0; j < centroids.size(); j++){

            vector<double> grid_curve;
            vector<double> q = centroids[j].get_p();

              if (discrete_or_continuous == 0){ //carve is discrete
            
                grid_curve = generate_discrete_grids_curve(q,delta,t_frechet[i]);
                remove_consecutive_duplicates(grid_curve,data_dimension);
                
                if (grid_curve.size() < q.size()){
                    grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
                }
        
            
                
                }else if(discrete_or_continuous == 1){
                    cout<<"NOT ABLE FOR THIS PART"<<endl;
                    exit(-1);       //curve is continuous
                }

            long long int ID = ID_func(grid_curve,v[i],t[i],r,w,k,TableSize);
            long long int hash_result = g_func(ID,  TableSize);
            
            vector <Info_node> best =  (Range_Search_for_Reverse_Approach(L_hash_tables[i],L_hash_tables[0],q,flag_matrix,range,hash_result,M,count,data_dimension,metric));

            clusters[j] = combine_k_results(best,clusters[j],INT_MAX,0);
        
        }

    }
    return clusters;

}

vector<vector<Info_node>> hypercube_for_reverse_approach(vector<vector<Bucket_node>> &hypercube,vector<Bucket_node> &centroids,vector<vector<Info_node>> &clusters
,vector<vector<bool>> &flag_matrix,vector<vector<double>>& v, vector<double>& t, vector<int>& r,int w,int new_dimension,int probes,double range,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int)){

  
    for (int i=0;i<centroids.size(); i++){

        vector<double> q = centroids[i].get_p();

        vector<vector<int>> binary_buckets = return_buckets_for_hashing(q,new_dimension,probes,v,t,w, pairs);
       
        for (int j = 0;j <binary_buckets.size(); j++){   

           unsigned int hash_result = binary_int_to_decimal_int(binary_buckets[j]);

           vector<Info_node> best =  (Range_Search_for_Reverse_Approach(hypercube,hypercube,q,flag_matrix,range,hash_result,M,count,data_dimension,metric));
 
           for(int x = 0; x < best.size(); x++) 
                clusters[i].push_back(best[x]);
        }
        binary_buckets.clear();
        
    }
  
    return clusters;
}

/*returns 1 if all clusters are eampty */
bool check_if_all_clusters_are_eampty(vector<vector<Info_node>> &clusters){

    bool flag = 0;
    for(int i = 0; i < clusters.size(); i++){
        if (clusters[i].size() != 0)
            flag = 1;
    }

    if (flag == 1) 
        return 0;

    return 1;

}

long long unsigned int number_of_all_points(vector<vector<Bucket_node>> &hash_table){

    long long unsigned int sum = 0;

    for(int i = 0; i < hash_table.size(); i++){
        sum+= hash_table[i].size();
    }

    return sum;
}


long long unsigned int number_of_assigned_points(vector<vector<Info_node>> &clusters){

    long long unsigned int sum = 0;

    for(int i = 0; i < clusters.size(); i++){
        sum+= clusters[i].size();
    }

    return sum;
}


void clustering_update_step(vector<Bucket_node> &centroids,vector<vector<Info_node>> &clusters,int data_dimension,int data_length,double e,string method){
  
  
    int number_of_centroids = centroids.size();
    for (int i = 0; i < number_of_centroids; i++){  //maybe change with centroids.size()
        
        if (clusters[i].size() != 0){
        
            if(method.compare("LSH_Frechet") == 0){
                
                cout<<"i = "<<i<<endl;
                vector<double> mean_curve = Return_Mean_Curve(clusters[i], data_dimension,data_length,e);

                cout<<"Mean Curve size = "<<mean_curve.size()<<endl;
                //print_vector(mean_curve,mean_curve.size());
                cout<<"clusters["<<i<<"] size = "<<clusters[i].size()<<endl;
                //sleep(2);

                
                if (mean_curve.size() > data_length){
                    mean_curve_filtering(mean_curve,data_length,data_dimension,e);
                   
                }
                
                if (mean_curve.size() < data_length){
                    mean_curve = padding(mean_curve,PADDING_VALUE,data_length);
                   
                }
                centroids[i].set_p(mean_curve);              

            }else{

                cout<<"i = "<<i<<endl;
                vector<double> mean_vector = calculate_mean_vector(clusters[i]);            
               
                centroids[i].set_p(mean_vector);

            }
        }

    }

}


vector<vector<Info_node>> Reverse_Approach_LSH(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<Bucket_node> &centroids,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet,int w,int k,int TableSize,double range,int max_iterations,int probes,string method,long int  M,long long unsigned int &count,int data_dimension,double delta,double e,bool discrete_or_continuous,double(*metric)(vector<double>,vector<double>,int)){

    vector<vector<bool>> flag_matrix;
    double min_dist = DBL_MAX;
    double max_dist_between_initial_centroids = 0;
    int clusters_flag = 0;

    cout<<"\n\nSTARTING CLUSTERING \n\n"<<endl;
    vector<vector<Info_node>> clusters;
    initialize_flag_matrix(flag_matrix,L_hash_tables[0]);

    long long int all_points = number_of_all_points(L_hash_tables[0]);
    long long int assigned_points = 0;

    for (int i = 0; i < centroids.size(); i++  ){
                vector<Info_node> node;
                clusters.push_back(node);
        } 

    
    //find minimum distance between two centroids 
    for (int i = 0; i < centroids.size(); i++){
        
        for (int j = 0; j < centroids.size(); j++){
            
            if (i != j){
                vector<double> p1 = centroids[i].get_p();
                vector<double> p2 = centroids[j].get_p();

                double dist = metric(p1,p2,data_dimension);
                if (dist < min_dist)
                    min_dist = dist;
                if (dist > max_dist_between_initial_centroids)
                    max_dist_between_initial_centroids = dist;    
       
            }
        }
    }

    int data_length = centroids[0].get_p().size();
    int iterations = 0;
    
    //while there are unussignid points
    range = (min_dist/2.0);

    cout <<"range = " << range <<" and centroids size = "<<centroids.size() <<endl;
    cout << "max_distance = " << max_dist_between_initial_centroids <<endl;
    int cycles = 0;
    while(1){


            clusters_flag = 0;
            cout<<"before LSH ITERATIONS L =  "<<L_hash_tables.size()<<" iterations = "<<iterations<<"\n\n"<<endl;
            /* Find Range Search clusters using LSH */

            vector<int> clusters_size;
            for (int i = 0; i < centroids.size(); i++){
                clusters_size.push_back(clusters[i].size());

            }

            if (method.compare("LSH") == 0)
                lsh_for_reverse_approach(L_hash_tables,centroids,clusters,flag_matrix,v,t,r,w,k,TableSize,range,max_iterations,M,count,data_dimension,metric);
            else if (method.compare("Hypercube") == 0)
                hypercube_for_reverse_approach(L_hash_tables[0],centroids,clusters,flag_matrix,v[0],t[0],r,w,k,probes,range,M,count,data_dimension,metric);
            else if (method.compare("LSH_Frechet") == 0)
                lsh_frechet_for_reverse_approach(L_hash_tables,centroids,clusters,flag_matrix,v,t,r,t_frechet,w,k,TableSize,range,max_iterations,M,count,data_dimension,delta,discrete_or_continuous,metric);
            
            /* Check if points are added to any cluster */

            vector<Info_node> common_points = search_clusters_for_common_points(clusters);

            for (int i = 0; i < common_points.size(); i++){
                common_points[i].print();
            }

            /* If a point exists in more than one clusters then assign it to the nearest centroid */
            if (common_points.size() != 0){

                for (int i = 0; i < common_points.size(); i++){
                    
                    Bucket_node *node = NULL;
                    vector<double> point = common_points[i].get_p();
                    node = return_nearest_centroid(point,centroids,data_dimension,metric);
                    int index = search_centroids_index(centroids,node->get_p());
                    
                    for (int j = 0; j < centroids.size(); j++){
                        if ( j != index ){
                            if(search_cluster(clusters[j],point) == 1){
                                remove_point_from_cluster(clusters[j],point );
                            }
                        }
                    }
                }

            common_points.clear();
            }
          
            for (int i = 0; i < clusters.size(); i++){

                for (int j = 0; j < clusters[i].size(); j++){

                    vector<double> p = clusters[i][j].get_p();
                    vector<int> position;
                    position = search_first_hashtable_for_key(L_hash_tables[0],p);
                    int index_i = position[0];
                    int index_j = position[1];   

                    if (flag_matrix[index_i][index_j] == 0 ){
                        
                        flag_matrix[index_i][index_j] = 1;

                    }

                }
            }

        /////////////////////////////////////////////////////////////////////////////////////////
            assigned_points = number_of_assigned_points(clusters);
            double frac = ((double)assigned_points/(double)all_points);

           

            for (int i = 0; i < centroids.size(); i++){
                 
                 if (frac < 0.7){
                     clusters_flag = 1;
                     break;
                 }
                    

                if(clusters[i].size() > clusters_size[i]){
                        clusters_flag = 1;
                }
            }
            if (check_if_all_clusters_are_eampty(clusters) == 1){
                clusters_flag = 1;        
            }

            if (range > 10*max_dist_between_initial_centroids){
                clusters_flag = 0;
            }        
            clusters_size.clear();


        /////////////////////////////////////////////////////////////////////////////////////    
            

            /*double range an each iteration */
            range = range*2.0;
            //update centroids  step
            if(clusters_flag == 0){

                cout<<"iterations "<<iterations<<endl;
                for (int i=0; i<clusters.size(); i++)
                    cout <<"clusters["<<i<<"]: = "<<clusters[i].size()<<endl;    


            ////////////////////////////////////////////////////////////////////////////////////////////
                /*finishing*/
                if (iterations == max_iterations){

                    cout<<"clusters flag = 0\n"<<endl;
                    vector<vector<Bucket_node>> unassigned_points = return_unassigned_points(L_hash_tables[0],flag_matrix);
                                       
                    vector<vector<Info_node>> loyds_clusters = Exact_Loyd(unassigned_points,centroids,1,data_dimension,e,method,metric);

                    for (int i=0; i<loyds_clusters.size(); i++)
                        cout <<"loyds["<<i<<"]: = "<<loyds_clusters[i].size()<<endl;
                    
                    for (int i=0; i<clusters.size(); i++)
                        cout <<"clusters["<<i<<"]: = "<<clusters[i].size()<<endl;    

                    for (int i=0;i<loyds_clusters.size(); i++){
                        for (int j = 0; j < loyds_clusters[i].size(); j++){

                            /*the first object os the centroid */    
                            if(j > 0){
                                clusters[i].push_back(Info_node(loyds_clusters[i][j].get_p(),-1,loyds_clusters[i][j].get_itemID()));
                            }
                        }
                    }
                    
                    for (int i = 0; i < centroids.size(); i++){
                        
                        clusters[i].insert(clusters[i].begin(),Info_node(centroids[i].get_p(),-1,centroids[i].get_itemID()));
                    }
                    unassigned_points.clear();
                    centroids.clear();
                    flag_matrix.clear();
                    
                    cout<<"M = "<<M<<"count = "<<count<<endl;
                    return clusters;
                    
                }
            
            //////////////////////////////////////////////////////////////////////////////////////////////    
              
        
                clustering_update_step(centroids,clusters,data_dimension,data_length,e,method);
                range = (min_dist/2.0);
                //reinitialize flag_matrix
                flag_matrix.clear();
                cout <<"clearing clusters"<<endl;
                clusters.clear();
                /*Reinitialize clusters */
                for (int i = 0; i < centroids.size(); i++  ){
                    vector<Info_node> node;
                    clusters.push_back(node);
                } 
                initialize_flag_matrix(flag_matrix,L_hash_tables[0]);
                iterations++;

                //update range

            }

            

    }


    cout << "ERROR RETURNING "<<endl;
    return  clusters;

}