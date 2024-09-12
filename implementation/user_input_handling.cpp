//#include "user_input_handling.h"
#include "clustering.h"

void lsh_user_input(int argc, char* argv[], char** input_file, char** query_file, int* k, int* L, char** output_file, int* number_of_nearest, int* radius){
    /* give default arguments */
	*k = 4;
	*L = 5;
	*number_of_nearest = 1; 
	*radius = 10000;

	for (int i = 1; i < argc; i++) { // for every user input
		if (!strcmp(argv[i], "-i")) {
			*input_file = strdup(argv[++i]);
			cout << "Input file is: " << *input_file << endl;
		}
		if (!strcmp(argv[i], "-q")) {
			*query_file = strdup(argv[++i]);
			cout << "Query file is: " << *query_file << endl;
		}	
		if (!strcmp(argv[i], "-k")) {
			*k = atoi(argv[++i]);
			cout << "k is: " << *k << endl;
		}
		if (!strcmp(argv[i], "-L")) {
			*L = atoi(argv[++i]);
			cout << "L is: " << *L << endl;
		}
		if (!strcmp(argv[i], "-o")) {
			*output_file = strdup(argv[++i]);
			cout << "Output file is: " << *output_file << endl;
		}
		if (!strcmp(argv[i], "-N")) {
			*number_of_nearest = atoi(argv[++i]);
			cout << "Number of nearest neighbors is: " << *number_of_nearest << endl;
		}
		if (!strcmp(argv[i], "-R")) {
			*radius = atoi(argv[++i]);
			cout << "Radius is: " << *radius << endl;
		}
		
	}

	/* Assert with message if a file name was not given */
	assertm(*input_file && *query_file && *output_file, "Please give input file name, query file name and output file name!");
}

void hypercube_user_input(int argc, char* argv[], char** input_file, char** query_file, int* k,long int* M, int* probes, char** output_file, int* number_of_nearest, int* radius){
	/* give default arguments */
	*k = 14; 
	*M = 10; 
	*probes = 2; 
	*number_of_nearest = 1; 
	*radius = 10000;

	for (int i = 1; i < argc; i++) { // for every user input
		if (!strcmp(argv[i], "-i")) {
			*input_file = strdup(argv[++i]);
			cout << "Input file is: " << *input_file << endl;
		}
		if (!strcmp(argv[i], "-q")) {
			*query_file = strdup(argv[++i]);
			cout << "Query file is: " << *query_file << endl;
		}	
		if (!strcmp(argv[i], "-k")) {
			*k = atoi(argv[++i]);
			cout << "k is: " << *k << endl;
		}
		if (!strcmp(argv[i], "-M")) {
			*M = atoi(argv[++i]);
			cout << "M is: " << *M << endl;
		}
		if (!strcmp(argv[i], "-probes")) {
			*probes = atoi(argv[++i]);
			cout << "probes is: " << *probes << endl;
		}
		if (!strcmp(argv[i], "-o")) {
			*output_file = strdup(argv[++i]);
			cout << "Output file is: " << *output_file << endl;
		}
		if (!strcmp(argv[i], "-N")) {
			*number_of_nearest = atoi(argv[++i]);
			cout << "Number of nearest neighbors is: " << *number_of_nearest << endl;
		}
		if (!strcmp(argv[i], "-R")) {
			*radius = atoi(argv[++i]);
			cout << "Radius is: " << *radius << endl;
		}
	}

	/* Assert with message if a file name was not given */
	assertm(*input_file && *query_file && *output_file, "Please give input file name, query file name and output file name!");
}

void cluster_user_input(int argc, char* argv[], char** input_file, char** configuration_file, char** output_file, bool* complete, char** lsh_or_hypercube_method){
	/* give default arguments */
	*complete = false;

	for (int i = 1; i < argc; i++) { // for every user input
		cout<<argv[i]<<endl;
		if (!strcmp(argv[i], "-i")) {
			*input_file = strdup(argv[++i]);
			cout << "Input file is: " << *input_file << endl;
		}
		if (!strcmp(argv[i], "-c")) {
			*configuration_file = strdup(argv[++i]);
			cout << "Configuration file is: " << *configuration_file << endl;
		}	
		if (!strcmp(argv[i], "-o")) {
			*output_file = strdup(argv[++i]);
			cout << "Output file is: " << *output_file << endl;
		}
		if (!strcmp(argv[i], "-complete")) {
			*complete = true;
		}
		if (!strcmp(argv[i], "-m")) {
			*lsh_or_hypercube_method = strdup(argv[++i]);
		}
	}
	
	/* Assert with message if a file name was not given */
	assertm(*input_file && *configuration_file && *output_file && *lsh_or_hypercube_method, "Please give input file name, configuration file name, output file name and lsh or hypercube method!");
}

void parse_configuration_file(char* configuration_file, int* number_of_clusters, int* number_of_vector_hash_tables, int* number_of_vector_hash_functions, int* max_number_M_hypercube, int* number_of_hypercube_dimensions, int* number_of_probes){
		// default 
		*number_of_vector_hash_tables = 3; 
		*number_of_vector_hash_functions = 4; 
		*max_number_M_hypercube = 10; 
		*number_of_hypercube_dimensions = 3; 
		*number_of_probes = 2;
		//cout << file << endl;
		ifstream config_file;
		config_file.open(configuration_file);
		char words[80];
		char numbers[10];

		config_file >> words;
		config_file >> numbers;
		*number_of_clusters = atoi(numbers);
		if (!config_file.eof()) {
			config_file >> words;
			config_file >> numbers;
			*number_of_vector_hash_tables = atoi(numbers);
		}
		if (!config_file.eof()) {
			config_file >> words;
			config_file >> numbers;
			*number_of_vector_hash_functions = atoi(numbers);
		}
		if (!config_file.eof()) {
			config_file >> words;
			config_file >> numbers;
			*max_number_M_hypercube = atoi(numbers);
		}
		if (!config_file.eof()) {
			config_file >> words;
			config_file >> numbers;
			*number_of_hypercube_dimensions = atoi(numbers);
		}
		if (!config_file.eof()) {
			config_file >> words;
			config_file >> numbers;
			*number_of_probes = atoi(numbers);
		}
		config_file.close();
	}



void print_clustering_output(vector<vector<Info_node>> clusters,ofstream &out_file,bool complete,bool silhouette_on_off,int data_dimension,double e,string metric_name,double(*metric)(vector<double>,vector<double>,int)){

	if (complete == false){

		for (unsigned int i=0; i<clusters.size(); i++){
				out_file<<"CLUSTER-"<<i<<"{size: "<<clusters[i].size()<<", centroid: ";
				vector<Info_node> vec = clusters[i];
				vector<double> centroid =  vec[0].get_p();

				for(unsigned int x = 0; x <centroid.size(); x++){
					out_file<<centroid[x]<<" ";

				}
				out_file<<endl; 
		}
	}else if (complete == true){
			
		for (unsigned int i=0; i<clusters.size(); i++){
			out_file<<"CLUSTER-"<<i<<" {centroid,";
			vector<Info_node> vec = clusters[i];
			vector<double> centroid =  vec[0].get_p();

			for(unsigned int x = 0; x <clusters[i].size(); x++){
				out_file<<clusters[i][x].get_itemID()<<", ";

			}
			out_file<<"}"<<endl; 
		}


	
	}

	if (silhouette_on_off == 1){

		double sum  = 0;
		vector<double> sil_2 = silhouette(clusters,data_dimension,e,metric_name,metric);
		out_file<<"Silhouette: [";
		cout<<"\n\n"<<endl;
		for(unsigned int i = 0 ; i < sil_2.size(); i++){
			out_file <<sil_2[i]<<",";
			cout <<sil_2[i]<<",";
			sum += sil_2[i];
		}
		double stotal = sum / sil_2.size();
		out_file<<stotal<<"]";

	}
}
