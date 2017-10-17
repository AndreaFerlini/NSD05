#include <iostream>

#include "loadgraph.h"


int main() {

    AdjacencyList loadedGraph;

    string filename = "../graphs/sample.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good())
        cout << "[ERROR] main.cpp: no such file " << filename << endl;

    cout << endl << "main.cpp: loading graph" << endl << endl;
    if (loadAdjListContiguous(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print();

    return 0;
}