#include <iostream>
#include <queue>

#include "loadgraph.h"

int main() {

    AdjacencyList loadedGraph;

    string filename = "../graphs/sample.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file ... " << endl;

    cout << "Loading graph ..." << endl;
    if (loadAdjList(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print(debug);

    priority_queue<Node*,vector<Node*>, LessByDegree> minHeap;

    // connect link all the nodes of the graph in the heap
    for (unsigned int i=1; i<=loadedGraph.num_nodes; i++){
        minHeap.push(loadedGraph.nodes+i);
    }

    while (!minHeap.empty()){
        cout << *minHeap.top() << endl;
        minHeap.pop();
    }

    cout << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl;


    return 0;
}