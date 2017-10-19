#include <iostream>
#include <queue>

#include "DecomposableGraph.h"

int main() {

    AdjacencyList adjGraph;

    string filename = "../graphs/sample.graph";
    bool debug = true;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file ... " << endl;
/*
    cout << "Loading graph ..." << endl;
    if (adjGraph.loadFromFile(filename, debug))
        return -1;

    adjGraph.print(debug);
*/

    DecomposableGraph decGraph(filename, debug);

    decGraph.print(debug);
    decGraph.flushHeap(debug);

    cout << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl << "Size of unsigned int: " << sizeof(unsigned int);
    cout << endl;

    return 0;
}