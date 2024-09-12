
#ifndef BTREE_NODE_H
#define BTREE_NODE_H



#include <iostream>
#include <vector>
#include "info_node.h"



using namespace std;



typedef struct btree_node {

    vector<double> p;
    btree_node *left;
    btree_node *right;

    void print(){

        if (p.size() != 0){
            cout<<"btree_node curve = ";
            
            for(unsigned int i=0; i<p.size(); i++)
                cout << p[i] << " ";
            cout<<endl;   

        }
    }
        
}btree_node;

btree_node *btree_create_node(btree_node *node);


btree_node *btree_create_and_fill(btree_node *root,int height,int current_height,int i,int data_dimension,vector<Info_node> cluster);   //current height must be = 0 at the beggining


void print_postorder(btree_node *root);

void btree_delete(btree_node *root);


#endif