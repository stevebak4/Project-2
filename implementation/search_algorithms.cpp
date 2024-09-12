
#include "grid_functions.h"
#include "math_functions.h"
#include "f_functions.h"
#include <cfloat>
#include <unistd.h>
#include "grid_functions.h"
#include "lsh_frechet.h"
#include "hash_functions_h.h"




/*function to compare distances in std::sort() */
struct less_than_key
{
    inline bool operator() (const Info_node& struct1, const Info_node& struct2)
    {
        return (struct1.get_distance() < struct2.get_distance());
    }
};

vector<Info_node> A_KNN(vector<vector<Bucket_node>> &hashtable,vector<double> q,int id,int N,int hash_result,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) ) {

    long unsigned int dimension = q.size();
   
    double kth_dist = DBL_MAX;
    double dist;
    vector<Info_node> info;
    
    if (dimension == 0)
        return info;

    cout<<"into A_KNN "<<endl;

    for(int j = 0; j < hashtable[hash_result].size(); j++){
        //cout<<"J =  "<<j<<endl;
        if(hashtable[hash_result][j].get_ID() == id ){    
            cout<<" id = "<<id<<endl;
            cout<<" hash_result = "<<hash_result<<endl;

            
            
            count++;
            if (count > M){
                cout<<"returned count = "<<count<<endl;
                return info;

            }    
            
            vector<double> p = hashtable[hash_result][j].get_p();
            string item_id = hashtable[hash_result][j].get_itemID();

            if (q != p){

                if (  ((dist = metric(q,p,data_dimension) ) < kth_dist ) || info.size() < N ){   //change with metric
                    cout<<"dist = "<<dist<<" kth_dist = "<<kth_dist<<endl;

                    kth_dist = dist;
                    //Info_node node(p,dist); 
                    info.push_back(Info_node(p,dist,item_id));     
                    sort(info.begin(), info.end(), less_than_key());
                    if (info.size() > N)
                        info.pop_back();
                    
                }
            }

        }

    }
    cout<<"returned A_KNN"<<endl;
    return info;
    
}


vector<Info_node> BF_KNN(vector<vector<Bucket_node>> &hashtable,vector<double> &q,int N,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) ) {

   
    long unsigned int dimension = q.size();
   
    double kth_dist = DBL_MAX;
    double dist;
    vector<Info_node> info;
    
    if (dimension == 0)
        return info;


    cout<<"into BF_KNN  = "<<endl;
    
    for(int i=0;i<hashtable.size();i++) {
       
        for(int j = 0; j < hashtable[i].size(); j++){
            cout<<"J =  "<<j<<endl;  

        
        count++;
        if (count > M){
            cout<<"returned count = "<<count<<endl;
            return info;

        }    
        
        vector<double> p = hashtable[i][j].get_p();
        string item_id = hashtable[i][j].get_itemID();
    
            if (q != p){
            
                if (  ((dist = metric(q,p,data_dimension) ) < kth_dist ) || info.size() < N ){   //change with metric
                    cout<<" dist = "<<dist<<" kth_dist = "<<kth_dist<<endl;
                    kth_dist = dist;
                    //Info_node node(p,dist); 
                    info.push_back(Info_node(p,dist,item_id));     
                    sort(info.begin(), info.end(), less_than_key());
                    if (info.size() > N)
                        info.pop_back();
                    
                }
            }

        }
    }

    return info;    
}


vector<Info_node> Range_Search(vector<vector<Bucket_node>> &hashtable,vector<double> q,double range,int N,int hash_result,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) ) {

    long unsigned int dimension = q.size();
   
    double kth_dist = DBL_MAX;
    double dist;
    vector<Info_node> info;
    if (dimension == 0)
        return info;

    cout<<"into Range Search"<<endl;

    for(int j = 0; j < hashtable[hash_result].size(); j++){
        //cout<<"J =  "<<j<<endl;
        
        count++;
        if (count > M)
            return info;

        

        vector<double> p = hashtable[hash_result][j].get_p();
        string item_id = hashtable[hash_result][j].get_itemID();

        if (q != p){

            if (  ((dist = metric(q,p,data_dimension) ) < range ) && info.size() < N ){   //change with metric
                
                info.push_back(Info_node(hashtable[hash_result][j].get_p(),dist,item_id));     
                sort(info.begin(), info.end(), less_than_key());
                if (info.size() > N)
                    info.pop_back();
                
            }

        }

    }

    return info;    
}


vector<int> search_first_hashtable_for_key(vector<vector<Bucket_node>> hashtable,vector<double> &p){

    vector<int> result;

    for(int i=0;i<hashtable.size();i++){

        for(int j=0;j< hashtable[i].size();j++){

            if (hashtable[i][j].get_p() == p ){

                result.push_back(i);
                result.push_back(j);
                return result;
                 
            }
        }
    }

    return result;

}

vector<Info_node> Range_Search_for_Reverse_Approach(vector<vector<Bucket_node>> &hashtable,vector<vector<Bucket_node>> &first_hash_table,vector<double> &q,vector <vector<bool>> &flag_matrix,double range,int hash_result,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) ) {

    long unsigned int dimension = q.size();
   
    double kth_dist = DBL_MAX;
    double dist;
    vector<Info_node> info;
    if (dimension == 0)
        return info;

    cout<<"into Range_Search_for_Reverse_Approach"<<endl;

    for(int j = 0; j < hashtable[hash_result].size(); j++){
        //cout<<"J =  "<<j<<endl;
        
        count++;
        if (count > M)
            return info;

        //cout<<"M = "<<M<<" count = "<<count<<endl;
    
        vector<int> position;
        vector<double> p = hashtable[hash_result][j].get_p();
        string item_id = hashtable[hash_result][j].get_itemID();


        if (q != p){
            

            position = search_first_hashtable_for_key(first_hash_table,p);
            int index_i = position[0];
            int index_j = position[1]; 

            if (flag_matrix[index_i][index_j] == 0){

                if (  ((dist = metric(q,hashtable[hash_result][j].get_p(),data_dimension) ) < range ) ){   //change with metric                    

                        info.push_back(Info_node(hashtable[hash_result][j].get_p(),dist,item_id));                             
                    
                }
            }
        }
    }

    return info;    
}



/* clear duplicates and return  put the points of best into best_k if best[i].distance < best_k.distance*/
vector<Info_node> combine_k_results(vector<Info_node>  best,vector<Info_node> best_k,int N,int sort_flag){

       int flag = 0;

        cout<<"into combine_k_results"<<endl;
        cout <<"best size = "<<best.size()<<"and best_k size = "<<best_k.size()<<endl;
       
        if (best_k.size() != 0){

                for(int j = 0; j < best.size(); j++){
                    
                    flag = 0;
                    for (int x = 0;x < best_k.size(); x++){
                        
                        if(best[j].get_p() == best_k[x].get_p() ){

                             //cout<<"equal vectors"<<endl;

                            flag = 1;
                            if(best[j].get_distance() < best_k[x].get_distance() ){
                                
                                best_k.erase(best_k.begin()+x);
                                //cout<<"element erased "<<best[j].get_distance()<<endl;
                                best_k.push_back(Info_node(best[j]) );  
                                if(sort_flag ==1)
                                    sort(best_k.begin(), best_k.end(), less_than_key());
            
                              break;
                            }
                        }          
                    }

                     if (flag == 0){

                        for (int x = 0;x < best_k.size(); x++){

                                    
                                    best_k.push_back(Info_node(best[j]) );  
                                    if(sort_flag ==1)
                                        sort(best_k.begin(), best_k.end(), less_than_key());
                                    
                                    if (best_k.size() > N)
                                        best_k.pop_back();
                
                                    flag = 0;
                                    break;
                            
                        }

                    }
                }
               
                best.clear();
           
           
            }else if(best.size() != 0){
                //cout << "else2"<<endl;
                for(int j = 0; j < best.size(); j++){

                    best_k.push_back(Info_node(best[j]) );  
                    if(sort_flag ==1)
                        sort(best_k.begin(), best_k.end(), less_than_key());
                    
                    if (best_k.size() > N)
                        best_k.pop_back();
                
                    }
                    best.clear();
            }

        //cout <<"ending combine"<<endl;    
        return best_k;

}

/*return k nearest neighbors from all hashtables using method as a function */
vector<Info_node> return_k_best_LSH(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<double>& q,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,int w,int k,int TableSize,int N,double range,string &search_method,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int)){


    vector<Info_node> best_k;


    if (search_method.compare("A_KNN") == 0){

        for(int i = 0; i < L_hash_tables.size(); i++){

            long long int ID = ID_func(q,v[i],t[i],r,w,k,TableSize);
            long long int hash_result = g_func(ID,  TableSize);

            vector<Info_node> best =  (A_KNN(L_hash_tables[i],q,ID,N,hash_result,M,count,data_dimension,metric));
            
            best_k = combine_k_results(best,best_k,N,1);
           
        }
    }else if (search_method.compare("BF_KNN") == 0){

        
            vector<Info_node> best =  (BF_KNN(L_hash_tables[0],q,N,M,count,data_dimension,metric));
            
            return best;               
        
    }else if (search_method.compare("Range_Search") == 0){
       
        for(int i = 0; i < L_hash_tables.size(); i++){

            long long int ID = ID_func(q,v[i],t[i],r,w,k,TableSize);
            long long int hash_result = g_func(ID,  TableSize);

            vector<Info_node> best =  (Range_Search(L_hash_tables[i],q,range,N,hash_result,M,count,data_dimension,metric));
            
            best_k = combine_k_results(best,best_k,N,1);
           
        }
    }



    return best_k;    
}

/*return k nearest neighbors from all hashtables using method as a function */
vector<Info_node> return_k_best_LSH_Frechet(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<double>& q,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet,int w,int k,int TableSize,int N,double range,string &search_method,long int M,long long unsigned int &count,int data_dimension,double delta,bool discrete_or_continuous,double(*metric)(vector<double>,vector<double>,int)){


    vector<Info_node> best_k;
    vector<double> grid_curve;
    double e = 1;

    if (search_method.compare("A_KNN") == 0){
        //cout << "here"<<endl;
        for(int i = 0; i < L_hash_tables.size(); i++){
        
            if (discrete_or_continuous == 0){ //carve is discrete
            
                grid_curve = generate_discrete_grids_curve(q,delta,t_frechet[i]);
                remove_consecutive_duplicates(grid_curve,data_dimension);
                
                if (grid_curve.size() < q.size()){
                    grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
                }
        
            
            }
            else if(discrete_or_continuous == 1){       //curve is continuous
                
                grid_curve = e_filtering(q,data_dimension,e);
                grid_curve = generate_continuous_grids_curve(grid_curve,delta,t_frechet[i]);
                grid_curve = min_max_filtering(grid_curve,data_dimension);
            
                //cout<<"grid size = "<<grid_curve.size()<<endl;
                //cout <<" q size = "<<q.size()<<endl;
                if (grid_curve.size() < q.size()){
                    //cout<<"doint padding"<<endl;
                
                    grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
                }
           
            }
            long long int ID = ID_func(grid_curve,v[i],t[i],r,w,k,TableSize);
            long long int hash_result = g_func(ID,  TableSize);
            vector<Info_node> best =  (A_KNN(L_hash_tables[i],q,ID,N,hash_result,M,count,data_dimension,metric));
            
            best_k = combine_k_results(best,best_k,N,1);
            grid_curve.clear();
            
            
           
        }
    }else if (search_method.compare("BF_KNN") == 0){
          
        if (discrete_or_continuous == 0){ //carve is discrete
        
            grid_curve = generate_discrete_grids_curve(q,delta,t_frechet[0]);
            remove_consecutive_duplicates(grid_curve,data_dimension);
            
            if (grid_curve.size() < q.size()){
                grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
            }
    
        
        }
        else if(discrete_or_continuous == 1){       //curve is continuous
            
            grid_curve = e_filtering(q,data_dimension,e);
            grid_curve = generate_continuous_grids_curve(grid_curve,delta,t_frechet[0]);
            grid_curve = min_max_filtering(grid_curve,data_dimension);
        

            if (grid_curve.size() < q.size()){
                grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
            }
        
        }
    

        vector<Info_node> best =  (BF_KNN(L_hash_tables[0],q,N,M,count,data_dimension,metric));
        return best;
                       
    }else if (search_method.compare("Range_Search") == 0){
        
        for(int i = 0; i < L_hash_tables.size(); i++){
            
           
            if (discrete_or_continuous == 0){ //carve is discrete
            
                grid_curve = generate_discrete_grids_curve(q,delta,t_frechet[i]);
                remove_consecutive_duplicates(grid_curve,data_dimension);
                
                if (grid_curve.size() < q.size()){
                    grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
                }
        
            
            }
            else if(discrete_or_continuous == 1){       //curve is continuous
                
                grid_curve = e_filtering(q,data_dimension,e);
                grid_curve = generate_continuous_grids_curve(grid_curve,delta,t_frechet[i]);
                grid_curve = min_max_filtering(grid_curve,data_dimension);
            

                if (grid_curve.size() < q.size()){
                    grid_curve = padding(grid_curve,PADDING_VALUE,q.size());
                }
           
            }

            long long int ID = ID_func(grid_curve,v[i],t[i],r,w,k,TableSize);
            long long int hash_result = g_func(ID,  TableSize);

            vector<Info_node> best =  (Range_Search(L_hash_tables[i],q,range,N,hash_result,M,count,data_dimension,metric));
            
            best_k = combine_k_results(best,best_k,N,1);
           
        }
    }



    return best_k;    
}



vector<Info_node> return_k_best_hypercube(vector<vector<Bucket_node>> hypercube,vector<double>& q,vector<vector<double>>& v, vector<double>& t, vector<int>& r,int w,vector<map<int, int>>& pairs,int new_dimension,int probes,int N,double range,string &search_method,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int)){

    vector<Info_node> best_k;

    vector<vector<int>> binary_buckets = return_buckets_for_hashing(q,new_dimension,probes,v,t,w, pairs);

    //cout<<"number of binary buckets = "<<binary_buckets.size()<<endl;
    if (search_method.compare("A_KNN") == 0){

        for (int i=0;i<binary_buckets.size(); i++){
            
            long long unsigned int hash_result = binary_int_to_decimal_int(binary_buckets[i]);
            if (hash_result > hypercube.size() || hash_result < 0){
                cout <<"ERROR hash result = "<<hash_result<<endl;
                exit(-5);
            }
            vector<Info_node> best =  (A_KNN(hypercube,q,0,N,hash_result,M,count,data_dimension,metric));
            
            best_k = combine_k_results(best,best_k,N,1);    
        }
        

    }else if (search_method.compare("BF_KNN") == 0){

            
            vector<Info_node> best =  (BF_KNN(hypercube,q,N,M,count,data_dimension,metric));
            
            return best;
        

    }else if (search_method.compare("Range_Search") == 0){

        for (int i=0;i<binary_buckets.size(); i++){
            
            long long unsigned int hash_result = binary_int_to_decimal_int(binary_buckets[i]);

            vector<Info_node> best =  (Range_Search(hypercube,q,range,N,hash_result,M,count,data_dimension,metric));
            
            best_k = combine_k_results(best,best_k,N,1);    

        }

    }
    return best_k;

}