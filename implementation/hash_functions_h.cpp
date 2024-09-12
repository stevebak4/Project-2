#include "hash_functions_h.h"

vector<double> create_v_for_hash_function(long unsigned int dimension){
	vector<double> v;
	double num;
	
	for(int j=0; j < dimension; j++){
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    	default_random_engine generator(seed);
    	normal_distribution<double> distribution(0.0, 1.0);

   		num =  distribution(generator);
		v.push_back(num);
	}
	return v;	
}

vector<vector<double>> fill_v_for_hash_functions(long unsigned int dimension, int k){ // !!! dimension -1 to ignore first ineger(id) !!!	
	
	vector<vector<double>> vec;
	for (int i=0; i<k; i++){
		vec.push_back(create_v_for_hash_function(dimension));
	}

	return vec;
}


void fill_v_for_hash_tables(long unsigned int dimension, int k,int L, vector<vector<vector<double>>>& vec){ // !!! dimension -1 to ignore first ineger(id) !!!	
	
	for (int i=0; i<L; i++){
		
		vec.push_back(fill_v_for_hash_functions(dimension,k));
		
	}
}



void print_vector(vector<double> vec, long unsigned int dimension){
    int i;
    for(i=0; i<dimension; i++){
		
        cout << vec[i] << " ";
    }
    cout << endl;
}


void print_vector(vector<int> vec, long unsigned int dimension){
    int i;
    for(i=0; i<dimension; i++){
		
        cout << vec[i] << " ";
    }
    cout << endl;
}



void print_v(vector<vector<vector<double>>>& vec,int L,int k){

	for(int i=0; i<L; i++){
		cout<<"HASHTABLE "<<i<<"\n\n\n";
		for(int j=0; j<k; j++){
			cout<<"for h["<<i<<"]\n\n";
			print_vector(vec[i][j],vec[i][j].size());
		}
	}
}

void print_vector_of_doubles(vector<double> vec, long unsigned int dimension){
    int i;
    for(i=0; i<dimension; i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}


double create_t_for_hash_function(double w){
	double t;
	random_device generator;
	uniform_real_distribution<double> distribution (0.0, (double) w);
	t = distribution(generator); /* Generate a new double number */
	return t;
}

vector<double> fill_t_for_hash_functions(double w, int k){
	
	vector<double> vec;
	for(int i=0; i<k; i++){
		double current_t = create_t_for_hash_function(w);
		// cout << current_t << endl;
		vec.push_back(current_t);
	}
	return vec;
}

void fill_t_for_hash_tables(double w,int k,int L, vector<vector<double>>& vec){

	for (int i=0; i<L; i++){

		vec.push_back(fill_t_for_hash_functions(w,k));
	}

}




double mean_distance_brute_force(ifstream& inputFileStream){
    int i, j;
    double distance_sum = 0;
    long unsigned int line_num;
    long unsigned int all_lines = number_of_file_lines(inputFileStream);
    long unsigned int dimension_num = data_dimension_with_id(inputFileStream);
    cout <<"inside mean_distance_brute_force" << endl;
    if (all_lines > 100)
        line_num = 100;
    else
        line_num = all_lines;    

    for(i=1; i<all_lines; i++){
        for(j= 1; j<line_num; j++){
            if (i != j){
                double currect_distance = euclidean_distance(inputFileStream, i, inputFileStream, j);
                //cout << "11111   " << currect_distance << endl;
                distance_sum = distance_sum + currect_distance;
            }
        }
    }
    //cout << "----   " << distance_sum << endl;
    long unsigned int num_of_calculated_distances = (line_num*(line_num-1))/2;
    double mean_distance = distance_sum/num_of_calculated_distances;
    return mean_distance;
}



int create_w_for_hash_functions(ifstream& inputFileStream){
	int w;
	double mean_distance = mean_distance_brute_force(inputFileStream);
	//cout<<"exiting w"<<endl;
	w =(int)floor(5 * mean_distance);
	return w;
}

int h_p_hash_function(vector<double> p,vector<double> v, double t, int w){
	double inner_product_p_v = dot_product(p,v ); // p*v
	double a = (inner_product_p_v + t)/w; // h double
	int h = (int)floor(a); // h int
	return h;
}
