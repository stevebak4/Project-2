#include "user_input_handling2.h"
#include <cstring>

void search_input(int argc, char* argv[], char** input_file, char** query_file, int* k, int* L, long int* M, int* probes, char** output_file, char** LSH_Hypercube_or_Frechet, char** discrete_or_continuous, double* delta){
	int have_k = 0;
	/* give default arguments */
	*L = 5;
	*M = 10;
	*probes = 2;

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
			have_k = 1;
			cout << "k is: " << *k << endl;
		}
		if (!strcmp(argv[i], "-L")) {
			*L = atoi(argv[++i]);
			cout << "L is: " << *L << endl;
		}
		if (!strcmp(argv[i], "-M")) {
			*M = atoi(argv[++i]);
			cout << "M is: " << *M << endl;
		}
		if (!strcmp(argv[i], "-probes")) {
			*probes = atoi(argv[++i]);
			cout << "Probes is: " << *probes << endl;
		}
		if (!strcmp(argv[i], "-o")) {
			*output_file = strdup(argv[++i]);
			cout << "Output file is: " << *output_file << endl;
		}
		if (!strcmp(argv[i], "-algorithm")) {
			*LSH_Hypercube_or_Frechet = strdup(argv[++i]);
			/* give default argument k */
			if (!strcmp(*LSH_Hypercube_or_Frechet, "LSH") && have_k == 0){
				*k = 4; 
			}
			if (!strcmp(*LSH_Hypercube_or_Frechet, "Frechet") && have_k == 0){
				*k = 4; 
			}
			if (!strcmp(*LSH_Hypercube_or_Frechet, "Hypercube") && have_k == 0){
				*k = 14; 
			}
			cout << "LSH_Hypercube_or_Frechet is: " << *LSH_Hypercube_or_Frechet << endl;
		}
		if (!strcmp(argv[i], "-metric")) {
			*discrete_or_continuous = strdup(argv[++i]);
			cout << "discrete_or_continuous is: " << *discrete_or_continuous << endl;
		}
		if (!strcmp(argv[i], "-delta")) {
			*delta = atof(argv[++i]);
			cout << "delta is: " << *delta << endl;
		}
	}

}

void cluster_input(int argc, char* argv[], char** input_file, char** configuration_file, char** output_file, char** mean_frechet_or_vector, char** classic_LSH_or_hypercube, bool* complete, bool* silhouette){
    /* give default arguments */
	*complete = false;
    *silhouette = false;
	char *str1 = NULL;
	char *str2 = NULL;

	for (int i = 1; i < argc; i++) { // for every user input
		//cout<<argv[i]<<endl;
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
        if (!strcmp(argv[i], "-update")) {
			str1 = strdup(argv[++i]);
			str2 = strdup(argv[++i]);
			*mean_frechet_or_vector = new char[strlen(str1) + strlen(str2) +2];
			strcat(*mean_frechet_or_vector, str1);
			strcat(*mean_frechet_or_vector," ");
			strcat(*mean_frechet_or_vector, str2);
			delete str1;
			delete str2;


			cout << "mean_frechet_or_vector is: " << *mean_frechet_or_vector << endl;
		}
        if (!strcmp(argv[i], "-assignment")) {
			*classic_LSH_or_hypercube = strdup(argv[++i]);
			cout << "classic_LSH_or_hypercube is: " << *classic_LSH_or_hypercube << endl;
		}
		if (!strcmp(argv[i], "-complete")) {
			*complete = true;
		}
        if (!strcmp(argv[i], "-silhouette")) {
			*silhouette = true;
		}
	}
	
	/* Assert with message if a file name was not given */
	assertm(*input_file && *configuration_file && *output_file && *mean_frechet_or_vector && *classic_LSH_or_hypercube, "Please give input file name, configuration file name, output file name, mean frechet or mean vector and classic, LSH or hypercube!");
}