#ifndef GRID_FUNCTIONS_H
#define GRID_FUNCTIONS_H


#include "frechet_metric_functions.h"

// double **generate_array_grid_t(int L, int K, double d)

/* This function gets a curve, δ, and t uniformly generated and returns the discrete grids curve */
vector<double> generate_discrete_grids_curve(vector<double> current_curve, double d, vector<double> t);

/* This function gets a curve, δ, and t uniformly generated and returns the continuous grids curve */
vector<double> generate_continuous_grids_curve(vector<double> current_curve, double d, vector<double> t);

/* This function gets a vector of filtered curve, the large padding value and the dimension of the unfiltered curve and fills curve with padding values */
vector<double> padding(vector<double> filtered_curve, double padding_value, int dimension);

/*This function is used for min_max_filtering a vector */
vector<double> min_max_filtering(vector<double> &curve, int data_dimension);

/*This function is used for the continuous frechet filtering */
vector<double> e_filtering(vector<double> &curve, int data_dimension,double e);


#endif