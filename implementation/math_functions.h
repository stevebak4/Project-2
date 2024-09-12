#ifndef MATH_FUNCTIONS_H_
#define MATH_FUNCTIONS_H_


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <map>
#include <time.h>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
#include <chrono>
#include <iomanip>
#include <cmath>
#include "file_handling.h"

using namespace std;

/* Returns a random number following normal distribution */
double normal_distribution_generator(void);

/* Modulo between a and b. */
/* The modulo supports negative numers */
long long int modulo(long long int a, long long int b); 

/* This function gets two file pointers and the number of rows where the vectors are */
/* It returns the euclidean distance between these two vectors */
double euclidean_distance(ifstream& inputFileStream1, int line1, ifstream& inputFileStream2, int line2);

/* This function computes and returns the euclidean distance between two vectors*/
double euclidean_distance_2(vector<double> vec1,vector<double> vec2);

/* This function computes and returns the euclidean distance between two vectors*/
double euclidean_distance_2(vector<double> vec1,vector<double> vec2,int data_dimension);  //the third argument is a dummy argument

/* This function converts a string of integers to a vector without the first number which is the id */
vector<double> string_of_integers_to_vector(string str);

/* This function converts a string of integers to a vector and adds the x coordinate without the first number which is the id */
vector<double> string_of_integers_to_vector_add_time(string str);

/* This function calculates inner product of two vectors */
double dot_product(vector<double> p, vector<double> v);

/* This function creates a random integer between 0 and k-1 */
int random_number_generator(int k);

/* This function gets a vector with zeros and ones and concatenates to an unsigned integer*/
unsigned int bits_concatenation(vector<int> bits);

/* This function returns the hamming distance of two integers */
/* For example number1=9 and number2=14 hamming_distance is 2. 9->1001 and 14->1110 */
int hamming_distance(int number1, int number2);

/* This function splits an integer into its digits. 19->1 and 9 */
vector<int> split_integer_digits(int num);

/* This function gets a number the digits place. we want for example to replace the second (start from end) digit of 10110. We will get 10100. */
vector<int> replace_digit(vector<int> &num, int digits_place, int new_dimension);


#endif