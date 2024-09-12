#ifndef BUCKET_NODE_H
#define BUCKET_NODE_H


#include <vector>
#include <iostream>



using namespace std;



class Bucket_node {
    
    private:
        
        long long int ID;
        string itemID;
        vector<double> p;

    public:
        
        Bucket_node(vector<double> point,long long int id,string item_id) : p(point),ID(id),itemID(item_id) {
            /*
            cout<<"Bucket_node created witn ID = "<< ID<<" itemiD = "<<itemID <<" and point = ";
            
            for(unsigned int i=0; i<p.size(); i++)
		        cout << p[i] << " ";
            cout<<endl;    
            */
        }

        ~Bucket_node() {}

        long long int get_ID() const { return ID; }
        string get_itemID() const { return itemID; }

        void set_ID(long long int id) { ID = id; }
        void set_itemID(string item_id) { itemID = item_id; }


        vector<double> get_p() const { return p; }
        void set_p(vector <double> point) { p = point;}

        vector<double> *get_p_address()  {return &p;}

        void print(){

            cout<<"Bucket_node ID = "<< ID <<" itemID = "<< itemID<<" and point = ";
            
            for(unsigned int i=0; i<p.size(); i++)
		        cout << p[i] << " ";
            cout<<endl;   

        }
        
};

#endif