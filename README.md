# Dijkstras-BellmanFord-DAGShortest
This C++ program takes in a graph file and then determines which of three algorithms(Dijkstras, Bellman Ford, or DAG shortest path) it should run to visit all nodes in the shortest time possible.


Run main.cpp, it will prompt you to enter the name of the edgelist file, then it will determine which algorithm to use. If there is a cycle in the graph and has negative edges, it will run Bellman Ford. If it has a cycle and no negative edges, it will run Dijkstra. If it does not contain a cycle, it will run DAG SP
