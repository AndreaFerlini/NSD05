#include <iostream>
#include <queue>

#include "AdjacencyList.h"

int main() {

    AdjacencyList adjGraph;

    string filename = "../graphs/sample.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file ... " << endl;

    cout << "Loading graph ..." << endl;
    if (adjGraph.loadFromFile(filename, debug))
        return -1;

    adjGraph.print(debug);

/*
    // connect link all the nodes of the graph in the heap
    for (unsigned int i=1; i<=adjGraph.getNumNodes(); i++){
        minHeap.push(loadedGraph.nodes+i);
    }

    while (!minHeap.empty()){
        cout << *minHeap.top() << endl;
        minHeap.pop();
    }

    cout << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl;

*/
    return 0;
}