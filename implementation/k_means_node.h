

#ifndef K_MEANS_NODE_H
#define K_MEANS_NODE_H


#include "math_functions.h"
#include "clustering.h"

class k_means_node{


    public:

        Bucket_node *pointer;
        double D;
        double prob;


        k_means_node(Bucket_node *p,double distance,double probability):pointer(p) {
            
            D = distance;
            prob = probability;
        }
            
        void print(){
            cout<<"D = "<<D<<" ,prob = "<<prob<<endl;
            
        }

};

#endif