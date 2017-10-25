#include <iostream>
#include <queue>

#include "DecomposableGraph.h"

int main() {

    string filename = "../graphs/sample.graph";
    bool debug = true;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file ... " << endl;

    DecomposableGraph decGraph(filename, debug);

    //decGraph.print(debug);
    //decGraph.heapTest();


    decGraph.decomposeGraph(debug);

    decGraph.findDensestPrefix();
    decGraph.densest_prefix.print();
    decGraph.print_prefix(decGraph.densest_prefix.size);

    cout << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl << "Size of unsigned int: " << sizeof(unsigned int);
    cout << endl << "Size of float: " << sizeof(float);

    cout << endl;

    return 0;
}