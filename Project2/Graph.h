#include "Node.h"
#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <list>
#include <queue>
#include <algorithm>

class Graph {
public: 
int V; 
list<pair<int, int>> *adj; 

Graph(int V) {
    this->V = V;
    adj = new list<pair<int, int>>[V];          //set up adj list
}

void addEdge(int u, int v, int weight) {            //add edge to adj list
        adj[u].push_back(make_pair(v, weight));
    }       

    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack) {
        visited[v] = true;

        for(auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if(!visited[i->first]) {
                topologicalSortUtil(i->first, visited, Stack);
            }
        }
        Stack.push(v);
    }



    bool isCyclicUtil(int v, bool visited[], bool *recStack) {
    if (!visited[v]) {
        visited[v] = true;          //if vertex not visited, mark as visited
        recStack[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[i->first] && isCyclicUtil(i->first, visited, recStack)) {      //Recursive call for all adjacent vertices to curr vertex
                return true;
            } else if (recStack[i->first]) {
                return true;
            }
        }
    }
    recStack[v] = false; // Remove the vertex from recursion stack
    return false;
}

bool isCyclic() {
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;             //initialize all vertices as unvisited and not in stack
        recStack[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (isCyclicUtil(i, visited, recStack)) {           //detect cyclces
            delete[] visited;
            delete[] recStack;
            return true;
        }
    }

    delete[] visited;
    delete[] recStack;          //free memory
    return false;
}

bool checkNegativeEdges() {
    for (int u = 0; u < V; u++) {
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            if (i->second < 0) {                                            //go through each vertex and its adj edges to see if value is negative
                return true;
            }
        }
    }
    return false;
}

bool checkNegativeWeightCycle(vector<double> &dist) {
    // Iterate over all edges
    for (int u = 0; u < V; u++) {
        for (auto j = adj[u].begin(); j != adj[u].end(); ++j) {
            int v = j->first; // Neighbor vertex
            double weight = j->second; // Weight of the edge u-v

            // If a shorter path is found, a negative-weight cycle exists
            if (dist[u] != numeric_limits<double>::max() && dist[u] + weight < dist[v]) {
                return true;
            }
        }
    }
    return false;
}

void DAGSP(int s, int d) {
    stack<int> Stack;
    vector<double> dist(V, numeric_limits<double>::max());
    vector<int> pred(V, -1); 

    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;                     // Initialize all vertices as unvisited
    }

    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, Stack);       // Perform topological sort on all vertices
        }
    }

    dist[s] = 0; // Distance to source vertex is 0

  
    while (!Stack.empty()) {
        int u = Stack.top();            // Get the next vertex from topological order
        Stack.pop();

        if (dist[u] != numeric_limits<int>::max()) {
            for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = i->first;
                double weight = i->second;

                                                                        // Relax edge if a shorter path is found
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pred[v] = u; 
                }
            }
        }
    }

                                                                            // Check if there is a path to the destination
    if (dist[d] >= 100000000) {
        cout << "There is no path from " << s << " to " << d << endl;
    } else {
        cout << "The shortest path from " << s << " to " << d << " is " << dist[d] << endl;

                                                                            // Reconstruct the path from s to d using predecessor vector
        vector<int> path;
        for (int v = d; v != -1; v = pred[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    delete[] visited;
}




void dijkstra(int src, int dest) {
    priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;
    vector<double> dist(V, numeric_limits<double>::max());
    vector<int> pred(V, -1); 

    pq.push(make_pair(src, 0));     //push source node into PQ
    dist[src] = 0;                  

    while (!pq.empty()) {
        int u = pq.top().first;     //Get smallest distance vertex and pop from queue
        pq.pop();

        
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = i->first;
            double weight = i->second;

                                                    //calculate adjacent vertices distances from popped vertex
            if (dist[v] > dist[u] + weight) {       //also relax edges if distance is smaller now
                dist[v] = dist[u] + weight;         
                pq.push(make_pair(v, dist[v]));
                pred[v] = u; 
            }
        }
    }

    if (dist[dest] == numeric_limits<double>::max()) {
        cout << "There is no path from " << src << " to " << dest << endl;
    } else {
        cout << "The shortest path from " << src << " to " << dest << " is " << dist[dest] << endl;

        
        vector<int> path;
        for (int v = dest; v != -1; v = pred[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());          //get path of nodes by reconstructing using predecessor vector

        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}


   
 void bellmanFord(int src, int dest) {
    vector<double> dist(V, numeric_limits<double>::max()); 
    vector<int> pred(V, -1); 

    dist[src] = 0;  

                                                                
    for (int i = 1; i <= V - 1; i++) {
       
        for (int u = 0; u < V; u++) {
            
            for (auto j = adj[u].begin(); j != adj[u].end(); ++j) {
                int v = j->first; 
                double weight = j->second;                                          //Relaxes all vertices for V-1 iterations
                                                                                    //Goes through each vertex per iteration, and relaxes edges if possible
                
                if (dist[u] != numeric_limits<double>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight; 
                    pred[v] = u; 
                }
            }
        }
    }

                                                                        // Check for negative-weight cycles
    if (checkNegativeWeightCycle(dist)) {
        cout << "Graph contains negative weight cycle" << endl;
        return;
    }

   
    if (dist[dest] == numeric_limits<double>::max()) {
        cout << "There is no path from " << src << " to " << dest << endl;
    } else {
        cout << "The shortest path from " << src << " to " << dest << " is " << dist[dest] << endl;

                                                                //Reconstruct path from predecessor vector
        vector<int> path;
        for (int v = dest; v != -1; v = pred[v]) {
            path.push_back(v); 
        }
        reverse(path.begin(), path.end());

       
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}   
    
    
    
    
                                            
    


};