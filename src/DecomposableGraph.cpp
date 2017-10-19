//
// Created by Luca De Mori on 18/10/2017.
//

#include "DecomposableGraph.h"

DecomposableGraph::DecomposableGraph(string filename, bool debug): AdjacencyList(filename, debug) {
    this->makeHeap();
    cout << "[DecomposableGraph] Graph loaded and heap successfully created!";
}

void DecomposableGraph::makeHeap() {
    // connect link all the nodes of the graph in the heap
    for (unsigned int i=1; i<=this->num_nodes; i++){
        nodesHeap.push(this->nodes+i);
    }
}

void DecomposableGraph::flushHeap(bool debug) {
    while (!this->nodesHeap.empty()){
        if (debug) cout << *(this->nodesHeap.top()) << endl;
        this->nodesHeap.pop();
    }
}