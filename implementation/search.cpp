#include "grid_functions.h"
#include "user_input_functions.h"
#include "user_input_handling2.h"
#include "clustering.h"
#include "lsh_frechet.h"
#include <unistd.h>
#include "main_algorithms.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    char* input_file = NULL ;
    char* query_file = NULL;
    int k = -1;
    int L;
    long int M;
    int probes;
    char* output_file = NULL;
    char* LSH_Hypercube_or_Frechet = NULL;
    char* discrete_or_continuous = NULL; 
    double delta;
    int data_dimension = 1;
    int TableSize;
    int number_of_nearest = 1;
    double radius = 10000;

    vector<int> r;
    vector<vector<double>> t;
    vector<vector<vector<double>>> v;
    vector<map<int, int>> pairs;
    vector<vector<Bucket_node>> one_hash_table;
    vector<vector<vector<Bucket_node>>> L_hash_tables;
    vector<vector<Bucket_node>> hypercube;
    srand(time(NULL));




    ifstream p_file;
    ifstream q_file;
    ofstream out_file;

    search_input(argc, argv, &input_file, &query_file, &k, &L, &M, &probes, &output_file, &LSH_Hypercube_or_Frechet, &discrete_or_continuous, &delta);

    // if input file has not been given already, ask user to give it
    if (input_file == NULL){
        ask_user_for_dataset_file_path(p_file);
    }


    // if query file and output file have not been given already, ask user to give them
    if (query_file == NULL || output_file == NULL){
        ask_user_for_query_and_output_file_path(q_file, &output_file);
        ofstream out_file(output_file);
    }


    // if algorithm has not been given already, ask user to give it

    if (LSH_Hypercube_or_Frechet == NULL)
        LSH_Hypercube_or_Frechet = ask_user_for_algorithm(&LSH_Hypercube_or_Frechet);
    if (!strcmp(LSH_Hypercube_or_Frechet, "LSH")){
        cout << "im:   " << *LSH_Hypercube_or_Frechet << endl;
        if (k == -1){
            k = 4;
        }

        string method = "LSH";
        LSH(input_file,query_file,output_file,method ,k,L,number_of_nearest,radius);

    }
    if (!strcmp(LSH_Hypercube_or_Frechet, "Hypercube")){
        cout << "im:   " << *LSH_Hypercube_or_Frechet << endl;
        if (k == -1){
            k = 14;
        }

        string method = "Hypercube";
        HYPERCUBE(input_file,query_file,output_file,method ,k,number_of_nearest,radius,probes);

    }
    if (!strcmp(LSH_Hypercube_or_Frechet, "Frechet")){
        cout<<"inside Frechet"<<endl;
        cout << "im:   " << *LSH_Hypercube_or_Frechet << endl;
        if (k == -1){
            k = 4;
        }
        if(discrete_or_continuous == NULL)
          ask_user_for_metric(&discrete_or_continuous);
        
        if (strcmp(discrete_or_continuous, "continuous") == 0){
            
            int data_dimension = 1;
            bool discrete_or_continuous = 1;
            bool fill_curve = 0;
            cout<<"delta continuous = "<<delta<< endl;
            //sleep(5);
            string method ="Frechet";
            LSH_FRECHET(input_file, query_file, output_file,method,k,L, number_of_nearest,radius,delta,data_dimension,discrete_or_continuous,fill_curve);

        }else if (strcmp(discrete_or_continuous, "discrete") == 0){
          
            int data_dimension = 2;
            bool discrete_or_continuous = 0;
            bool fill_curve = 1;
            cout<<"delta discrete= "<<delta<< endl;
            //sleep(5);
            
            string method ="Frechet";
            LSH_FRECHET(input_file, query_file, output_file,method,k,L, number_of_nearest,radius,delta,data_dimension,discrete_or_continuous,fill_curve);
            
            return 0;            


        }  
    }
      

    delete[] query_file;
    delete[] output_file;
    delete[] input_file;
    delete[] LSH_Hypercube_or_Frechet;
    delete[] discrete_or_continuous; 
    
    return 0;
}









