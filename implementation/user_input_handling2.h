#ifndef USER_INPUT_HANDLING_2_H
#define USER_INPUT_HANDLING_2_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <cassert>
#include <vector>
#include <string>
#include <list> 
#include <fstream>
#include <stdlib.h>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

/* Function for user input for search */
void search_input(int argc, char* argv[], char** input_file, char** query_file, int* k, int* L, long int* M, int* probes, char** output_file, char** LSH_Hypercube_or_Frechet, char** discrete_or_continuous, double* delta);

/* Function for user input for cluster */
void cluster_input(int argc, char* argv[], char** input_file, char** configuration_file, char** output_file, char** mean_frechet_or_vector, char** classic_LSH_or_hypercube, bool* complete, bool* silhouette);

#endif