#ifndef EDGE_H
#define EDGE_H

#include <vector>
using namespace std;

#pragma once

class Edge
{
public:
    int u;
    int v;
    double w;

    Edge(int src, int dest, double wey) {
    this->u = src;
    this->v = dest;
    this->w = wey;
 }
    
   

};

#endif