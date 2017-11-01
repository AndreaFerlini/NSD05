#include <iostream>
#include <queue>

#include "DecomposableGraph.h"

//#include "MinHeap.h"
int main() {


    int start = (int)time(nullptr);


    //string filename = "../graphs/com-youtube.ungraph.graph";
    string filename = "../graphs/course5.graph",
            outputfilename = "../plots/course5.out",
            rankfilename = "../plots/course5.rnk";

    bool debug = false;

    ifstream file(filename);
    if (!file.good()) {
        cout << time(nullptr)-start << "s: " <<  "[ERROR] - main(): No such file ... " << endl;
        exit(0);
    }

    /// LOAD ADJLIST, MEASURE FILE
    /*
    cout << time(nullptr)-start << "    create AdjList... "  << endl;
    AdjacencyList loadedGraph;

    cout << time(nullptr)-start << "    load from file... "  << endl;
    loadedGraph.loadFromFile(filename, false);

    cout << time(nullptr)-start << "    done!"  << endl;
    cout << "nodes: " << loadedGraph.getNumNodes() << endl
         << "edges: " << loadedGraph.getNumEdges() << endl;
*/

    /// LOAD DECOMPOSABLE GRAPH

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): loading decomposable graph..." << endl;
    DecomposableGraph decGraph(filename, debug);
    //decGraph.print(debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done! decomposing graph..." << endl;




    /// MINHEAP TESTS
    /*
    loadedGraph.print(false);


    MinHeap heap(loadedGraph.getNumNodes());
    heap.make_heap(loadedGraph.nodes+1);
    heap.print_container();
    heap.flush_heap();
    heap.print_container();
*/
/*
    cout << "[EXECTUION] - main(): printing heap container..." << endl;
    decGraph.print_minHeap_container();

    cout << "[EXECTUION] - main(): flushing heap..." << endl;
    decGraph.flush_minHeap();


    decGraph.print_minHeap_container();



    //decGraph.heapTest();

*/





    ///  ES 2

    decGraph.decomposeGraph(debug);


    if (decGraph.isDecomposed()){
        cout << endl << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done! finding densest prefix..." << endl;
    } else {
        cout << endl << time(nullptr)-start << "s: " << "[ERROR] - main(): Not decomposed. Aborting..." << endl;
        return -1;
    }


    decGraph.findDensestPrefix(debug);
    cout <<  time(nullptr)-start << "s: " << "[EXECUTION] - main(): done! output:" << endl;
    decGraph.densest_prefix.print();
    //decGraph.print_prefix(decGraph.densest_prefix.size);

    cout << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done! writing file to plot..." << endl;
    decGraph.writeCorenessDegreeFile(outputfilename, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): successfully written!" << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): writing nodes ranking in file: " << rankfilename << endl;
    decGraph.writeAllInFile(rankfilename, true);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): successfully written!" << endl;




    /// ES 3
/*
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): find densest prefix using mkscore" << endl;
    decGraph.findDensestPrefixWithMKscore(debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done! output:" << endl;
    decGraph.densest_prefix.print();
    //decGraph.print_prefix(decGraph.densest_prefix.size);
*/

    return 0;
}