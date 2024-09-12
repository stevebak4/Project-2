#ifndef HASH_FUNCTIONS_H_H_
#define HASH_FUNCTIONS_H_H_


#include "search_algorithms.h"


/* This function computes and returns the mean distance of p data using brute force */
double mean_distance_brute_force(ifstream& inputFileStream);

/* This function creates the v of the h formula */
vector<double> create_v_for_hash_function(long unsigned int dimension);

/* This function creates k v's and fills v vector */
vector<vector<double>> fill_v_for_hash_functions(long unsigned int dimension, int k);

/* This function creates L v vectors of vectors  one vecotr for each h function */
void fill_v_for_hash_tables(long unsigned int dimension, int k,int L, vector<vector<vector<double>>>& vec);

/* This function prints a vector of doubles for debugging purposes */
void print_vector(vector<double> vec, long unsigned int dimension);

/* This function prints a vector of integers for debugging purposes */
void print_vector(vector<int> vec, long unsigned int dimension);

/* This function prints a vector of doubles for debugging purposes */
void print_vector_of_doubles(vector<double> vec, long unsigned int dimension);

/* This function prints v vector for debugging purposes */
void print_v(vector<vector<vector<double>>>& vec,int L,int k);

/* This function creates the t of the h formula */
/* t is a double created with a uniform real distribution (0.0, w) */
double create_t_for_hash_function(double w);

/* This function creates k t's and fills t vector */
vector<double> fill_t_for_hash_functions(double w, int k);

/* This function creates L t vectors one for each hash table */
void fill_t_for_hash_tables(double w,int k,int L, vector<vector<double>>& vec);

/* This function creates the w of the h formula */
int create_w_for_hash_functions(ifstream& inputFileStream);

/* This function gets data p input and the output is an integer from h hashing */
int h_p_hash_function(vector<double> p, vector<double> v, double t, int w );


#endif