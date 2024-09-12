#include "hash_tables.h"
#include <unistd.h>

#define M 2147483647




char search_bucket_for_point(vector<Bucket_node> bucket,vector<double> point){

	for (int i = 0; i < bucket.size(); i++){

		if (bucket[i].get_p() == point)
			return 1;
	}

	return 0;

}


void fill_one_hash_table(ifstream& p_inputFile,vector<vector<Bucket_node>>& one_hash_table, int k, vector<vector<double>>& vec, vector<double>& taf, vector<int>& r, int w,int TableSize){	
	long long int sum_of_h_multiplied_with_r;
	long unsigned int n = number_of_file_lines(p_inputFile);
	long unsigned int dimension = data_dimension_without_id(p_inputFile);

	vector<Bucket_node> array_of_vector_of_buckets[TableSize];	
	string str_p_to_hash;
	for (int line=1; line<=n; line++){ // for every p

		/* get the string that will be hashed.  */
	 	getline(p_inputFile,str_p_to_hash);
		/* convert it to vector without the first number which is the id */
		vector<double> vec_p_to_hash = string_of_integers_to_vector(str_p_to_hash); // without id in it

		string item_id;
		stringstream iss( str_p_to_hash );
		iss >> item_id;
		cout<<"item_id: "<<item_id<<endl;

		long long int id = ID_func(vec_p_to_hash,vec,taf,r,w,k,TableSize);
		long long int hashed_p_with_g_function = g_func( id,TableSize);
		/* create the bucket node for this p and push it into the right place in hash table */
		
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

long long int ID_func(vector<double>& q,vector<vector<double>>& v, vector<double>& t, vector<int>& r,int w,int k,int TableSize){

	long long int sum_of_h_multiplied_with_r = 0;

	for (int h=0; h<k; h++){ // for every hash function h
		int hashed_p_with_h_function = h_p_hash_function(q, v[h], t[h], w);	
		sum_of_h_multiplied_with_r = modulo(sum_of_h_multiplied_with_r + hashed_p_with_h_function*r[h],M);
		
	}
	long long int ID = sum_of_h_multiplied_with_r;

	return ID;		

}

long long int g_func(int ID,int TableSize){

	long long int hashed_p_with_g_function = modulo(ID, TableSize);

	return hashed_p_with_g_function;		

}

void clear_one_hash_table_variable(vector<vector<Bucket_node>>& one_hash_table){

	for (size_t y = 0; y < one_hash_table.size(); y++)
	{
		for (size_t x = 0; x < one_hash_table[y].size(); x++)
		{
			one_hash_table[y].clear();
		}
	}
	one_hash_table.clear();

}

void fill_L_hash_tables(vector<vector<vector<Bucket_node>>>& L_hash_tables, ifstream& p_inputFile, int k, vector<vector<vector<double>>>& v, vector<vector<double>>& t, vector<int>& r, int w, int L,int TableSize){
	
	vector<vector<Bucket_node>> one_hash_table;
	for (int i=0; i<L; i++){
		fill_one_hash_table(p_inputFile, one_hash_table, k, v[i], t[i], r, w,TableSize);
		L_hash_tables.push_back(one_hash_table);
		clear_one_hash_table_variable(one_hash_table);
	}
	cout << L_hash_tables.size() << endl;
	cout << L_hash_tables[0].size() << endl;
	cout << L_hash_tables[0][0].size() << endl;	

}


void print_one_hash_table(vector<vector<Bucket_node>>& one_hash_table){

	for (int i = 0; i < one_hash_table.size(); i++){
		cout<<"printing bucket i = "<<i<<"\n"<<endl;
		for(int j = 0; j < one_hash_table[i].size(); j++){
			cout <<"size = "<<one_hash_table[i].size();
			cout <<endl;
			cout <<endl;
		
			break;	
			//one_hash_table[i][j].print();
		}
	}

}


void print_L_hash_tables(vector<vector<vector<Bucket_node>>>& L_hash_tables){

	for (int i = 0; i < L_hash_tables.size(); i++){
		cout<<"PRINTING HASHTABLE I = "<<i<<"\n\n\n"<<endl;
		print_one_hash_table(L_hash_tables[i]);
	}	
}









