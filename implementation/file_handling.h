#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H



#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/* This function gets an opened file and returns the number of lines in file */
long unsigned int number_of_file_lines(ifstream& inputFileStream);

/* This function opens a file with name file_name */
void open_file(string file_name, ifstream& inputFileStream);

void open_file(string file_name, ofstream& inputFileStream);

/* This function closes a file */
void close_file(ifstream& inputFileStream);

void close_file(ofstream& inputFileStream);

/* This function returns the dimension of data with id */
long unsigned int data_dimension_with_id(ifstream& inputFileStream);

/* This function returns the dimension of data without id */
long unsigned int data_dimension_without_id(ifstream& inputFileStream);

/* get a specific line of file */
string get_specific_line(long int line_num, ifstream& inputFileStream);

/* just move to specific line */
void move_to_specific_line(long int line_num, ifstream& inputFileStream);

/*make query vector from query file */
vector<vector<double>> make_query_vector(ifstream& q_file,vector<string> &item_id,bool fill_curve);


#endif