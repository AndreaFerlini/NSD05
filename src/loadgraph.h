//
// Created by Andrea Ferlini on 17/10/2017.
//

#ifndef PRACTICAL5_LOADGRAPH_H
#define PRACTICAL5_LOADGRAPH_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <list>

using namespace std;

struct Node {
    unsigned int id;
    unsigned int degree;
    unsigned int first_neighbour;

    Node(){
        id = 0;
        degree = 0;
        first_neighbour = 0;
    }
};

struct AdjacencyList{
    Node* nodes;
    unsigned int* neighbours_list;
    unsigned int size_neighbour_list;
    unsigned int num_edges;
    unsigned int num_nodes;

    AdjacencyList(){
        nodes = nullptr;
        neighbours_list = nullptr;
        size_neighbour_list = 0;
        num_nodes = 0;
        num_edges = 0;
    }

    ~AdjacencyList(){
        delete[] nodes;
        delete[] neighbours_list;
    }

    void print(){
        for (unsigned int i = 1; i < num_nodes+1; i++) {
            if (nodes[i].id) {
                cout << nodes[i].id << " -> ";
                for (unsigned int d = 0; d < nodes[i].degree; d++) {
                    if (nodes[i].degree) {
                        cout << neighbours_list[nodes[i].first_neighbour + d] << " ";
                    }
                }
                cout << endl;
            }
        }
        cout << endl ;
    }



};


int graphSize(string filename, AdjacencyList& adjList, bool debug);
int computeDegree(string filename, AdjacencyList& adjList, bool debug);
int computeCumulativeDegree(AdjacencyList& adjList, bool debug);
int computeFirstNeighbour(AdjacencyList& adjList, bool debug);
int loadAdjListContiguous(string filename, AdjacencyList& adjList, bool debug);


#endif //PRACTICAL5_LOADGRAPH_H
