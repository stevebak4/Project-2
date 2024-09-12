#ifndef F_FUNCTIONS_H_
#define F_FUNCTIONS_H_


#include "hash_tables.h"

static vector<map<int, int>> pairs;

/* This function gets an integer and returns zero or one randomly */
int f_function(int h_p);

/* This function initializes the vector of map */
void initialize_vector_of_map(vector<map<int, int>>& pairs, int d);

/* This function gets a point p and hashes it. It returns an int of concatenated bits */
vector<int> f_p_hash_function(vector<double> &p, int new_dimension, vector<vector<double>>& v, vector<double>& t, int w, vector<map<int, int>>& pairs);

/* This function prints the vector of map */
void print_map(vector<map<int, int>>& pairs);

/* This function searches if element in the i'th map of pairs vector exists. If the pair already exists it returns it->second else it returns 0 */
int exist_pair(vector<map<int, int>>& pairs, int ith, int element);

/* This function gets a binary ineger and converts it to decimal integer */
long long unsigned int binary_int_to_decimal_int(vector<int> n);

//return all neighbor buckets with hamming distance = 1 of hashed_q bucket //
vector<vector<int>> hypercube_neighbor_buckets(vector <int> &q, int number_of_neighbor_bukets, int new_dimension, vector<vector<double>>& v, vector<double>& t, int w, vector<map<int, int>>& pairs);

/*Return all neighbor buckets of q  in 0101 (binary) form */
vector<vector<int>> return_buckets_for_hashing(vector<double> &q, int new_dimension,int probes, vector<vector<double>>& v, vector<double>& t, int w, vector<map<int, int>>& pairs);

#endif