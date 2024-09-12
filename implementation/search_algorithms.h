
#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H


#include "bucket_node.h"
#include "math_functions.h"
#include "user_input_handling.h"


/*This function is used to combine the results of each one of the L HASTABLES inti one list by
clearing duplicates and sorting the points by distance */
vector<Info_node> combine_k_results(vector<Info_node>  best,vector<Info_node> best_k,int N,int sort_flag);

/*Find the position i and j of vector p in the hashtable[0] of the L HASTABLES */
vector<int> search_first_hashtable_for_key(vector<vector<Bucket_node>> hashtable,vector<double> &p);

/*Implementation of Aproximate K Nearest Neighbors*/
vector<Info_node> A_KNN(vector<vector<Bucket_node>> &hashtable,vector<double> q,int id,int N,int hash_result,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) );

/*Implementation of Brute Force K Nearest Neighbors*/
vector<Info_node> BF_KNN(vector<vector<Bucket_node>> &hashtable,vector<double> &q,int N,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) );

/*Implementation of Range_Search */
vector<Info_node> Range_Search(vector<vector<Bucket_node>> &hashtable,vector<double> q,double r,int N,int hash_result,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) );

/*Implementation of a Range_Search version wich is used for Reverse_Approach LSH and Hypercube in order to mark the poits of the flag matrix */
vector<Info_node> Range_Search_for_Reverse_Approach(vector<vector<Bucket_node>> &hashtable,vector<vector<Bucket_node>> &first_hashtable,vector<double> &q,vector <vector<bool>> &flag_matrix,double range,int hash_result,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int) );

/*Returning K best neighbors from all hash tables using method as a search function */
vector<Info_node> return_k_best_LSH(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<double>& q,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,int w,int k,int TableSize,int N,double range,string &search_method,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int));

/*Returning K best neighbors from Hyercube using method as a search function */
vector<Info_node> return_k_best_hypercube(vector<vector<Bucket_node>> hypercube,vector<double>& q,vector<vector<double>>& v, vector<double>& t, vector<int>& r,int w,vector<map<int, int>>& pairs,int new_dimension,int probes,int N,double range,string &search_method,long int M,long long unsigned int &count,int data_dimension,double(*metric)(vector<double>,vector<double>,int));

/*Returning K best neighbors from LSH FRECHET using method as a search function */
vector<Info_node> return_k_best_LSH_Frechet(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<double>& q,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet,int w,int k,int TableSize,int N,double range,string &search_method,long int M,long long unsigned int &count,int data_dimension,double delta,bool discrete_or_continuous,double(*metric)(vector<double>,vector<double>,int));

#endif