
#include "main_algorithms.h"
#include "clustering.h"
#include "hash_tables.h"
#include <chrono>
#include <climits>
#include <unistd.h>
#include "file_handling.h"
#include "frechet_metric_functions.h"
#include "math_functions.h"

using namespace std::chrono;

void LSH_FRECHET(char* input_file,char* query_file,char* output_file,string &method ,int k, int L,int number_of_nearest,double radius,double delta,int data_dimension,bool discrete_or_continuous,bool fill_curve){

    
    vector<int> r;
    vector<vector<double>> t;
    vector<vector<double>> t_frechet;

    vector<vector<vector<double>>> v;
    vector<map<int, int>> pairs;
    vector<vector<Bucket_node>> one_hash_table;
    vector<vector<vector<Bucket_node>>> L_hash_tables;
    vector<vector<Bucket_node>> hypercube;
    srand(time(NULL));
    
    
    ifstream p_file;
    ifstream q_file;
    ofstream out_file(output_file);


    open_file(input_file, p_file);
    open_file(query_file, q_file);
    long unsigned int d_without = data_dimension_without_id(p_file);


    //double w = create_w_for_hash_functions(p_file);
    // cout << "w= " << w << endl;

    int w= 600;
    cout<<"w = " << w << endl;
    
    fill_t_for_hash_tables((double)w,k,L,t);
    fill_t_for_hash_tables(delta,data_dimension,L,t_frechet);

    if(data_dimension == 2)
        fill_v_for_hash_tables(d_without*2,k,L, v);
    else if(data_dimension == 1)
        fill_v_for_hash_tables(d_without,k,L, v);

    fill_r_for_g_hash_functions(k, r);
    

    
    int n = number_of_file_lines(p_file);
    int TableSize = n/4;
    if (TableSize == 0)
        TableSize = 1;

    double e;
    if (discrete_or_continuous == 1)
        e = 0.05;
    else 
        e = 1.2;    
    
    cout<<"n = "<<n<<endl;

    
    if (method.compare("Frechet") ==0)
        lsh_frechet_fill_L_hash_tables(L_hash_tables, p_file, k, v, t, r,t_frechet, w, L,TableSize,delta,data_dimension,e,discrete_or_continuous,fill_curve);
    else exit(-1);

    print_L_hash_tables(L_hash_tables);

    vector<string> q_ids;
    vector<vector<double>> q_vector = make_query_vector(q_file,q_ids,fill_curve);
    

    cout<<"Testing\n\n\n"<<endl;
    cout<<"LSH_FRECHET"<<endl;
    vector<string> search_method;

    string search_method1 = "BF_KNN";
    string search_method2 = "A_KNN";
    string search_method3 = "Range_Search";

    static long long unsigned int count = 0;
    long int M = LONG_MAX/3;
    cout<<"count = "<<count<<"M = "<<M<<endl;
    //cout<<"N =   "<<number_of_nearest<<endl;

    cout<<"TableSize = "<<TableSize<<endl;

    cout<<"delta = "<<delta<<endl;
    cout<<"k = "<<k<<endl;
    cout<<"L = "<<L<<endl;
    cout<<"fill_curve = "<<fill_curve<<endl;
    cout<<"radius = "<<radius<<endl;
    cout<<"data_dimension = "<<data_dimension<<endl;
    cout<<"number_of_nearest = "<<number_of_nearest<<endl;
    cout<<"method = "<<method<<endl;
    cout<<"discrete_or_continuous = "<<discrete_or_continuous<<endl;

    double tApproximateAverage;
    double tTrueAverage;
    double af = 0.0;
    double dist1;
    double dist2;
    double MAF = 0.0;

    
    for (int i=0; i<q_vector.size(); i++){
        
            auto start = high_resolution_clock::now();

            vector<Info_node> best_BF_KNN =  (return_k_best_LSH_Frechet(L_hash_tables,q_vector[i],v,t,r,t_frechet,w,k,TableSize,number_of_nearest,radius,search_method1,M,count,data_dimension,delta,discrete_or_continuous,frechet_distance));
            cout<<"--------------------------------\n";
            for(int j = 0; j <best_BF_KNN.size(); j++){
                best_BF_KNN[j].print();
            }
            auto stop = high_resolution_clock::now();
            auto duration_BF_KNN = duration_cast<seconds>(stop - start);
    
            start = high_resolution_clock::now();

            vector<Info_node> best_A_KNN (return_k_best_LSH_Frechet(L_hash_tables,q_vector[i],v,t,r,t_frechet,w,k,TableSize,number_of_nearest,radius,search_method2,M,count,data_dimension,delta,discrete_or_continuous,frechet_distance));
            
            stop = high_resolution_clock::now();
            auto duration_A_KNN = duration_cast<seconds>(stop - start);


            //vector<Info_node> best_Range_Search (return_k_best_LSH_Frechet(L_hash_tables,q_vector[i],v,t,r,t_frechet,w,k,TableSize,number_of_nearest,radius,search_method3,M,count,data_dimension,delta,discrete_or_continuous,frechet_distance));

            cout<<best_BF_KNN.size()<< endl;
            cout<<best_A_KNN.size()<< endl;
            //cout<<best_Range_Search.size()<< endl;

            cout<<"Finished algos"<< endl;
            cout<<"Making output"<< endl;
            for (unsigned int x = 0;x <best_BF_KNN.size(); x++){

                out_file<<"\nQuery: "<<q_ids[i]<<endl;
                if (discrete_or_continuous == 0)
                    out_file<<"Algorithm: LSH_Frechet_Discrete"<<endl;
                else if(discrete_or_continuous == 1)
                    out_file<<"Algorithm: LSH_Frechet_Continuous"<<endl;

                if (best_A_KNN.size() > 0){
                    out_file<<"Approximate Nearest neighbor-"<<x<<": "<<best_A_KNN[x].get_itemID() <<endl;
                    out_file<<"True Nearest neighbor-"<<x<<": "<<best_BF_KNN[x].get_itemID() <<endl;
                    out_file<<"distanceApproximate: "<<best_A_KNN[x].get_distance()<<endl;
                    out_file<<"distanceTrue: "<<best_BF_KNN[x].get_distance()<<endl;
                dist2 = best_BF_KNN[x].get_distance();
                dist1 = best_A_KNN[x].get_distance();
                }else {
                    dist1 = 0;
                    dist2 = best_BF_KNN[x].get_distance();
                    out_file<<"Approximate Nearest neighbor-"<<x<<": Not found" <<endl;
                    out_file<<"True Nearest neighbor-"<<x<<": "<<best_BF_KNN[x].get_itemID() <<endl;
                    out_file<<"distanceApproximate: --"<<endl;
                    out_file<<"distanceTrue: "<<best_BF_KNN[x].get_distance()<<endl;

                }  
               
                
                af = dist1/dist2;
                if (af > MAF)
                    MAF = af;

            }
          


            tApproximateAverage +=duration_A_KNN.count();
            tTrueAverage += duration_BF_KNN.count();

           
        
    }

    tApproximateAverage = tApproximateAverage/q_vector.size();
    tTrueAverage = tTrueAverage/q_vector.size();

    out_file<<"\n\n"<<endl;  
    out_file<<"tApproximateAverage: "<<tApproximateAverage<<endl;
    out_file<<"tTrueAverage: "<<tTrueAverage<<endl;
    out_file<<"MAF: "<<MAF<<" [Maximum Approximation Factor]"<<endl;



    close_file(out_file);
    close_file(p_file);
    close_file(q_file);
   

}



void LSH(char* input_file,char* query_file,char* output_file,string &method ,int k, int L,int number_of_nearest,double radius){

    
    vector<int> r;
    vector<vector<double>> t;
    vector<vector<double>> t_frechet;

    vector<vector<vector<double>>> v;
    vector<map<int, int>> pairs;
    vector<vector<Bucket_node>> one_hash_table;
    vector<vector<vector<Bucket_node>>> L_hash_tables;
    vector<vector<Bucket_node>> hypercube;
    srand(time(NULL));
    
    ifstream p_file;
    ifstream q_file;
    ofstream out_file(output_file);


    open_file(input_file, p_file);
    open_file(query_file, q_file);
    long unsigned int d_without = data_dimension_without_id(p_file);


  
    cout <<"inside discrite\n"<<endl;
    double w = 650;
    fill_t_for_hash_tables((double)w,k,L,t);


    fill_v_for_hash_tables(d_without,k,L, v);
    fill_r_for_g_hash_functions(k, r);
    

    
    int n = number_of_file_lines(p_file);
    int TableSize = n/4;
    if (TableSize == 0)
        TableSize = 1;

    double e = 1;
    
    cout<<"n = "<<n<<endl;
    cout<<"TableSize = "<<TableSize<<endl;

    
    if (method.compare("LSH") ==0)
        fill_L_hash_tables(L_hash_tables, p_file, k, v, t, r, w, L,TableSize);

    print_L_hash_tables(L_hash_tables);
    
    vector<string> q_ids;
    bool fill_curve = 0;

    vector<vector<double>> q_vector = make_query_vector(q_file,q_ids,fill_curve);
    
    
    cout<<"Testing\n\n\n"<<endl;
    vector<string> search_method;

    string search_method1 = "BF_KNN";
    string search_method2 = "A_KNN";
    string search_method3 = "Range_Search";

    static long long unsigned int count = 0;
    long int M = LONG_MAX/3;
    cout<<"count = "<<count<<"M = "<<M<<endl;
    

    double tApproximateAverage;
    double tTrueAverage;
    double af = 0.0;
    double dist1;
    double dist2;
    double MAF = 0.0;

    for (int i=0; i<q_vector.size(); i++){
        
            auto start = high_resolution_clock::now();

            vector<Info_node> best_BF_KNN =  BF_KNN(L_hash_tables[0],q_vector[i],number_of_nearest, M,count,1,euclidean_distance_2) ;
            cout<<"--------------------------------\n";
           
            auto stop = high_resolution_clock::now();
            auto duration_BF_KNN = duration_cast<seconds>(stop - start);
    
            start = high_resolution_clock::now();

            vector<Info_node> best_A_KNN (return_k_best_LSH(L_hash_tables,q_vector[i],v,t,r,w,k,TableSize,number_of_nearest,radius,search_method2,M,count,-1,euclidean_distance_2));
            
            stop = high_resolution_clock::now();
            auto duration_A_KNN = duration_cast<seconds>(stop - start);


            //vector<Info_node> best_Range_Search (return_k_best_LSH(L_hash_tables,q_vector[i],v,t,r,w,k,TableSize,number_of_nearest,radius,search_method3,M,count,-1,euclidean_distance_2));

            cout<<best_BF_KNN.size()<< endl;
            cout<<best_A_KNN.size()<< endl;
            //cout<<best_Range_Search.size()<< endl;

            cout<<"Finished algos"<< endl;
            cout<<"Making output"<< endl;
            for (unsigned int x = 0;x <best_BF_KNN.size(); x++){

                out_file<<"\nQuery: "<<q_ids[i]<<endl;
                out_file<<"Algorithm: LSH_VECTOR"<<endl;
                if (best_A_KNN.size() > 0){
                    out_file<<"Approximate Nearest neighbor-"<<x<<": "<<best_A_KNN[x].get_itemID() <<endl;
                    out_file<<"True Nearest neighbor-"<<x<<": "<<best_BF_KNN[x].get_itemID() <<endl;
                    out_file<<"distanceApproximate: "<<best_A_KNN[x].get_distance()<<endl;
                    out_file<<"distanceTrue: "<<best_BF_KNN[x].get_distance()<<endl;
                dist2 = best_BF_KNN[x].get_distance();
                dist1 = best_A_KNN[x].get_distance();
                }else {
                    dist1 = 0;
                    dist2 = best_BF_KNN[x].get_distance();
                    out_file<<"Approximate Nearest neighbor-"<<x<<": Not found" <<endl;
                    out_file<<"True Nearest neighbor-"<<x<<": "<<best_BF_KNN[x].get_itemID() <<endl;
                    out_file<<"distanceApproximate: --"<<endl;
                    out_file<<"distanceTrue: "<<best_BF_KNN[x].get_distance()<<endl;

                }  
               
                
                af = dist1/dist2;
                if (af > MAF)
                    MAF = af;

            }
         


            tApproximateAverage +=duration_A_KNN.count();
            tTrueAverage += duration_BF_KNN.count();

           
        
    }

    tApproximateAverage = tApproximateAverage/q_vector.size();
    tTrueAverage = tTrueAverage/q_vector.size();

    out_file<<"\n\n"<<endl;  
    out_file<<"tApproximateAverage: "<<tApproximateAverage<<endl;
    out_file<<"tTrueAverage: "<<tTrueAverage<<endl;
    out_file<<"MAF: "<<MAF<<" [Maximum Approximation Factor]"<<endl;



    close_file(out_file);
    close_file(p_file);
    close_file(q_file);
  

}




void HYPERCUBE(char* input_file,char* query_file,char* output_file,string &method ,int k,int number_of_nearest,double radius,int probes){

    
    vector<int> r;
    vector<vector<double>> t;
    vector<vector<double>> t_frechet;

    vector<vector<vector<double>>> v;
    vector<map<int, int>> pairs;
    vector<vector<Bucket_node>> one_hash_table;
    vector<vector<vector<Bucket_node>>> L_hash_tables;
    vector<vector<Bucket_node>> hypercube;
    srand(time(NULL));
    
    ifstream p_file;
    ifstream q_file;
    ofstream out_file(output_file);


    open_file(input_file, p_file);
    open_file(query_file, q_file);
    long unsigned int d_without = data_dimension_without_id(p_file);
    int L = 1;


   
    cout <<"inside Hypercube\n"<<endl;
    double w = 650;
    fill_t_for_hash_tables((double)w,k,L,t);


    fill_v_for_hash_tables(d_without,k,L, v);
    fill_r_for_g_hash_functions(k, r);
    

    
    int n = number_of_file_lines(p_file);
    int TableSize = n/4;
    if (TableSize == 0)
        TableSize = 1;

    double e = 1;
    
    cout<<"n = "<<n<<endl;
    cout<<"TableSize = "<<TableSize<<endl;

    
    if (method.compare("Hypercube") ==0)
        fill_hypercube(p_file, hypercube, pairs, v[0], t[0], w, k);

    
    vector<string> q_ids;
    bool fill_curve = 0;

    vector<vector<double>> q_vector = make_query_vector(q_file,q_ids,fill_curve);
   

    cout<<"Testing\n\n\n"<<endl;
    vector<string> search_method;

    string search_method1 = "BF_KNN";
    string search_method2 = "A_KNN";
    string search_method3 = "Range_Search";

    static long long unsigned int count = 0;
    long int M = LONG_MAX/3;
    cout<<"count = "<<count<<"M = "<<M<<endl;
   
    double tApproximateAverage;
    double tTrueAverage;
    double af = 0.0;
    double dist1;
    double dist2;
    double MAF = 0.0;

    for (int i=0; i<q_vector.size(); i++){
        
            auto start = high_resolution_clock::now();

            vector<Info_node> best_BF_KNN =  BF_KNN(hypercube,q_vector[i],number_of_nearest, M,count,-1,euclidean_distance_2) ;
            cout<<"--------------------------------\n";
            for(int j = 0; j <best_BF_KNN.size(); j++){
                best_BF_KNN[j].print();
            }
            auto stop = high_resolution_clock::now();
            auto duration_BF_KNN = duration_cast<seconds>(stop - start);
    
            start = high_resolution_clock::now();

            vector<Info_node> best_A_KNN (return_k_best_hypercube(hypercube,q_vector[i],v[0],t[0],r,w,pairs,k,probes,number_of_nearest,radius,search_method2,M,count,-1,euclidean_distance_2));
            
            stop = high_resolution_clock::now();
            auto duration_A_KNN = duration_cast<seconds>(stop - start);


            //vector<Info_node> best_Range_Search (return_k_best_hypercube(hypercube,q_vector[i],v[0],t[0],r,w,pairs,k,probes,number_of_nearest,radius,search_method3,M,count,-1,euclidean_distance_2));

            cout<<best_BF_KNN.size()<< endl;
            cout<<best_A_KNN.size()<< endl;
            //cout<<best_Range_Search.size()<< endl;

            cout<<"Finished algos"<< endl;
            cout<<"Making output"<< endl;
            for (unsigned int x = 0;x <best_BF_KNN.size(); x++){

                out_file<<"Query: "<<q_ids[i]<<endl;
                out_file<<"Algorithm: Hypercube"<<endl;

                if (best_A_KNN.size() > 0){
                    out_file<<"Approximate Nearest neighbor-"<<x<<": "<<best_A_KNN[x].get_itemID() <<endl;
                    out_file<<"True Nearest neighbor-"<<x<<": "<<best_BF_KNN[x].get_itemID() <<endl;
                    out_file<<"distanceApproximate: "<<best_A_KNN[x].get_distance()<<endl;
                    out_file<<"distanceTrue: "<<best_BF_KNN[x].get_distance()<<endl;
                dist2 = best_BF_KNN[x].get_distance();
                dist1 = best_A_KNN[x].get_distance();
                }else {
                    dist1 = 0;
                    dist2 = best_BF_KNN[x].get_distance();
                    out_file<<"Approximate Nearest neighbor-"<<x<<": Not found" <<endl;
                    out_file<<"True Nearest neighbor-"<<x<<": "<<best_BF_KNN[x].get_itemID() <<endl;
                    out_file<<"distanceApproximate: --"<<endl;
                    out_file<<"distanceTrue: "<<best_BF_KNN[x].get_distance()<<endl;

                }  
               
                
                af = dist1/dist2;
                if (af > MAF)
                    MAF = af;

            }
          


            tApproximateAverage +=duration_A_KNN.count();
            tTrueAverage += duration_BF_KNN.count();

         
    }

    tApproximateAverage = tApproximateAverage/q_vector.size();
    tTrueAverage = tTrueAverage/q_vector.size();

    out_file<<"\n\n"<<endl;  
    out_file<<"tApproximateAverage: "<<tApproximateAverage<<endl;
    out_file<<"tTrueAverage: "<<tTrueAverage<<endl;
    out_file<<"MAF: "<<MAF<<" [Maximum Approximation Factor]"<<endl;



    close_file(out_file);
    close_file(p_file);
    close_file(q_file);
   




}


















void CLUSTERING_LSH(char* input_file,char* output_file,char *configuration_file,char *mean_frechet_or_vector,char *classic_LSH_or_hypercube,bool complete,bool silhouette_on_off){


    int number_of_clusters;
    int number_of_vector_hash_tables;
    int number_of_vector_hash_functions;
    int max_number_M_hypercube; 
    int number_of_hypercube_dimensions; 
    int number_of_probes;
    
    int k;
    int L;
    long int M;
    int number_of_nearest;
    double radius = 10000.0;
    double delta = 1;
    int data_dimension;
    bool discrete_or_continuous;
    bool fill_curve;

    vector<int> r;
    vector<vector<double>> t;
    vector<vector<double>> t_frechet;

    vector<vector<vector<double>>> v;
    vector<map<int, int>> pairs;
    vector<vector<Bucket_node>> one_hash_table;
    vector<vector<vector<Bucket_node>>> L_hash_tables;
    vector<vector<Bucket_node>> hypercube;
    srand(time(NULL));

    ifstream p_file;
    ifstream q_file;
    ofstream out_file;

    vector<vector<Info_node>> matrix;


    

    parse_configuration_file(configuration_file, &number_of_clusters, &number_of_vector_hash_tables, &number_of_vector_hash_functions, &max_number_M_hypercube, &number_of_hypercube_dimensions, &number_of_probes); 
    // cout << number_of_vector_hash_functions << endl;

    L = number_of_vector_hash_tables;
    k = number_of_vector_hash_functions;
    M = LONG_MAX/3;

    open_file(input_file, p_file);
    open_file(output_file, out_file);
    

    
    long unsigned int d = data_dimension_with_id(p_file);
    cout << "d = " << d << endl;

    long unsigned int d_without = data_dimension_without_id(p_file);
    cout << "d_without = " << d_without << endl;
    int w;
    /* testing create_w_for_hash_functions function */
    //w = create_w_for_hash_functions(p_file);
    // cout << "w= " << w << endl;
    w = 650;

    if (strcmp(mean_frechet_or_vector,"Mean Frechet") == 0 )
        data_dimension = 2;
    else 
        data_dimension = 1;

    if(strcmp("Hypercube",classic_LSH_or_hypercube) == 0){
        k = number_of_hypercube_dimensions;
    }

    fill_t_for_hash_tables((double)w,k,L,t);
    fill_t_for_hash_tables(delta,data_dimension,L,t_frechet);

    if (data_dimension == 2)
        fill_v_for_hash_tables(2*d_without,k,L, v);
    else if(data_dimension == 1)    
        fill_v_for_hash_tables(d_without,k,L, v);

    fill_r_for_g_hash_functions(k, r);
    

    
    int n = number_of_file_lines(p_file);
    int TableSize = n/4;
    if (TableSize == 0 )
        TableSize = 1;

    double e = 1.2;    
    cout<<"n = "<<n<<endl;
    cout<<"TableSize = "<<TableSize<<endl;

    int reps = 3;

    static long long unsigned int count = 0;

    cout<<"number_of_clusters = "<<number_of_clusters<<endl;
    cout<<"number_of_vector_hash_tables = "<<number_of_vector_hash_tables<<endl;
    cout<<"max_number_M_hypercube = "<<max_number_M_hypercube<<endl;
    cout<<"number_of_hypercube_dimensions = "<<number_of_hypercube_dimensions<<endl;
    cout<<"number_of_clusters = "<<number_of_clusters<<endl;
    cout<<"number_of_probes = "<<number_of_probes<<endl;
    cout<<"mean_frechet_or_vector = "<<mean_frechet_or_vector<<endl;
    cout<<"classic_LSH_or_hypercube = "<<classic_LSH_or_hypercube<<endl;
    cout<<"complete = "<<complete<<endl;
    cout<<"silhouette_on_off = "<<silhouette_on_off<<endl;
    cout<<"delta = "<<delta<<endl;
    cout<<"k = "<<k<<endl;
    cout<<"L = "<<L<<endl;
    cout<<"fill_curve = "<<fill_curve<<endl;
    cout<<"radius = "<<radius<<endl;
    cout<<"data_dimension = "<<data_dimension<<endl;

    


    if( strcmp("LSH",classic_LSH_or_hypercube) == 0){

        count = 0;
        M = LONG_MAX/3;   
        cout<<"M = "<<M << endl;
        cout <<"inside LSH "<<endl;

       
        data_dimension = 1;
        discrete_or_continuous = 0;

        fill_L_hash_tables(L_hash_tables, p_file, k, v, t, r, w, L,TableSize);

        vector<Bucket_node>  k_centers_for_reverse_approach = Initialize_k_centers_bucket(L_hash_tables[0],number_of_clusters);
        string method = "LSH";

        vector<vector<Info_node>> matrix = Reverse_Approach_LSH(L_hash_tables,k_centers_for_reverse_approach,v,t,r,t_frechet,w,k,TableSize,radius,reps,number_of_probes,method,M,count,data_dimension,delta,e,discrete_or_continuous,euclidean_distance_2);

        out_file<<"\n\n\n\nAlgorithm: Range Search LSH "<<endl;
        print_clustering_output(matrix,out_file,complete,silhouette_on_off,data_dimension,e,"-",euclidean_distance_2);

    


    }else if( strcmp("Classic",classic_LSH_or_hypercube) == 0){

        if (strcmp(mean_frechet_or_vector,"Mean Frechet") == 0 ){
            count = 0;
            M = LONG_MAX/3; 
            fill_curve = 1;
            data_dimension = 2;
            discrete_or_continuous = 0;
            cout<<"\n\n\nisnide classic Loyd"<<endl;
           
            reps = 2;

            lsh_frechet_fill_L_hash_tables(L_hash_tables, p_file, k, v, t, r,t_frechet, w, L,TableSize,delta,data_dimension,e,discrete_or_continuous,fill_curve);

            print_L_hash_tables(L_hash_tables);

            cout<<"\n\nFinished Loyd \n\n";

            vector<Bucket_node>  k_centers_for_loyd = Initialize_k_centers_bucket(L_hash_tables[0],number_of_clusters);
            matrix = Exact_Loyd(L_hash_tables[0],k_centers_for_loyd,reps,data_dimension,e,"LSH_Frechet",frechet_distance);
            
            print_final_matrix(matrix);
            out_file<<"Algorithm Lloyds "<<endl;
            print_clustering_output(matrix,out_file,complete,silhouette_on_off,data_dimension,e,"Frechet",frechet_distance);

        }else{

            count = 0;
            M = LONG_MAX/3; 
            fill_curve = 0;
            data_dimension = -1;
            discrete_or_continuous = 0;
            cout<<"\n\n\nisnide classic loiyd"<<endl;

            fill_L_hash_tables(L_hash_tables, p_file, k, v, t, r, w, L,TableSize);

            print_L_hash_tables(L_hash_tables);

            cout<<"\n\nFinished Loyd \n\n";

            vector<Bucket_node>  k_centers_for_loyd = Initialize_k_centers_bucket(L_hash_tables[0],number_of_clusters);
            matrix = Exact_Loyd(L_hash_tables[0],k_centers_for_loyd,reps,data_dimension,e,"Classic",euclidean_distance_2);
            
            print_final_matrix(matrix);
            out_file<<"Algorithm Lloyds "<<endl;
            print_clustering_output(matrix,out_file,complete,silhouette_on_off,data_dimension,e,"Classic",euclidean_distance_2);






        }

    }else if( strcmp("LSH_Frechet",classic_LSH_or_hypercube) == 0){

        count = 0;
        M = LONG_MAX/3;   
        cout<<"M = "<<M << endl;
        data_dimension = 2;
        fill_curve = 1;
        discrete_or_continuous = 0;
        reps = 2;
       
        cout<<"inside LSH_Frechet"<<endl;
       

       lsh_frechet_fill_L_hash_tables(L_hash_tables, p_file, k, v, t, r,t_frechet, w, L,TableSize,delta,data_dimension,e,discrete_or_continuous,fill_curve);

        print_L_hash_tables(L_hash_tables);

       

        vector<Bucket_node>  k_centers_for_reverse_approach = Initialize_k_centers_bucket(L_hash_tables[0],number_of_clusters);
        string method = "LSH_Frechet";

        matrix = Reverse_Approach_LSH(L_hash_tables,k_centers_for_reverse_approach,v,t,r,t_frechet,w,k,TableSize,radius,reps,number_of_probes,method,M,count,data_dimension,delta,e,discrete_or_continuous,euclidean_distance_2);

        out_file<<"\n\n\n\nAlgorithm: Range Search LSH_Frechet  "<<endl;
        print_clustering_output(matrix,out_file,complete,silhouette_on_off,data_dimension,e,"Frechet",frechet_distance);


    }else if( strcmp("Hypercube",classic_LSH_or_hypercube) == 0){

        count = 0;
        reps = 3;
        M = max_number_M_hypercube;   
        cout<<"M = "<<M << endl;
        data_dimension = -1;
        L=1;
      
        discrete_or_continuous = 0;
        k = number_of_hypercube_dimensions;
        
        fill_hypercube(p_file, hypercube, pairs, v[0], t[0], w, number_of_hypercube_dimensions);

        cout<<"\nbefore loyd"<<endl;

        vector<vector<vector<Bucket_node>>> hypercube_first;
        hypercube_first.push_back(hypercube);

        
        print_L_hash_tables(hypercube_first);
        //sleep(3);

        vector<Bucket_node>  k_centers_for_reverse_approach = Initialize_k_centers_bucket(hypercube_first[0],number_of_clusters);
        string method = "Hypercube";

        matrix = Reverse_Approach_LSH(hypercube_first,k_centers_for_reverse_approach,v,t,r,t_frechet,w,number_of_hypercube_dimensions,TableSize,radius,reps,number_of_probes,method,M,count,data_dimension,delta,e,discrete_or_continuous,euclidean_distance_2);

        out_file<<"\n\n\n\nAlgorithm: Range Search LSH_Frechet  "<<endl;
        print_clustering_output(matrix,out_file,complete,silhouette_on_off,data_dimension,e,"-",euclidean_distance_2);

    


    }

        close_file(out_file);


}