#ifndef HYPERCUBE_H_
#define HYPERCUBE_H_


#include "f_functions.h"

/* This function fills the hypercube with p's */
void fill_hypercube(ifstream& p_inputFile, vector<vector<Bucket_node>>& hypercube, vector<map<int, int>>& pairs, vector<vector<double>>& v, vector<double>& t, int w, int new_dimension);

#endif