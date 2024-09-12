#include "user_input_functions.h"

void ask_user_for_dataset_file_path(ifstream& inputFileStream){
    string path;
    cout << "Please give the dataset file path." << endl;
    cin >> path;
    open_file2(path, inputFileStream);
}

void ask_user_for_query_and_output_file_path(ifstream& queryFileStream, char** output_file){
    *output_file = new char[100];
    string path1;
    cout << "Please give the query file path." << endl;
    cin >> path1;
    open_file2(path1, queryFileStream);
    cout << "Please give the output file path." << endl;
    cin >> *output_file;  
    //*output_file = strdup(*output_file);
}


char* ask_user_for_algorithm(char** algorithm){
    *algorithm = new char[100];
    cout << "Please give the algorithm name you want to use." << endl;
    cin >> *algorithm;
    return *algorithm;
}

void ask_user_for_metric(char** metric){
    *metric = new char[100];
    cout << "Please give the metric name you want to use." << endl;
    cin >> *metric;
}

int ask_user_continue_or_exit(){
    int ce;
    cout << "If you want to continue press 1 and if you want to exit press 0." << endl;
    cin >> ce;
    return ce;
}

void open_file2(string file_name, ifstream& inputFileStream){
    inputFileStream.open(file_name, ios::in);
	if (!inputFileStream) {
		cout << "No such file" << endl;
        exit(-1);
	}else
        cout << "File opened successfully!" << endl;
}
