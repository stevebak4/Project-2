#ifndef USER_INPUT_HANDLING_H
#define USER_INPUT_HANDLING_H


#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <cassert>
#include <vector>
#include <string>
#include <list> 
#include <fstream>
#include "btree_node.h"
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

/* Function for user input for LSH */
void lsh_user_input(int argc, char* argv[], char** input_file, char** query_file, int* k, int* L, char** output_file, int* number_of_nearest, int* radius);

/* Function for user input for Hypercube */
void hypercube_user_input(int argc, char* argv[], char** input_file, char** query_file, int* k, long int* M, int*probes, char** output_file, int* number_of_nearest, int* radius);

/* Function for user input for cluster */
void cluster_user_input(int argc, char* argv[], char** input_file, char** configuration_file, char** output_file, bool* complete, char** lsh_or_hypercube_method);

void parse_configuration_file(char* configuration_file, int* number_of_clusters, int* number_of_vector_hash_tables, int* number_of_vector_hash_functions, int* max_number_M_hypercube, int* number_of_hypercube_dimensions, int* number_of_probes);

void print_clustering_output(vector<vector<Info_node>> clusters,ofstream &out_file,bool complete,bool silhouette_on_off,int data_dimension,double e,string metric_name,double(*metric)(vector<double>,vector<double>,int));

#endif