
#ifndef LSH_FRECHET_H_
#define LSH_FRECHET_H_

#include <fstream>
#include <vector>
#include "bucket_node.h"

using namespace std;


void remove_consecutive_duplicates(vector<double> &vec,int data_dimension);

void lsh_frechet_one_table(ifstream& p_inputFile,vector<vector<Bucket_node>>& one_hash_table, int k, vector<vector<double>>& vec, vector<double>& taf, vector<int>& r,vector<double>& t_frechet, int w,int TableSize,double d,int data_dimension,double e,bool discrete_or_continuous,bool fill_curve);

void lsh_frechet_fill_L_hash_tables(vector<vector<vector<Bucket_node>>>& L_hash_tables, ifstream& p_inputFile, int k, vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet, int w, int L,int TableSize,double d,int data_dimension,double e,bool discrete_or_continuous,bool fill_curve);

#endif