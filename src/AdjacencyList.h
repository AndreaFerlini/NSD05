//
// Created by Andrea Ferlini on 17/10/2017.
//

#ifndef PRACTICAL5_LOADGRAPH_H
#define PRACTICAL5_LOADGRAPH_H

#include "Node.h"
#include <fstream>
#include <ctime>

using namespace std;

class AdjacencyList{
public:
    /// DEFAULT CONSTRUCTOR
    AdjacencyList();

    /// SPECIFIC CONSTRUCTOR (directly load graph)
    AdjacencyList(string filename);

    /// DESTRUCTOR
    ~AdjacencyList();

    unsigned int getNumNodes();
    unsigned int getNumEdges();

    int loadFromFile(string filename, bool debug);

    /// PRINT METHOD
    void print(bool debug);


protected:
    Node** neighbours_list;
    unsigned int cumulative_degree;
    unsigned int num_edges;
    unsigned int num_nodes;
    Node* nodes;

private:
    void countDegree(fstream& graph, bool debug);
    int measureGraph(fstream& graph, bool debug);
    void storeNeighbours(fstream& graph, bool debug);
    Node* getNeighbour(unsigned int node_id, unsigned int neighbour_number);


};

/// FUNCTIONS


#endif //PRACTICAL5_LOADGRAPH_H
