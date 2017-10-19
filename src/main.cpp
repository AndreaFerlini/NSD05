#include <iostream>
#include <queue>

#include "DecomposableGraph.h"

int main() {

    string filename = "../graphs/course5.graph";
    bool debug = true;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file ... " << endl;

    DecomposableGraph decGraph(filename, debug);

    //decGraph.print(debug);
    //decGraph.heapTest();




    decGraph.decomposeGraph(debug);


    cout << endl << "Size of Node: " << sizeof(Node);
    cout << endl << "Size of Node*: " << sizeof(Node*);
    cout << endl << "Size of unsigned int: " << sizeof(unsigned int);
    cout << endl;

    return 0;
}