#ifndef MATH_FUNCTIONS_2_H_
#define MATH_FUNCTIONS_2_H_


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <random>

using namespace std;


/* This function returns the max of two numbers*/
double max_between_two_numbers(double num1, double num2);

/* This function returns the mix of two numbers*/
double min_between_three_numbers(double num1, double num2, double num3);

/* This function returns the min index of three numbers*/
double min_index_between_three_numbers(double num1, double num2, double num3);

/* This function calculates the euclidean distance between two point */
double euclidean_dist(double point1, double point2);

/* This function creates and returns size of grid δ */
double create_grids_d(int num_of_curves_points);

/* This function creates random number from uniform distribution between [0,δ) */
double t_uniformly_generated(double d);

/*This function takes a vector curve and outputs a sigle point of the curve starting from vector_start*/
vector<double> make_vector(vector<double> &vec,int vector_start,int data_dimension);


#endif