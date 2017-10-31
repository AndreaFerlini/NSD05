//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include "MinHeap.h"

#include <queue>
#include <algorithm>
#include <iostream>
#include <ctime>

class Subgraph {
public:

    Subgraph(): avg_deg_dens(), edge_density(), size() {};

    void print(){
        cout << endl;
        cout << "avg degree density: " << this->avg_deg_dens<< endl
             << "edge density:       " << this->edge_density << endl
             << "size:               " << this->size << endl;
    }

    float avg_deg_dens;
    float edge_density;
    unsigned int size;
};

class DecomposableGraph : public AdjacencyList {
public:
    Subgraph densest_prefix;

    DecomposableGraph(string filename, bool debug);
    ~DecomposableGraph();
    int decomposeGraph(bool debug);

    void update(int i){
        minHeap.update(i);
    }

    bool isDecomposed()const;


    void heapTest(){
        minHeap.print_container();
        update(1);
        minHeap.pop_min();
        minHeap.pop_min();
        cout << "update(1);" << endl;
        cout << "minHeap.pop_min();" << endl;
        cout << "minHeap.pop_min();" << endl;
        minHeap.print_container();
        update(3);
        update(3);
        update(2);
        update(6);
        cout << "update(3);" << endl;
        cout << "update(3);" << endl;
        cout << "update(2);" << endl;
        cout << "update(6);" << endl;
        minHeap.print_container();
    }


    int findDensestPrefix(bool debug);

    int writeCorenessDegreeFile(const string filename, const bool debug) const;

    void print_prefix(unsigned int p=0){
        cout << "prefix:             ";
        if (!p)
            p=num_nodes;
        for (unsigned int n=1; n<=p; n++){
            cout << ordered_n[n]->ID << ", ";
        }
    }

    void flush_minHeap(){
        minHeap.flush_heap();
    }

    void print_minHeap_container(){
        minHeap.print_container();
    }


private:

    bool decomposed;
    MinHeap minHeap;
    unsigned int *c;
    Node **ordered_n;

    void initHeap();

};


#endif //NSD05_DECOMPOSABLEGRAPH_H
