#ifndef HASH_TABLES_H
#define HASH_TABLES_H


#include "math_functions.h"
#include <iterator>
#include "g_functions.h"

#define PADDING_VALUE 1000.0


/* This function fills one hash table with p's */
void fill_one_hash_table(ifstream& p_inputFile, vector<vector<Bucket_node>>& one_hash_table, int k, vector<vector<double>>& v, vector<double>& t, vector<int>& r, int w,int TableSize);

/* This function clears one_hash_table variable so we can fill it again */
void clear_one_hash_table_variable(vector<vector<Bucket_node>>& one_hash_table);

/* This function fills L hash tables with p's */
void fill_L_hash_tables(vector<vector<vector<Bucket_node>>>& L_hash_tables, ifstream& p_inputFile, int k, vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r, int w, int L,int TableSize);

/* This function prints the elements of one hash table*/
void print_one_hash_table(vector<vector<Bucket_node>>& one_hash_table);

/* This function prints the elements of L hash tables*/
void print_L_hash_tables(vector<vector<vector<Bucket_node>>>& L_hash_tables);

/*Calculate ID */
long long int ID_func(vector<double>& q,vector<vector<double>>& v, vector<double>& t, vector<int>& r,int w,int k,int TableSize);
/*Calculate g*/
long long int g_func(int ID,int TableSize);

/*Search bucket for point in order to avoid duplixates */
char search_bucket_for_point(vector<Bucket_node> bucket,vector<double> point);

#endif