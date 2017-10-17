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

struct Node{
    unsigned int ID;
    unsigned int degree;
    unsigned int first_neigh_pos;

    Node() {
        ID =0;
        degree=0;
        first_neigh_pos=0;
    }

    unsigned int getLastNeighbourPos(){
        return first_neigh_pos+degree;
    }
};

struct AdjacencyList{
    unsigned int* neighbours_list;
    unsigned int cumulative_degree;
    unsigned int num_edges;
    unsigned int num_nodes;
    Node* nodes;


    /// DEFAULT CONSTRUCTOR
    AdjacencyList(){
        neighbours_list = nullptr;
        cumulative_degree = 0;
        num_nodes = 0;
        num_edges = 0;
    }

    /// DESTRUCTOR
    ~AdjacencyList(){
        if (neighbours_list != nullptr){
            delete[] neighbours_list;
        }
        if (nodes != nullptr) {
            delete[] nodes;
        }
    }
/*
    unsigned int getDegree(unsigned int id){
        if (nodes[id].ID == id)
            return nodes[id].degree;
        else{
            cout << "[AdjacencyList] - Error, node list corrupted";
            return 0;
        }
    }


    unsigned int getFirstNeighbourPos(unsigned int id){
        if (nodes[id].ID == id)
            return nodes[id].first_neigh_pos;
        else{
            cout << "[AdjacencyList] - Error, node list corrupted";
            return 0;
    }

    unsigned int getLastNeighbourPos(unsigned int vertex){
        return list_beginning[vertex]+getDegree(vertex);
    }
*/

    unsigned int getNeighbour(unsigned int node_id, unsigned int neighbour_number){
        if (nodes[node_id].ID == node_id){
            return neighbours_list[nodes[node_id].first_neigh_pos+neighbour_number];
        }
        else{
            cout << "[AdjacencyList] - Error, node list corrupted";
            return 0;
        }

    }


    /// PRINT METHOD
    void print(bool debug){

        if (debug){
            cout << "[myAdj.print]" << endl;
            cout << "cumulative_degree: " << cumulative_degree << endl;
            cout << "num_nodes:         " << num_nodes << endl;
            cout << "num_edges:          " << num_edges << endl;
        }

        cout << "  Node      Neighbours" << endl;
        cout << "  --------------------------------------------------" << endl;
        for (unsigned int node_id = 1; node_id <= num_nodes; node_id++) {
            cout << node_id << " -> ";
            for (unsigned int i = 0; i < nodes[node_id].degree; i++) {
                cout << getNeighbour(node_id,i) << " ";
            }
            cout << endl;

        }
        cout << endl ;
    }
};

/// FUNCTIONS
int loadAdjList(string filename, AdjacencyList& adjGraph, bool debug);
int graphSize(string filename, unsigned int &num_nodes, unsigned int &num_edges, bool debug);

#endif //PRACTICAL5_LOADGRAPH_H
