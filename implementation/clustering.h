#ifndef CLUSTERING_H_
#define CLUSTERING_H_


#include "hypercube.h"


Bucket_node& choose_randomly_uniform_centroid(vector<vector<Bucket_node>> &struct1,int val);

double min_distance_to_centroid(vector<double> &point,const vector<Bucket_node> &centroids);

bool search_centroids(vector<Bucket_node> centroids,vector<double> point);

Bucket_node* return_nearest_centroid(vector<double> &point,const vector<Bucket_node> &centroids,int data_dimension,double(*metric)(vector<double>,vector<double>,int));

Bucket_node* return_second_nearest_centroid(vector<double> &point,const vector<Bucket_node> &centroids,int data_dimension,double(*metric)(vector<double>,vector<double>,int));

vector<double> calculate_mean_vector(vector<Bucket_node> bucket);

vector<double> calculate_mean_vector(vector<Info_node> bucket);

void print_final_matrix(const vector<vector<Bucket_node>> matrix);

void print_final_matrix(const vector<vector<Info_node>> matrix);

void initialize_flag_matrix(vector<vector<bool>> &flag_matrix,vector<vector<vector<Bucket_node>>> L_hash_tables );

void print_flag_matrix(vector<vector<bool>> &flag_matrix);

bool search_cluster(vector<Info_node> &cluster,vector<double> &p);

vector<vector<Bucket_node>> return_unassigned_points(vector<vector<Bucket_node> > &hashtable,vector<vector<bool>> &flag_matrix);

vector<Bucket_node> Initialize_k_centers_bucket(vector<vector<Bucket_node>> &struct1,int N);

vector<double> silhouette(vector<vector<Info_node>>& clusters,int data_dimension,double e,string metric_name,double(*metric)(vector<double>,vector<double>,int));

void clustering_update_step(vector<Bucket_node> &centroids,vector<vector<Info_node>> &clusters,int data_dimension,int data_length,double e,string method);

vector<vector<Info_node>> Exact_Loyd(vector<vector<Bucket_node>> &struct1,vector<Bucket_node> &centroids,int reps,int data_dimension,double e,string method,double(*metric)(vector<double>,vector<double>,int));

vector<vector<Info_node>> Reverse_Approach_LSH(vector<vector<vector<Bucket_node>>> L_hash_tables,vector<Bucket_node> &centroids,vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet,int w,int k,int TableSize,double range,int max_iterations,int probes,string method,long int  M,long long unsigned int &count,int data_dimension,double delta,double e,bool discrete_or_continuous,double(*metric)(vector<double>,vector<double>,int));

#endif 