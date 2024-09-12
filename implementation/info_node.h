#ifndef INFO_NODE_H
#define INFO_NODE_H


#include <float.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <map>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cmath>


using namespace std;

class Info_node {
    
    private:
        
        double distance;
        string itemID;
        vector<double> p;

    public:
        
        Info_node(vector<double> point,double dist,string item_id) : p(point),distance(dist),itemID(item_id) {
            /*
            cout<<"Info_node created witn distance = "<<dist<<" itemID = "<<itemID<<" and point = ";
            for (auto i: p)
                std::cout << i << ' ';
            
            cout<<endl;    
            */
        }

        ~Info_node() {}

        double get_distance() const { return distance; }
        void set_distance(double dist) { distance = dist; }
       
        void set_itemID(string item_id) { itemID = item_id; }
        string get_itemID() const { return itemID; }

        vector<double> get_p() const { return p; }
        void set_p(vector<double> point) { p = point;}
        
        void print(){

            cout<<"Info_node distance = "<< distance<<" itemID = "<< itemID<<" and point = ";
            
            for(unsigned int i=0; i<p.size(); i++)
		        cout << p[i] << " ";
            cout<<endl;   

        }
};


#endif