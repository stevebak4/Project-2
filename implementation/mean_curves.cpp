#include "mean_curves.h" 
#include "grid_functions.h"
#include "math_functions_2.h"
#include "frechet_metric_functions.h"
#include <unistd.h>
#include "hash_tables.h"


void print_vector_2(vector<double> vec, long unsigned int dimension){
    int i;
    for(i=0; i<dimension; i++){
		
		// cout << "iiiiiiiii " << i << endl;
        cout << vec[i] << " ";
    }
    cout << endl;
}



list < pair <vector<double>, vector<double>> > OptimalTraversal(vector<double> P,vector<double> Q,double **C,int data_dimension){

    list < pair <vector<double>, vector<double>> > pairs;

    cout<<"inside OptimalTraversal"<<endl;

    int counter = 0;
    vector<double> vec1;
    vector<double> vec2;
    int min_index;
    int m1 = P.size()/data_dimension-1;
    int m2 = Q.size()/data_dimension-1;
    vec1 = make_vector(P,m1*data_dimension,data_dimension);
    vec2 = make_vector(Q,m2*data_dimension,data_dimension);
    pairs.push_back({vec1,vec2});
   
    while ( (m1 != 0) && (m2 != 0 )){                                                   //maybe this needs to be adjusted
        min_index = min_between_three_numbers(C[m1-1][m2],C[m1][m2-1],C[m1-1][m2-1]);
        if (min_index == 0){
            m1 = m1 - 1;
            vec1 = make_vector(P,m1*data_dimension,data_dimension);
            vec2 = make_vector(Q,m2*data_dimension,data_dimension);
            pairs.push_back({vec1,vec2});
        }else if (min_index == 1){
            m2 = m2 - 1;
            vec1 = make_vector(P,m1*data_dimension,data_dimension);
            vec2 = make_vector(Q,m2*data_dimension,data_dimension);
            pairs.push_back({vec1,vec2});

        }else {
            m1 = m1 - 1;
            m2 = m2 - 1;
            vec1 = make_vector(P,m1*data_dimension,data_dimension);
            vec2 = make_vector(Q,m2*data_dimension,data_dimension);
            pairs.push_back({vec1,vec2});
        }

        counter++;
    }

    printf("m1 = %d , m2= %d\n",m1,m2);
    return pairs;

}


vector<double> MeanCurve(vector<double> left_curve,vector<double> right_curve,int data_dimension,int data_length,double e){

    double **traversal_array;
    double current_mean = 0;
    double point = 0;
    vector<double> mean_vector;
    list < pair <vector<double>, vector<double>> > pairs;

    
    mean_curve_filtering(left_curve,data_length,data_dimension,e);
    mean_curve_filtering(right_curve,data_length,data_dimension,e);


    if (right_curve.size() == 0)
        return left_curve;
    if (left_curve.size() == 0)
        return right_curve;        

    
    

    traversal_array = frechet_array(left_curve,right_curve,data_dimension);
    pairs = OptimalTraversal(left_curve,right_curve,traversal_array,data_dimension);
    
    cout <<"MeanCurve \n\n\n\n"<<endl;
    for (const auto mypair : pairs){
        vector<double> vec1 = mypair.first;
        vector<double> vec2 = mypair.second;
       
        for (int i = 0; i < data_dimension; i++){
            point = (vec1[i] + vec2[i])/2;
            mean_vector.push_back(point);
        }
        
    }
    cout<<"left curve size = "<<left_curve.size()<<endl;
    cout<<"right curve size = "<<right_curve.size()<<endl;
    cout<<"meann_curve_size = "<< mean_vector.size() <<endl;
    cout<<"data dimension = "<<data_dimension<<endl;
    
    //sleep(2);
    
    for(int i = 0; i < left_curve.size()/data_dimension; i++) {
        delete [] traversal_array[i];
    }
    delete [] traversal_array;
    
 
    cout<<"\n\nEXITING MEAN_VECTOR\n\n"<<endl;
    return mean_vector;
}


//works for a complete binary tree
vector<double> PostOrderTraversal(btree_node *root,int data_dimension,int data_length,double e){

    btree_node *node = root;
    vector<double> left_curve;
    vector<double> right_curve;    
    
    if((node->left == NULL) && (node->right == NULL)){
        
       return node->p;
    }else{
        left_curve = PostOrderTraversal(node->left,data_dimension,data_length,e);
        if(node->right != NULL){
            right_curve = PostOrderTraversal(node->right,data_dimension,data_length,e);
        }//else right_curve = NULL curve. this step is not weitten because NULL curve means that size == 0
            
        return MeanCurve(left_curve,right_curve,data_dimension,data_length,e);
            
    } 



}




vector<double> Return_Mean_Curve(vector<Info_node> &cluster,int data_dimension,int data_length,double e){

    btree_node *root = NULL;
    int height = ceil( log2(cluster.size()) );
    root = btree_create_and_fill(root,height,0,0,data_dimension,cluster);   //current height must be = 0 at the beggining
    vector<double> mean_curve = PostOrderTraversal(root,data_dimension,data_length,e);
    btree_delete(root);
    
    root = NULL;
    reverse(mean_curve.begin(), mean_curve.end());
    //printf("MeanCurve size = ")
    return mean_curve;
}






void mean_curve_filtering(vector<double> &mean_curve,int data_length,int data_dimension,double e){
    
    
    mean_curve = e_filtering(mean_curve,data_dimension,e);    
    if (mean_curve.size() > data_length){
        mean_curve = min_max_filtering(mean_curve,data_dimension);

        while(mean_curve.size() > data_length){
            mean_curve.pop_back();
        }
    }

}