#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <random>
#include <vector>
#include <time.h>
#include "Graph.h"
#include "Node.h"


using namespace std;

int main() {

cout << "Please enter the name of the text file of the input graph you will be using: ";
string graphtextfile;
std::getline(cin, graphtextfile);


    


    std::ifstream File(graphtextfile);  // Attempt to open the file with user input
    if (!File.is_open()) {  // Check if the file stream is in a good state
        std::cout << "Unable to open file: " << graphtextfile << "\n";
        return 1;
    }

cout << "Graph file has been aquired successfully and will now be read in.... \n";

    string firstLine;
    getline(File, firstLine);  
    istringstream read(firstLine);
    int numofvertices;
    Graph *firstTry = nullptr;
    if (read >> numofvertices) {
        firstTry = new Graph(numofvertices); // use first line to set up graph using num of vertices
       
    }

    
    string line;
    int edgecount = 0;
    while (getline(File, line)) {
        istringstream read(line);
        int vertex;
        int neighbor;                       ////Read in each line and add to the graph
        double weight;
        

        if (read >> vertex >> neighbor >> weight) {         
            
            
            firstTry->addEdge(vertex, neighbor, weight);     
            
            
            
            
        }
    }


cout << "Graph has been read in... \n";

File.close();



cout << "Checking for cycle...\n";
int typeofalgorithm;

    
    if (firstTry->isCyclic()) {
        cout << "Graph contains a cycle. Cannot run DAG SP \n"; 
        if(firstTry->checkNegativeEdges()) {
        cout << "Graph has negative weights, running Bellman Ford(As long as there is no negative cycle)";
        typeofalgorithm = 2;  
        }
        else {
            cout << "Graph has no negative weights, running Dijkstra";
            typeofalgorithm = 1;
        }  
    }
    else {
        cout << "Running DAG SP, does not contain cycle \n";
        typeofalgorithm= 0;                                                 //set to 0 for switch statement to run DAGSP
    }



int source;
int dest;
double newdest;
double duration;
clock_t start;
clock_t end;
switch(typeofalgorithm) {
    case(0):                                                                                    //CASE 0, DAGSP

    cout << endl << "Now please enter the integer of the source node: ";
    

    cin >> source;

    cout << "Thank you, now please enter the integer of the destination node: ";
    
    cin >> dest;
     start = clock();
    firstTry->DAGSP(source, dest);
     end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;            //show time 
    cout << "\n Time taken by function: " << duration << " seconds";

    cout << "Enter another destination node or enter -1 to end the program: ";
    
    cin >> newdest;
    while(newdest != -1) {
     start = clock();
    firstTry->DAGSP(source, newdest);
     end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;            //show time 
    cout << "\n Time taken by function: " << duration << " seconds" << endl;
    cout << "Enter another destination node or enter -1 to end the program: ";    
    cin >> newdest;
    }
    
    cout << "Ending program...\n";
    break;
    

    case(1):
                                                                             //CASE 1, DIJKSTRA
    cout << endl << "Now please enter the integer of the source node: ";
    

    cin >> source;



    cout << "Thank you, now please enter the integer of the destination node: ";
    
    cin >> dest;
    
    start = clock();
    firstTry->dijkstra(source, dest);
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;            //show time 
    cout << "\n Time taken by function: " << duration << " seconds" << endl;

    cout << "Enter another destination node or enter -1 to end the program: ";
    
    cin >> newdest;
    while(newdest != -1) {
    start = clock();
    firstTry->dijkstra(source, newdest);
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;            //show time 
    cout << "\n Time taken by function: " << duration << " seconds" << endl;
    cout << "Enter another destination node or enter -1 to end the program: ";    
    cin >> newdest;
    }
    
    cout << "Ending program...\n";
    break;

    case(2):
                                                                                                    //CASE 2 BELLMAN
    cout << endl << "Now please enter the integer of the source node: ";
    

    cin >> source;



    cout << "Thank you, now please enter the integer of the destination node: ";
    
    cin >> dest;
     start = clock();
    firstTry->bellmanFord(source, dest);
     end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;            //show time 
    cout << "\n Time taken by function: " << duration << " seconds";

    cout << "Enter another destination node or enter -1 to end the program: ";
    
    cin >> newdest;
    while(newdest != -1) {
    start = clock();
    firstTry->bellmanFord(source, newdest);
     end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;            //show time 
    cout << "\n Time taken by function: " << duration << " seconds" << endl;
    cout << "Enter another destination node or enter -1 to end the program: ";    
    cin >> newdest;
    }
    
    cout << "Ending program...\n";
    break;
}







    return 0;
}