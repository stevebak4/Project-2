#include "grid_functions.h"
# include "hash_functions_h.h"
#include <unistd.h>


vector<double> generate_discrete_grids_curve(vector<double> current_curve, double d, vector<double> t){
    vector<double> grids_curve;
    int points = current_curve.size();
    int dimension = t.size();
    double a;

    for (int i = 0; i < points; i++){
        a = round(current_curve[i] / d);
        double y = (double)((double) a * d) + t[i%dimension];
        grids_curve.push_back(y);
    }
    return grids_curve;
}


vector<double> generate_continuous_grids_curve(vector<double> current_curve, double d, vector<double> t){
    vector<double> grids_curve;
    int points = current_curve.size();
    int dimension = t.size();
    double a;

    for (int i = 0; i < points; i++){
        a = round( (current_curve[i] + t[i%dimension] )/ d );
        double y = (double)((double) a * d);
        grids_curve.push_back(y);
    }
    return grids_curve;
}


vector<double> padding(vector<double> input_curve, double padding_value, int dimension){
    
    vector<double> filtered_curve = input_curve;
    while (filtered_curve.size() < dimension){
        filtered_curve.push_back(padding_value);
    }
    return filtered_curve;
}



vector<double> e_filtering(vector<double> &input_curve, int data_dimension,double e){
   
   int size = input_curve.size();
   vector<double> curve = input_curve;
   vector<double> point1;
   vector<double> point2;
   vector<double>point3;
   
   for (int i = 0; i < size; i+= data_dimension){
       
       if (size >= i+3*data_dimension){
        point1 = make_vector(curve, i, data_dimension);
        point2 = make_vector(curve, i+data_dimension,data_dimension);
        point3 = make_vector(curve, i+2*data_dimension,data_dimension);
       
        if ( ( euclidean_distance_2(point1,point2) <= e )  && (euclidean_distance_2(point2,point3) <= e ) ){

            for (int j = 0; j < data_dimension; j++){
                curve.erase(curve.begin()+i+data_dimension+j);
                i--;
            }
        }

       }
       size = curve.size();  
       
   }


    return curve;
}





vector<double> min_max_filtering(vector<double> &input_curve, int data_dimension){
   
   int size = input_curve.size();
   vector<double> curve = input_curve;
   vector<double> point1;
   vector<double> point2;
   vector<double>point3;
   
   for (int i = 0; i < size; i+= data_dimension){
       
       if (size >= i+3*data_dimension){
        point1 = make_vector(curve, i, data_dimension);
        point2 = make_vector(curve, i+data_dimension,data_dimension);
        point3 = make_vector(curve, i+2*data_dimension,data_dimension);
        if ( (point1 <= point2 && point2 <= point3) || (point1 >= point2 && point2 >= point3) ){
        
            for (int j = 0; j < data_dimension; j++){
                curve.erase(curve.begin()+i+data_dimension+j);
                i--;
            }
        }

       }
       size = curve.size();  
       
   }


    return curve;
}