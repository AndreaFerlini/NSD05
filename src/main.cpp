#include <iostream>

#include "loadgraph.h"


int main() {

    AdjacencyList loadedGraph;

    string filename = "../graphs/sample.graph";
    bool debug = true;
    bool is_weighted = false;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file ... " << endl;

    cout << "Loading graph ..." << endl;
    if (loadAdjList(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print(debug);




    return 0;
}