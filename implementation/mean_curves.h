#ifndef MEAN_CURVE_H
#define MEAN_CURVE_H



#include <iostream>
#include <map>
#include <vector>
#include "btree_node.h"
#include <list>


using namespace std;

list < pair <vector<double>, vector<double>> > OptimalTraversal(vector<double> P,vector<double> Q,double **C,int data_dimension);

vector<double> MeanCurve(vector<double> left_curve,vector<double> right_curve,int data_dimension,int data_length,double e);

vector<double> PostOrderTraversal(btree_node *root,int data_dimension,int data_length,double e);

vector<double> Return_Mean_Curve(vector<Info_node> &cluster,int data_dimension,int data_length,double e);

void mean_curve_filtering(vector<double> &mean_curve,int data_length,int data_dimension,double e);

#endif