#include <iostream>
#include <queue>

#include "DecomposableGraph.h"

//#include "MinHeap.h"
int main() {



    //string filename = "../graphs/com-youtube.ungraph.graph";
    string filename = "../graphs/sample.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good()) {
        cout << "[ERROR] - main(): No such file ... " << endl;
        exit(0);
    }


/*
    AdjacencyList loadedGraph;

    loadedGraph.loadFromFile(filename, false);

    loadedGraph.print(false);


    MinHeap heap(loadedGraph.getNumNodes());
    heap.make_heap(loadedGraph.nodes+1);
    heap.print_container();
    heap.flush_heap();
    heap.print_container();
*/


    cout << "[EXECUTION] - main(): loading decomposable graph..." << endl;
    DecomposableGraph decGraph(filename, debug);
    cout << "[EXECUTION] - main(): done! decomposing graph..." << endl;


/*
    cout << "[EXECTUION] - main(): printing heap container..." << endl;
    decGraph.print_minHeap_container();

    cout << "[EXECTUION] - main(): flushing heap..." << endl;
    decGraph.flush_minHeap();


    decGraph.print_minHeap_container();
*/

    //decGraph.heapTest();

/*  ES 2
    decGraph.decomposeGraph(debug);


    if (decGraph.isDecomposed()){
        cout << endl << "[EXECUTION] - main(): done! finding densest prefix..." << endl;
    } else {
        cout << endl << "[ERROR] - main(): Not decomposed. Aborting..." << endl;
        return -1;
    }


    decGraph.findDensestPrefix(debug);
    cout << "[EXECUTION] - main(): done! output:" << endl;
    decGraph.densest_prefix.print();
    decGraph.print_prefix(decGraph.densest_prefix.size);

    cout << endl;

    cout << "[EXECUTION] - main(): done! writing file to plot..." << endl;
    decGraph.writeCorenessDegreeFile("../plots/sample.out", debug);
*/

/*
 * ES 3
 * */

    decGraph.findDensityFriendlyDensestPrefix(false);

/*
    cout << endl << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl << "Size of unsigned int: " << sizeof(unsigned int);
    cout << endl << "Size of float: " << sizeof(float);
*/

    return 0;
}