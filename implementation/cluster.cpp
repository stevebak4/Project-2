#include "user_input_handling2.h"
#include "main_algorithms.h"

using namespace std;

int main(int argc, char *argv[]) {
    char* input_file = NULL;
    char* configuration_file = NULL;
    char* output_file = NULL;
    char* mean_frechet_or_vector = NULL;
    char* classic_LSH_or_hypercube = NULL;
    bool complete;
    bool silhouette_on_off;
    // config
    int number_of_clusters;
    int number_of_vector_hash_tables;
    int number_of_vector_hash_functions;
    int max_number_M_hypercube; 
    int number_of_hypercube_dimensions; 
    int number_of_probes;

    cluster_input(argc, argv, &input_file, &configuration_file, &output_file, &mean_frechet_or_vector, &classic_LSH_or_hypercube, &complete, &silhouette_on_off);



    
        
    CLUSTERING_LSH(input_file,output_file,configuration_file,mean_frechet_or_vector,classic_LSH_or_hypercube,complete,silhouette_on_off);
    

    delete[] output_file;
    delete[] input_file;
    delete[] mean_frechet_or_vector;
    delete[] configuration_file; 
    delete[] classic_LSH_or_hypercube; 




    return 0;
}