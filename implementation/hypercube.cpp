#include "hypercube.h"
#include <unistd.h>
void fill_hypercube(ifstream& p_inputFile, vector<vector<Bucket_node>>& hypercube, vector<map<int, int>>& pairs, vector<vector<double>>& v, vector<double>& t, int w, int new_dimension){	
	//initialize_vector_of_map(pairs, new_dimension);
	long unsigned int n = number_of_file_lines(p_inputFile);
	long unsigned int dimension = data_dimension_without_id(p_inputFile);
	long long unsigned int hypercube_number_of_buckets = pow(2, new_dimension);

	vector<Bucket_node> array_of_vector_of_buckets[hypercube_number_of_buckets];	
	string str_p_to_hash;
	for (int line=1; line<=n; line++){ // for every p
		/* get the string that will be hashed.  */
		getline(p_inputFile,str_p_to_hash);
		/* convert it to vector without the first number which is the id */
		vector<double> vec_p_to_hash = string_of_integers_to_vector(str_p_to_hash); // without id in it

		string item_id;
		stringstream iss( str_p_to_hash );
		iss >> item_id;
		vector<int> f_p = f_p_hash_function(vec_p_to_hash, new_dimension, v, t, w, pairs);
		unsigned int bucket_num = binary_int_to_decimal_int(f_p);	
		
		if (f_p.size() < new_dimension)
			exit(-1);
		if (search_bucket_for_point(array_of_vector_of_buckets[bucket_num],vec_p_to_hash ) != 1){
			Bucket_node bucket = Bucket_node(vec_p_to_hash, 0,item_id);
			array_of_vector_of_buckets[bucket_num].push_back(bucket);
		}
	}

	/* fill the hash table with the vectors which contain the p's */
	for(int i=0; i<hypercube_number_of_buckets; i++){
		hypercube.push_back(array_of_vector_of_buckets[i]);
	}
}

