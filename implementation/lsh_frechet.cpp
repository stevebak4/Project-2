#include "hash_tables.h"
#include <unistd.h>
#include "grid_functions.h"

#define M 2147483647


void remove_consecutive_duplicates(vector<double> &vec,int data_dimension){

	int flag = 1;
    for(int i = 0; i < vec.size(); i += data_dimension){
		
		if (i + data_dimension <vec.size()){
			flag = 1;
			for(int j = 0; j < data_dimension; j++){
				if (vec[i+j] != vec[i+j+data_dimension] ){
					flag = 0;
				}
			}
			if (flag == 1){
				for(int j = 0; j < data_dimension; j++)
					vec.erase(vec.begin()+i);
				i = i -data_dimension;	
			}
		}
    }

}

void lsh_frechet_one_table(ifstream& p_inputFile,vector<vector<Bucket_node>>& one_hash_table, int k, vector<vector<double>>& vec, vector<double>& taf, vector<int>& r,vector<double>& t_frechet, int w,int TableSize,double d,int data_dimension,double e,bool discrete_or_continuous,bool fill_curve){	
	long long int sum_of_h_multiplied_with_r;
	long unsigned int n = number_of_file_lines(p_inputFile);
		long unsigned int dimension = data_dimension_without_id(p_inputFile);
	cout <<"LSH Frechet filling one hashtable"<<endl;

	vector<Bucket_node> array_of_vector_of_buckets[TableSize];	
	string str_p_to_hash;
	for (int line=1; line<=n; line++){ // for every p
		/* get the string that will be hashed.  */
	 	getline(p_inputFile,str_p_to_hash);
		/* convert it to vector without the first number which is the id */
		vector<double> vec_p_to_hash;
        vector<double> grid_curve;
       

        if (discrete_or_continuous == 0){ //carve is discrete
            if (fill_curve == 1) //fill curve with time coordinate
                vec_p_to_hash = string_of_integers_to_vector_add_time(str_p_to_hash); // without id in it
            else 
                vec_p_to_hash = string_of_integers_to_vector(str_p_to_hash); // without id in it
	
            grid_curve = generate_discrete_grids_curve(vec_p_to_hash,d,t_frechet);
			remove_consecutive_duplicates(grid_curve,data_dimension);

			if (grid_curve.size() < vec_p_to_hash.size()){
				grid_curve = padding(grid_curve,PADDING_VALUE,vec_p_to_hash.size());
			}

			
            
        
        }
        else if(discrete_or_continuous == 1){       //curve is continuous
            vec_p_to_hash = string_of_integers_to_vector(str_p_to_hash); // without id in it

			grid_curve = e_filtering(vec_p_to_hash,data_dimension,e);
			grid_curve = generate_continuous_grids_curve(grid_curve,d,t_frechet);
			grid_curve = min_max_filtering(grid_curve,data_dimension);	

			if (grid_curve.size() < vec_p_to_hash.size()){
				grid_curve = padding(grid_curve,PADDING_VALUE,vec_p_to_hash.size());
			}
        }
        
		string item_id;
		stringstream iss( str_p_to_hash );
		iss >> item_id;
		long long int id =  ID_func( grid_curve, vec, taf,r, w,k,TableSize);
		//cout << "id= " << id << endl;
		long long int hashed_p_with_g_function = g_func(id, TableSize);

		if (search_bucket_for_point(array_of_vector_of_buckets[hashed_p_with_g_function],vec_p_to_hash ) != 1){

			Bucket_node bucket = Bucket_node(vec_p_to_hash, id,item_id);
			array_of_vector_of_buckets[hashed_p_with_g_function].push_back(bucket);
		}
		
	}
	/* fill the hash table with the vectors which contain the p's */
	for(int i=0; i<TableSize; i++){
		one_hash_table.push_back(array_of_vector_of_buckets[i]);
	}
	p_inputFile.clear();
	p_inputFile.seekg(0,ios::beg);
}


void lsh_frechet_fill_L_hash_tables(vector<vector<vector<Bucket_node>>>& L_hash_tables, ifstream& p_inputFile, int k, vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r,vector<vector<double>>& t_frechet, int w, int L,int TableSize,double d,int data_dimension,double e,bool discrete_or_continuous,bool fill_curve){
	
	vector<vector<Bucket_node>> one_hash_table;
	for (int i=0; i<L; i++){
		lsh_frechet_one_table(p_inputFile, one_hash_table, k, v[i], t[i], r,t_frechet[i], w,TableSize,d,data_dimension,e,discrete_or_continuous,fill_curve);
		L_hash_tables.push_back(one_hash_table);
		clear_one_hash_table_variable(one_hash_table);
	}
	
}









