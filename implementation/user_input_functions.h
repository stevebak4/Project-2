#ifndef USER_INPUT_FUNCTIONS_H
#define USER_INPUT_FUNCTIONS_H


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include <fstream>
#include <cstring>

using namespace std;

/* This function asks user to give the dataset file path, check if exists and opens it */
void ask_user_for_dataset_file_path(ifstream& inputFileStream);

/* This function asks user to give the query file path, check if exists and opens it. Also asks for the output file path and returns string with the output file path */
void ask_user_for_query_and_output_file_path(ifstream& queryFileStream, char** output_file);

/* This function asks user which algorithm to use. It returns a string with algorithm's name */
char* ask_user_for_algorithm(char** algorithm);

/* This function asks user which metric to use. */
void ask_user_for_metric(char** metric);

/* If user wants to continue presses 1, if wants to exit presses 0 */
int ask_user_continue_or_exit();

/* This function opens a file with name file_name */
void open_file2(string file_name, ifstream& inputFileStream);

#endif