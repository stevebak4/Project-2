#include "frechet_metric_functions.h"
#include "point.h"
#include "curve.h"
#include "frechet.h"
#include "math_functions.h"
#include "hash_functions_h.h"

using namespace Frechet::Continuous;

double frechet_distance(vector<double> curve1, vector<double> curve2,int data_dimension){
    
	double distance;
    int dimension1 = curve1.size()/data_dimension;
    int dimension2 = curve2.size()/data_dimension;

    vector<double> vec1;
    vector<double> vec2;

    /* memory allocation for array */
    double **traversal_array = new double * [dimension1];
    for(int i = 0; i < dimension1; ++i) {
        traversal_array[i] = new double[dimension2];
    }
    /* end of memory allocation */
    vec1 = make_vector(curve1,0,data_dimension);
    vec2 = make_vector(curve2,0,data_dimension);

    traversal_array[0][0] = euclidean_distance_2(vec1,vec2);
    
    
    for (int i = 0 ; i < dimension1; i++){
        for (int j = 0 ; j < dimension2; j++){

            
            if (i == 0 && j > 0){
                vec1 = make_vector(curve1,0,data_dimension);
                vec2 = make_vector(curve2,data_dimension*j,data_dimension);
                traversal_array[i][j] = max_between_two_numbers(traversal_array[0][j-1], euclidean_distance_2(vec1, vec2));

            }if (i > 0 && j == 0){
                vec1 = make_vector(curve1,data_dimension*i,data_dimension);
                vec2 = make_vector(curve2,0,data_dimension);
                traversal_array[i][j] = max_between_two_numbers(traversal_array[i-1][0], euclidean_distance_2(vec1, vec2));


            } 
            
            if( i > 0 && j > 0){
                vec1 = make_vector(curve1,data_dimension*i,data_dimension);
                vec2 = make_vector(curve2,data_dimension*j,data_dimension);
                traversal_array[i][j] = max_between_two_numbers(min_between_three_numbers(traversal_array[i-1][j], traversal_array[i][j-1], traversal_array[i-1][j-1]), euclidean_distance_2(vec1, vec2));
            }
        }
    
    }
    
	distance = traversal_array[dimension1-1][dimension2-1];
	
    /* free memory */
    for(int i = 0; i < dimension1; ++i) {
        delete [] traversal_array[i];
    }
    delete [] traversal_array;
    /* end free memory */
	
	return distance;
}





double** frechet_array(vector<double> curve1, vector<double> curve2,int data_dimension){
    
	double distance;
    int dimension1 = curve1.size()/data_dimension;
    int dimension2 = curve2.size()/data_dimension;

    vector<double> vec1;
    vector<double> vec2;

    /* memory allocation for array */
    double **traversal_array = new double * [dimension1];
    for(int i = 0; i < dimension1; ++i) {
        traversal_array[i] = new double[dimension2];
    }
    /* end of memory allocation */
    vec1 = make_vector(curve1,0,data_dimension);
    vec2 = make_vector(curve2,0,data_dimension);

    traversal_array[0][0] = euclidean_distance_2(vec1,vec2);
    
    for (int i = 0 ; i < dimension1; i++){
        for (int j = 0 ; j < dimension2; j++){

            
            if (i == 0 && j > 0){
                vec1 = make_vector(curve1,0,data_dimension);
                vec2 = make_vector(curve2,data_dimension*j,data_dimension);
                traversal_array[i][j] = max_between_two_numbers(traversal_array[0][j-1], euclidean_distance_2(vec1, vec2));

            }if (i > 0 && j == 0){
                vec1 = make_vector(curve1,data_dimension*i,data_dimension);
                vec2 = make_vector(curve2,0,data_dimension);
                traversal_array[i][j] = max_between_two_numbers(traversal_array[i-1][0], euclidean_distance_2(vec1, vec2));


            } 
            
            if( i > 0 && j > 0){
        
                vec1 = make_vector(curve1,data_dimension*i,data_dimension);
                vec2 = make_vector(curve2,data_dimension*j,data_dimension);
                traversal_array[i][j] = max_between_two_numbers(min_between_three_numbers(traversal_array[i-1][j], traversal_array[i][j-1], traversal_array[i-1][j-1]), euclidean_distance_2(vec1, vec2));
            }
        }
    
    }
   
    return traversal_array;
	

}



double continuous_frechet(vector<double> curve1, vector<double> curve2,int data_dimension){

    if (data_dimension != 1){
        cout<<"EROOR DATA DIMENSION"<<endl;
        exit(-1);
    }

    Points points1(1);
    Points points2(1);

    for (int i=0;i<curve1.size(); i++){
        Point point(1);
        point.set(0,curve1[i]);
        points1.add(point);

    }

    for (int i=0;i<curve2.size(); i++){
        Point point(1);
        point.set(0,curve2[i]);
        points2.add(point);

    }
    
    string str = "unnamed_curve";
    Curve cur1(points1,str);
    Curve cur2(points2,str);
    Distance d = Frechet::Continuous::distance(cur1,cur2);


    return (double)d.value;


}