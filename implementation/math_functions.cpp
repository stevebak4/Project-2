#include "math_functions.h"
#include "hash_functions_h.h"

double normal_distribution_generator(void){

	random_device rd{};
    mt19937 gen{rd()};

	normal_distribution<double> d{0,1};

	map<int, int> hist{};

	return round(d(gen));

}

long long int modulo(long long int a, long long int b){

	return (a % b + b) %b;
	
}

double euclidean_distance(ifstream& inputFileStream1, int line1, ifstream& inputFileStream2, int line2){
	long unsigned int dimension = data_dimension_without_id(inputFileStream1); // get dimension of vector
	string str1 = get_specific_line(line1, inputFileStream1); // first data
	string str2 = get_specific_line(line2, inputFileStream2); // second data
	/* convert str1 to vector */
	vector<double> vec1 = string_of_integers_to_vector(str1);
	/* convert str2 to vector */
	vector<double> vec2 = string_of_integers_to_vector(str2);
	/* calculate euclidean distance */
	//cout<<"str1 = "<<str1<<endl;
	//cout<<"str2 = "<<str2<<endl;

	print_vector(vec1,vec1.size());
	print_vector(vec1,vec1.size());

	double distance;
	long double diff;
	long double sum = 0;
	int i;
	//cout<<"inside euclidean distance"<<endl;
	//cout<<"dimension = "<<dimension<<" vec1_dim = "<<vec1.size()<<"vec2_dim =  "<<vec2.size()<<endl;
	for( i=0; i < dimension; i++ ){
		diff = vec1[i] - vec2[i];
		long double squared_diff = pow (diff, 2);
		sum = sum + squared_diff;
	}
	distance = sqrt(sum);
	//cout<<"returning euclidean distance"<<endl;
	return distance;
}

/*Calculate euclidean distance between two vectors*/

double euclidean_distance_2(vector<double> vec1,vector<double> vec2){


    long unsigned int dimension = vec1.size();
	long double distance;
	long double diff;
	long double sum = 0;
	int i;
	for( i=0; i < dimension; i++ ){
		diff = vec1[i] - vec2[i];
		long double squared_diff = pow (diff, 2);
		sum = sum + squared_diff;
	}
	distance = sqrt(sum);
	return distance;
}


double euclidean_distance_2(vector<double> vec1,vector<double> vec2,int data_dimension){  //the third argument is a dummy argument


    long unsigned int dimension = vec1.size();
	long double distance;
	long double diff;
	long double sum = 0;
	int i;
	for( i=0; i < dimension; i++ ){
		diff = vec1[i] - vec2[i];
		long double squared_diff = pow (diff, 2);
		sum = sum + squared_diff;
	}
	distance = sqrt(sum);
	return distance;
}


vector<double> string_of_integers_to_vector(string str){
	stringstream iss( str );
	double number;
	string s;
	vector<double> vec;
	iss >> s;
	while ( iss >> number )
		vec.push_back( number );		
	print_vector(vec, vec.size());
	return vec;
}


vector<double> string_of_integers_to_vector_add_time(string str){
	stringstream iss( str );
	double number;
	string s;
	vector<double> vec;
	iss >> s;
	int i = 1;
	while ( iss >> number ){
		vec.push_back(i);
		vec.push_back( number );
		i++;
	}			
	//print_vector(vec, vec.size());
	return vec;
}

double dot_product(vector<double> p, vector<double> v) {
	int size = p.size();
	long double product = 0;
	for (int i = 0; i < size; i++)
		product = product + p[i] * v[i];
	return product;
}

int random_number_generator(int k){
	int rand_num;
	rand_num = rand() % k;
	return rand_num;
}

unsigned int bits_concatenation(vector<int> bits){
    int s = bits.size();
	ostringstream oss;

	for(int i=0; i<s; i++){
		oss << bits[i];
	}
    istringstream iss(oss.str());
    unsigned int c;

    iss >> c;
    return c;
}

int hamming_distance(int number1, int number2){
    int x = number1 ^ number2;
    int hd = 0;
 
    while (x > 0) {
        hd += x & 1;
        x >>= 1;
    }
    return hd;
}

vector<int> split_integer_digits(int num){
	vector<int> digits;
	while(num > 0) //do till num greater than  0
    {
        int mod = num % 10;  //split last digit from number
		digits.push_back(mod);
        //printf("%d\n",mod); //print the digit.    
        num = num / 10;    //divide num by 10. 
    }
	return digits;
}

vector<int> replace_digit(vector<int> &num, int digits_place, int new_dimension){
	unsigned int replaced_num;
	vector<int> digits = num;
	if (digits.size() < new_dimension){
		int p = new_dimension - digits.size();
		for (int i=0; i<p; i++){
			digits.push_back(0);
		}
	}
	int flag = 3;
	// cout << digits[0] << endl;
	if (digits[digits_place] == 0){
		flag = 0;
		// digits[digits_place] = 1;
	}
	if (digits[digits_place] == 1){
		flag = 1;
		// digits[digits_place] = 0;
	}
	if (flag == 0){
		digits[digits_place] = 1;
	}
	if (flag == 1){
		digits[digits_place] = 0;
	}
	//reverse(digits.begin(), digits.end());
	//replaced_num = bits_concatenation(digits);
	return digits;
}








