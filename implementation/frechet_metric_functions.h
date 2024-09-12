#ifndef FRECHET_METRIC_FUNCTIONS_
#define FRECHET_METRIC_FUNCTIONS_


#include "math_functions_2.h"

/* This function calculates the discrete frechet distance between two curves with a dimension = 2 */
double frechet_distance(vector<double> curve1, vector<double> curve2,int data_dimension);

/* This function calculates the continuous frechet distance between two curves with a dimension = 1 */
double continuous_frechet(vector<double> curve1, vector<double> curve2,int data_dimension);

/* This function calculates the frechet distance between two curves with a dimension and returns the array */
double** frechet_array(vector<double> curve1, vector<double> curve2, int data_dimension);



#endif