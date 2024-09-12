#include "btree_node.h"



btree_node *btree_create_node(btree_node *node){

    node = new btree_node;
    node->left = NULL;
    node->right = NULL;

    return node;
}


btree_node *btree_create_and_fill(btree_node *root,int height,int current_height,int i,int data_dimension,vector<Info_node> cluster){   //current height must be = 0 at the beggining

    cout<<"height = "<<height<<" ,current_height = "<<current_height<<" ,i = "<<i<<" ,data_dimension>> = "<<data_dimension<<endl;
    if (current_height < height){

        btree_node *temp = btree_create_node(temp);

        root = temp;
        root->left = btree_create_and_fill(root->left,height,current_height+1,(2*i),data_dimension,cluster);
        root->right = btree_create_and_fill(root->right,height,current_height+1,(2*i+1),data_dimension,cluster);

    }else if (current_height == height){
        if( i < cluster.size() ){

            btree_node *temp = btree_create_node(temp);
            temp->p = cluster[i].get_p();   
            root = temp;
        }
    }

    return root;
}


void print_postorder(btree_node *root)
{
    if (root != NULL)
    {
        root->print();
        print_postorder(root->left);
        print_postorder(root->right);
    }
}


void btree_delete(btree_node *root)
{
    if (root == NULL)
        return;
    if(root->p.size() != 0){    
        cout<<"deleting node ";
        root->print();
    }    
    btree_delete(root->left);
    btree_delete(root->right);

    delete root;
    
}