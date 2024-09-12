#include "g_functions.h"

void fill_r_for_g_hash_functions(int k, vector<int>& r){
	for(int i=0; i<k; i++){
		int rand_num = random_number_generator(k);
		// cout << rand_num << endl;
		r.push_back(rand_num);
	}	
}