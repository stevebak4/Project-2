#include "grid_functions.h"
#include "user_input_functions.h"
#include "user_input_handling2.h"
#include <map>
#include "mean_curves.h"
#include "lsh_frechet.h"
#include "frechet.h"
#include "curve.h"
#include "point.h"
#include "frechet.h"

using namespace Frechet::Continuous;


using namespace std;

int main(int argc, char *argv[]) {
    
    char* input_file = NULL ;
    char* query_file = NULL;
    int k = -1;
    int L;
    long int M;
    int probes;
    char* output_file = NULL;
    char* LSH_Hypercube_or_Frechet = NULL;
    char* discrete_or_continuous = NULL; 
    double delta;

    ifstream p_file;
    ifstream q_file;
    ofstream out_file;


    /* testing max_between_two_numbers function */
    double max = max_between_two_numbers(5, 6);
    cout << "max = " << max << endl;
    /* -------- */

    /* testing min_between_three_numbers function */
    double min = min_between_three_numbers(5, 6, 7);
    cout << "min = " << min << endl;
    /* -------- */

    /* testing euclidean_dist function */
    double dist = euclidean_dist(5, 6);
    cout << "dist = " << dist << endl;
    /* -------- */

    /* testing frechet_distance function */
    vector<double> curve1 = {0.2,2.0, 1.5,2.8, 2.3,1.6, 2.9,1.8, 4.1,3.1, 5.6,2.9, 7.2,1.3, 8.2,1.1}; 
    //vector<double> curve1 = {1,2,3}; 
    /*

    curve1.push_back(1);
    curve1.push_back(1);

    curve1.push_back(2);
    curve1.push_back(2);

    curve1.push_back(3);
    curve1.push_back(3);
    */
    vector<double> curve2 = {0.3,1.6, 3.2,3.0, 3.8,1.8, 5.2,3.1, 6.5,2.8, 7.0,0.8, 8.9,0.6};
    //vector<double> curve2 = {4,5,6};
    /*
    curve2.push_back(1);
    curve2.push_back(4);

    curve2.push_back(2);
    curve2.push_back(5);

    curve2.push_back(3);
    curve2.push_back(6);
    */
    int data_dimension = 2;
    double fr_dist = frechet_distance(curve1, curve2,data_dimension);
    cout << "fr_dist = " << fr_dist << endl;
    /* -------- */

    /* testing create_grids_d function */
    double d = create_grids_d(150);
    cout << "d = " << d << endl;
    /* -------- */

    /* testing t_uniformly_generated function */
    double t1 = t_uniformly_generated(d);
    double t2 = t_uniformly_generated(d);
    double t3 = t_uniformly_generated(d);
    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;
    cout << "t3 = " << t3 << endl;
    /* -------- */

    /* testing generate_discrete_grids_curve function */
    vector<double> t;
    t.push_back(t1);
    vector<double> grids_curve = generate_discrete_grids_curve(curve1, d, t);
    for(int i=0; i<(int)grids_curve.size(); i++){
        cout << grids_curve[i] << " ";
    }
    cout << endl;
    /* -------- */

    /* testing padding function */
    vector<double> pad_vec = padding(curve1, 8, 6);
    for(int i=0; i<(int)pad_vec.size(); i++){
        cout << pad_vec[i] << " ";
    }
    cout << endl;
    /* -------- */

    /* testing ask_user_for_dataset_file_path function */
    ifstream dataset_file;
    //ask_user_for_dataset_file_path(dataset_file);
    /* -------- */

    /* testing ask_user_for_query_and_output_file_path function */
    ifstream query_file1;
    //string path = ask_user_for_query_and_output_file_path(query_file1);
    //ofstream output_file(path);
    /* -------- */

    /* testing ask_user_for_algorithm function */
    //string algorithm_name = ask_user_for_algorithm();
    //cout << algorithm_name << endl;
    /* -------- */

    /* testing ask_user_for_metric function */
    //string metric_name = ask_user_for_metric();
    //cout << metric_name << endl;
    /* -------- */

    

    //Test pairs_list
    list < pair <vector<double>, vector<double>> > pairs_list;

    vector<double> vec1 = {1,2};
    vector<double> vec2 = {4,5};

    pairs_list.push_back({vec1,vec2});
    for (const auto mypair : pairs_list){
        
        vector<double> vec3 = mypair.first;
        vector<double> vec4 = mypair.second;

        //print_vector(vec3,vec3.size());
        //print_vector(vec4,vec4.size());


    }    

    //Testing mean curve 
    /*
    cout << "testing mean curve\n\n" << endl;
    btree_node *root = NULL;
    vector<Info_node> cluster;
    int height;
    int current_height = 0;
    int i = 0;


    for (int j = 0; j < 4; j++){
        vector<double> vec;

        for (int i = 0; i < 4; i++){
            vec.push_back(i);
            vec.push_back(i*j);
        }

        cluster.push_back(Info_node(vec,-1,"-1"));
        vec.clear();
    }

    height = ceil( log2(cluster.size()) );
    cout <<"height = " << height << endl;
    
    root = btree_create_and_fill(root,height,current_height,i,data_dimension,cluster);   //current height must be = 0 at the beggining
    cout<<"here1\n";
    print_postorder(root);
    cout<<"here2\n";
    vector<double> mean_vector = PostOrderTraversal(root,data_dimension);
    cout<<"here3\n";
    btree_delete(root);
    cout<<"after deletion\n";
    root = NULL;

    for (int j = 0; j < mean_vector.size(); j++){
        cout << mean_vector[j]<<" ";
    }
    
    cout<<"\nTesting consecutive duplicates\n";
    //test remove duplicate points
    vector<double> duplicates = {3,4,3,4,3,4,4,4};

    remove_consecutive_duplicates(duplicates,2);
    for (int j = 0; j < duplicates.size(); j++){
        cout << duplicates[j]<<" ";
    }
    cout<<endl;

    cout<<"\nTesting min_max_filtering\n";
    vector<double> filtered;
    vector<double> vect =  {1,1,2,2,3,3,2,2,1,1};
    
    filtered = min_max_filtering(vect,2);
    for (int j = 0; j < filtered.size(); j++){
        cout << filtered[j]<<" ";
    }
    cout<<endl;
    */
    /* testing ask_user_continue_or_exit function */


      
    cout << "--------------------" << endl;

    /* testing distance continuous frechet function */
    Distance dsts;
    // Curve* crv1();
    // Curve* crv2();
    // dsts = distance(crv1, crv2);
    vector<double> dof(2);
    for (int j = 0; j < dof.size(); j++){
        cout<<"dof["<<j<<"] = "<<dof[j]<<endl;
    }



    Points points(1);
    Point point(1);
    point.set(0,3.25);
    cout<<point[0]<<endl;
    points.add(point);

    Curve curve(points);   


    vector<double> v1 = {1,2,3};
    vector<double> v2 = {4,5,6};

    double cont_frechet = continuous_frechet(v1, v2,1);

    cout<<"continuous_frechet result = "<<cont_frechet<<endl;
    int ce = ask_user_continue_or_exit();
    cout << ce << endl;


    
    return 0;
}








