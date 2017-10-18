#include <iostream>

#include "loadgraph.h"

#include <queue>
#include <vector>


int main() {

    AdjacencyList loadedGraph;
    priority_queue <Node*, vector<Node*>, Node > minHeap;

    string filename = "../graphs/sample.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good())
        cout << "[ERROR] main.cpp: no such file " << filename << endl;

    cout << endl << "main.cpp: loading graph" << endl << endl;
    if (loadAdjListContiguous(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print();

    for (unsigned int i=1; i < loadedGraph.num_nodes+1; i++){

        minHeap.push(&loadedGraph.nodes[i]);

        if (debug)
            cout << "[TEST] " << loadedGraph.nodes[i] << endl;
    }

    if (debug)
        cout << "[TEST] " << *minHeap.top() << endl;


    return 0;
}