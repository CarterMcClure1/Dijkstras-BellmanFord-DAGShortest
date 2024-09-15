#ifndef NODE_H
#define NODE_H
#include <vector>
#include "Edge.h"




class Node {
public:
int nodeID;
int distance=0; //for dijkstras
double key;
Node* parent;
bool visited;


vector<Edge> list;


Node(int ID) {
this->nodeID = ID;

} 



 // min priority queue compare
   bool operator<(const Node& node2) const {
       return key > node2.key; // Change to < for min priority
    }

    
   bool operator>(const Node& node2) const {
        return key < node2.key; // Change to > for max priority(currently at max priority)
    }
 
    //TO CHANGE TO MIN, change > to < in heapify function when comparing keys.
};


#endif
