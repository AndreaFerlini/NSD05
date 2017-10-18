//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include <queue>


// TODO: agree on structure, methods, and everything...
class DecomposableGraph : public AdjacencyList {
public:
    DecomposableGraph();
    ~DecomposableGraph();


private:
    priority_queue<Node*,vector<Node*>, Node::LessByDegree> minHeap;


    void makeHeap();
    void decomposeGraph();



};


#endif //NSD05_DECOMPOSABLEGRAPH_H
