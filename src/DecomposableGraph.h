//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include "MinHeap.h"
#include "MinHeapDouble.h"

#include <queue>
#include <algorithm>
#include <iostream>
#include <ctime>

class Subgraph {
public:
    ///--- CONSTRUCTORS ---
    Subgraph(): avg_deg_dens(), edge_density(), size() {};

    ///--- METHODS ---
    void print();   // print characteristics
    void reset();   // re initialize the arguments

    ///--- arguments ---
    float avg_deg_dens;
    float edge_density;
    unsigned int size;
};

class DecomposableGraph : public AdjacencyList {
public:
    ///--- CONSTRUCTORS ---
    DecomposableGraph(string filename, bool debug);
    ~DecomposableGraph();

    ///--- METHODS ---
    int decomposeGraph(bool debug);     // decompose the graph and compute coreness (save in coreness array, order nodes in ordered_n)
    bool isDecomposed()const;           // check if it as been decomposed (if coreness array has been filled)
    int findDensestPrefix(bool debug);  // calculate densest prefix using coreness value ad rank
    int writeCorenessDegreeFile(const string filename, const bool debug) const;  // (to plot) write a file with: <degree> <coreness> <number of nodes with these characteristics>
    void print_prefix(unsigned int p=0);  // print the elements contained in the prefix of size p
    void findDensestPrefixWithMKscore(bool debug);  // find densest prefix ordering the nodes according to their MK score (fill score array and orders nodes in ordered_n)
    int writeAllInFile(const string filename, const bool debug); // write all nodes with: <ID> <degree> <coreness> <mkscore>
    void mkscore(int iterations, bool debug); // calculate the mkscore of each nodes using 'iterations' number of iterations

    // oprartions on minHeap
    void update(int i); // decrease (by 1) the degree value of node with ID=i
    void heapTest();
    void flush_minHeap();   // (debug) flush the content of minHeap and print in cout
    void print_minHeap_container();  // (debug) print the container of minHeap without popping

    // MinHeapDouble heapSort();  // sort the container of minheapdouble


    ///--- arguments ---
    Subgraph densest_prefix;

private:
    bool decomposed;    // track the state of the graph
    MinHeap minHeap;    // used to decompose the graph in an efficient way (to be able to retrieve min wit O(1))
    unsigned int *c;    // to store the value of coreness for each node
    double *score;      // to store the value of mkscore for each node
    Node **ordered_n;   // to order nodes according to any criteria in order to find densest prefix

};


#endif //NSD05_DECOMPOSABLEGRAPH_H
