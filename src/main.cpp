#include <iostream>

#include "loadgraph.h"
#include "kdecomposition.h"

int main() {

    AdjacencyList loadedGraph;

    string filename = "../graphs/sample.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good())
        cout << "[ERROR] main.cpp: no such file " << filename << endl;

    cout << endl << "main.cpp: loading graph and computing the k-core decomposition" << endl << endl;
    computeKCoreDecomposition(loadedGraph, filename, true);

    if (debug){
        loadedGraph.print();
    }

    return 0;
}