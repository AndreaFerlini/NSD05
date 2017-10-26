#include <iostream>
#include <queue>

#include "DecomposableGraph.h"

int main() {


    string filename = "../graphs/course5.graph";
    bool debug = false;

    ifstream file(filename);
    if (!file.good()) {
        cout << "[ERROR] - main(): No such file ... " << endl;
        exit(0);
    }

    cout << "[EXECUTION] - main(): loading decomposable graph..." << endl;
    DecomposableGraph decGraph(filename, debug);
    cout << "[EXECUTION] - main(): done! decomposing graph..." << endl;

//    decGraph.print(debug);
//    decGraph.heapTest();
//    decGraph.flushHeap(true);


    decGraph.decomposeGraph(debug);

    cout << endl << "[EXECUTION] - main(): done! finding densest prefix..." << endl;
    decGraph.findDensestPrefix(debug);
    cout << "[EXECUTION] - main(): done! output:" << endl;
    decGraph.densest_prefix.print();
    decGraph.print_prefix(decGraph.densest_prefix.size);

    cout << endl;

   cout << "[EXECUTION] - main(): done! writing file to plot..." << endl;
   decGraph.writeCorenessDegreeFile("../plots/sample.out", debug);




/*
    cout << endl << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl << "Size of unsigned int: " << sizeof(unsigned int);
    cout << endl << "Size of float: " << sizeof(float);
*/
    cout << endl;

    return 0;
}