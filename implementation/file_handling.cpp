#include "file_handling.h"
#include "math_functions.h"

long unsigned int number_of_file_lines(ifstream& inputFileStream){
    long unsigned int lines=0;
    string get_each_line;
    while( getline(inputFileStream,get_each_line) ) 
    {
        //cout << get_each_line <<endl;
        lines = lines +1;
    }  

    inputFileStream.clear();
	inputFileStream.seekg(0,ios::beg);     
    return lines;
}

void open_file(string file_name, ifstream& inputFileStream){
    inputFileStream.open(file_name, ios::in);
	if (!inputFileStream) {
		cout << "No such file" << endl;
        exit(-1);
	}else
        cout << "File opened successfully!" << endl;
}

void open_file(string file_name, ofstream& inputFileStream){
    inputFileStream.open(file_name, std::ios_base::app);
	if (!inputFileStream) {
		cout << "No such file" << endl;
        exit(-1);
	}else
        cout << "File opened successfully!" << endl;
}


void close_file(ifstream& inputFileStream){
    if(inputFileStream.is_open()) {  
        inputFileStream.close(); //file close  
        cout<<"File closed successfully."<<endl;  
    }  
}

void close_file(ofstream& inputFileStream){
    if(inputFileStream.is_open()) {  
        inputFileStream.close(); //file close  
        cout<<"File closed successfully."<<endl;  
    }  
}

long unsigned int data_dimension_with_id(ifstream& inputFileStream){
    long unsigned int dimension = 0;
    int i = 0;
    int state = 0;

    string line;

	getline(inputFileStream, line);
    //cout << line << endl;
    while (i < line.length())
        {
            /* If next character is a separator, set the 
               state as zero */
            if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
            {
                state = 0;

            }                
            /* If next character is not a word separator
               and state is 0, then set the state as 1
               and increment dimension */
            else if (state == 0)
            {
                state = 1;
                dimension = dimension + 1;
            }      
            // Move to next character
            ++i;
        }
    
    inputFileStream.clear();
	inputFileStream.seekg(0,ios::beg); 
    return dimension;
}

long unsigned int data_dimension_without_id(ifstream& inputFileStream){
    long unsigned int dimension = 0;
    int i = 0;
    int state = 0;

    string line;

	getline(inputFileStream, line);
    //cout << line << endl;
    while (i < line.length())
        {
            /* If next character is a separator, set the 
               state as zero */
            if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
            {
                state = 0;

            }                
            /* If next character is not a word separator
               and state is 0, then set the state as 1
               and increment dimension */
            else if (state == 0)
            {
                state = 1;
                dimension = dimension + 1;
            }      
            // Move to next character
            ++i;
        }
    
    inputFileStream.clear();
	inputFileStream.seekg(0,ios::beg); 
    return dimension -1;
}

string get_specific_line(long int line_num, ifstream& inputFileStream){
    string line;
	inputFileStream.clear();
	inputFileStream.seekg(0,ios::beg);
	for(int i=0; i<line_num; i++) 
        getline(inputFileStream, line);
    inputFileStream.clear();
	inputFileStream.seekg(0,ios::beg);
    return line;
}

void move_to_specific_line(long int line_num, ifstream& inputFileStream){
	string line;
	inputFileStream.clear();
	inputFileStream.seekg(0,ios::beg);
	for(int i=1; i<=line_num; i++) 
        getline(inputFileStream, line);
    //inputFileStream.clear();
	//inputFileStream.seekg(0,ios::beg);
    cout << "You are at line " << line_num << "with content: " << line << endl;
}



vector<vector<double>> make_query_vector(ifstream& q_file,vector<string> &ids,bool fill_curve){

    long unsigned int n = number_of_file_lines(q_file);
	//cout << "number of lines= " << n << endl;
	long unsigned int dimension = data_dimension_without_id(q_file);
	//cout << "data dimension= " << dimension << endl;

    vector<vector<double>> querys;
    vector<double> vec_p_to_hash;

    for (int line=1; line<=n; line++){ // for every p
		//cout << "line now= " << line << endl;

		/* get the string that will be hashed.  */
	 	string str_p_to_hash = get_specific_line(line, q_file);
		/* convert it to vector without the first number which is the id */
		if (fill_curve == 1)
           vec_p_to_hash = string_of_integers_to_vector_add_time(str_p_to_hash); // without id in it
		else 
            vec_p_to_hash = string_of_integers_to_vector(str_p_to_hash); // without id in it

        string item_id;
		stringstream iss( str_p_to_hash );
		iss >> item_id;
		ids.push_back(item_id);
        
        
        querys.push_back(vec_p_to_hash);

    }

    return querys;


}




