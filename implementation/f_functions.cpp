#include "f_functions.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <unistd.h>

int f_function(int h_p){
    int f;
    f = rand()%2;
    return f;
}

void initialize_vector_of_map(vector<map<int, int>>& pairs, int d){
     map<int, int> mp;
    for(int i=0; i<d; i++){
        pairs.push_back(mp);
    }
}

vector<int> f_p_hash_function(vector<double> &p, int new_dimension, vector<vector<double>>& v, vector<double>& t, int w, vector<map<int, int>>& pairs){
    initialize_vector_of_map(pairs, new_dimension);
    vector<int> bits; 
    int f;
    for(int i=0; i <new_dimension; i++){
        //cout<<"new_dimension = "<<new_dimension<<" v.size = "<<v.size()<<" t.size = "<<t.size()<<endl;

        int h_p = h_p_hash_function(p, v[i], t[i], w);
        if(exist_pair(pairs, i, h_p) == -1){ // if the pair does not exist insert into map
            f = f_function(h_p);
            //cout<<"f1 = "<<f<<endl;
            pairs[i].insert(pair<int, int>(h_p, f)); // insert the pair into pairs
            bits.push_back(f);
        }
        else { // if the pair exists
            f = exist_pair(pairs, i, h_p);
            bits.push_back(f);
            //cout<<"f2 = "<<f<<endl;

        }
    }
    /*  
    cout<<"exiting f_p"<<endl;
    print_vector(bits,bits.size());
    */
    cout<<"before returning birs"<<endl;
    return bits;
}

void print_map(vector<map<int, int>>& pairs){
    map<int, int>::iterator itr;
    int size = pairs.size();
    for(int i=0; i<size; i++){
        for (itr = pairs[i].begin(); itr !=pairs[i].end(); ++itr) {
            cout << itr->first << " " << itr->second << endl;
        }
        cout << endl;
    }
}

int exist_pair(vector<map<int, int>>& pairs, int ith, int element){
    map<int,int>::iterator it;
    it = pairs[ith].find(element);
    if (it == pairs[ith].end())
    {
        //cout << "key not found\n";
        return -1;
    }
    //cout << "key found" << endl;
    cout << it->first << " " << it->second << endl;
    return it->second; 
}

long long unsigned int binary_int_to_decimal_int(vector<int> n){
   long long unsigned int decimalNum, i, rem;
   decimalNum = 0;
   i = 0;
   int power = 0;
   //converting binary to decimal
   //cout <<"entering decimal" << endl;
   for(int i = n.size() -1 ; i >= 0; i--)
   {
      //rem = n[i] % 10;
      //n[i] /= 10;
      decimalNum += n[i] * pow(2, power);
      power++;
   }
   //cout <<"Returning binary int = " << decimalNum << endl;
   return decimalNum;
}

//return all neighbor buckets with hamming distance = 1 of hashed_q bucket //
vector <vector<int>> hypercube_neighbor_buckets(vector<int> &hashed_q, int number_of_neighbor_bukets, int new_dimension, vector<vector<double>>& v, vector<double>& t, int w, vector<map<int, int>>& pairs){
    vector <vector<int>> buckets;
    
    for(int i=0; i<new_dimension; i++){
        vector<int> neighbor = replace_digit(hashed_q, i, new_dimension);
        /*
        cout<<"pushing neighbor ";
        print_vector(neighbor,neighbor.size());
        cout<<" offf ";
        print_vector(hashed_q,hashed_q.size());
        */
        buckets.push_back(neighbor);
    }  


    //sleep(4);
    random_device generator;

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle ( buckets.begin(), buckets.end());
    return buckets;
}


/*Return all neighbor buckets of q  in 0101 (binary) form */
vector<vector<int>> return_buckets_for_hashing(vector<double> &q, int new_dimension,int probes, vector<vector<double>>& v, vector<double>& t, int w, vector<map<int, int>>& pairs){

    //cout <<"probes = " << probes<<"mew dimension = "<<new_dimension<<endl;
    vector<vector<int>> buckets;
    vector<vector<int>> buck;
    //print_vector(q,q.size());
    vector<int> hashed_q = f_p_hash_function(q, new_dimension, v, t, w, pairs); // hashed q. The function send us in a bucket like 0110101
    //cout<<"here"<<endl;
    buckets.push_back(hashed_q);
    int neighbor_buckets = 0;

    /*
    vector<vector<int>> buck =  hypercube_neighbor_buckets(hashed_q,probes,new_dimension,v, t, w, pairs);
    cout << "buck_size  = "<<buck.size()<<endl;    
    for (int i=0; i < buck.size(); i++){
        
        if(neighbor_buckets < probes ){
            buckets.push_back(buck[i]);
            neighbor_buckets++;

        }
    }
    buck.clear();
    cout <<"neighbor_buckets = "<<neighbor_buckets<<endl;
    */
    //cout <<"before goint"<<endl;
    int counter= 0;
    while(neighbor_buckets < probes){

        buck = hypercube_neighbor_buckets(buckets[counter],probes,new_dimension,v, t, w, pairs);
        for (int i=0; i < buck.size(); i++){
        
            if(neighbor_buckets < probes ){
                buckets.push_back(buck[i]);
                neighbor_buckets++;

            }
        
    }
    //cout <<"neighbor_buckets2 = "<<neighbor_buckets<<endl;
    buck.clear();
    counter++;
    
    }

    sort( buckets.begin(), buckets.end() );
    buckets.erase( unique( buckets.begin(), buckets.end() ), buckets.end() );


    return buckets;

}