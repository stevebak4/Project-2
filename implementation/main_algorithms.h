
#ifndef MAIN_ALGORITHMS_H
#define MAIN_ALGORITHMS_H

#include "bucket_node.h"
#include "lsh_frechet.h"




void LSH(char* input_file,char* query_file,char* output_file,string &method ,int k, int L,int number_of_nearest,double radius);

void HYPERCUBE(char* input_file,char* query_file,char* output_file,string &method ,int k,int number_of_nearest,double radius,int probes);

void LSH_FRECHET(char* input_file,char* query_file,char* output_file,string &method, int k, int L,int number_of_nearest,double radius,double delta,int data_dimension,bool discrete_or_continuous,bool fill_curve);

void CLUSTERING_LSH(char* input_file,char* output_file,char *configuration_file,char *mean_frechet_or_vector,char *classic_LSH_or_hypercube,bool complete,bool silhouette_on_off);

#endif