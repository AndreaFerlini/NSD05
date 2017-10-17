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

/// DATA STRUCTURES
struct GraphDegree{
    int* degree_array;          // degree of every node
    unsigned int graph_size;    // number of vertices in the graph
    unsigned int graph_volume;  // number of edges

    /// DEFAULT CONSTRUCTOR
    GraphDegree(){
        degree_array = nullptr;
        graph_size = 0;
    }

    /// CONSTRUCTOR
    GraphDegree(unsigned int _graph_size, unsigned int _graph_volume){
        degree_array = new int[_graph_size](); // with () it's initialized with all 0s
        graph_size = _graph_size;
        graph_volume = _graph_volume;
    }

    /// COPY CONSTRUCTOR
    /// To allow -> a = b with NodeDegree a,b;
    GraphDegree(const GraphDegree &obj){
        graph_size = obj.graph_size;
        graph_volume = obj.graph_volume;
        degree_array = new int[obj.graph_size]; // with () it's initialized with all 0s
        for (unsigned int i=0; i<graph_size; i++){
            degree_array[i] = obj.degree_array[i];
        }
    }

    /// DESTRUCTOR
    ~GraphDegree(){
        if (degree_array != nullptr){
            delete[] degree_array;
        }
    }

    /// PRINT METHOD
    void print(){
        for (unsigned int i=0; i<graph_size; i++){
            cout << "  " << i+1 << " " << degree_array[i] << endl;
        }
    }

};

struct AdjacencyList{
    unsigned int* neighbours_list;
    unsigned int* weights_list;
    unsigned int* list_beginning;
    unsigned int size_neighbour_list;
    unsigned int num_edges;
    unsigned int num_vertices;
    bool is_weighted;

    GraphDegree adjNodesDegree;


    /// DEFAULT CONSTRUCTOR
    AdjacencyList(){
        neighbours_list = nullptr;
        weights_list = nullptr;
        list_beginning = nullptr;
        size_neighbour_list = 0;
        num_vertices = 0;
        num_edges = 0;
    }

    /// CONSTRUCTOR
    AdjacencyList(unsigned int _sum_degree, unsigned int _num_vertices, unsigned int _num_edges, bool is_weighted){
        size_neighbour_list = _sum_degree;
        num_vertices = _num_vertices;
        num_edges = _num_edges;

        neighbours_list = new unsigned int [size_neighbour_list]();
        list_beginning = new unsigned int [num_vertices]();

        if (is_weighted)
            list_beginning = new unsigned int [size_neighbour_list]();

    }

    /// COPY CONSTRUCTOR
    /// To allow -> a = b with NodeDegree a,b;
    AdjacencyList(const AdjacencyList &obj){
        num_vertices = obj.num_vertices;
        num_edges = obj.num_edges;
        size_neighbour_list= obj.size_neighbour_list;
        neighbours_list = new unsigned int[size_neighbour_list]; // with () it's initialized with all 0s
        list_beginning = new unsigned int[num_vertices]; // with () it's initialized with all 0s

        for (unsigned int i=0; i < size_neighbour_list; i++){
            neighbours_list[i] = obj.neighbours_list[i];
        }

        for (unsigned int i=0; i < num_vertices; i++) {
            list_beginning[i] = obj.list_beginning[i];
        }

        if ( obj.weights_list!= nullptr){
            weights_list = new unsigned int[size_neighbour_list];
            for (unsigned int i=0; i < size_neighbour_list; i++) {
                weights_list[i] = obj.weights_list[i];
            }
        }

    }

    /// DESTRUCTOR
    ~AdjacencyList(){
        if (neighbours_list != nullptr){
            delete[] neighbours_list;
        }
        if (list_beginning != nullptr){
            delete[] list_beginning;
        }
        if (weights_list != nullptr){
            delete[] weights_list;
        }
    }

    unsigned int getDegree(unsigned int vertex){
        return adjNodesDegree.degree_array[vertex];
    }


    unsigned int getFirstNeighbourId(unsigned int vertex){
        return list_beginning[vertex];
    }

    unsigned int getLastNeighbourId(unsigned int vertex){
        return list_beginning[vertex]+getDegree(vertex);
    }

    unsigned int getNeighbour(unsigned int vertex, unsigned int neighbour_number){

        return neighbours_list[list_beginning[vertex]+neighbour_number];
    }


    /// PRINT METHOD
    void print(bool debug){

        if (debug){
            cout << "[myAdj.print]" << endl;
            cout << "size_neighbour_list: " << size_neighbour_list << endl;
            cout << "num_vertices:        " << num_vertices << endl;
            cout << "num_edges:           " << num_edges << endl;
        }

        cout << "  Node      Neighbours" << endl;
        cout << "  --------------------------------------------------" << endl;
        for (unsigned int v_idx = 0; v_idx < num_vertices; v_idx++) {
            cout << v_idx + 1 << " -> ";
            for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.degree_array[v_idx]; neigh_index++) {
                cout << neighbours_list[list_beginning[v_idx] + neigh_index] << " ";
            }

            if (is_weighted) {
                cout << endl << "W:   ";
                for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.degree_array[v_idx]; neigh_index++) {
                    cout << weights_list[list_beginning[v_idx] + neigh_index] << " ";
                }
            }
            cout << endl ;
        }
        cout << endl ;
    }
};

/// FUNCTIONS
int loadAdjListContiguous(string filename, AdjacencyList& graphAdj, bool is_weighted, bool debug);
int graphSize(string filename, unsigned int &num_nodes, unsigned int &num_edges, bool is_weighted, bool debug);
int computeDegree(string filename, GraphDegree &nodesDegree, bool is_weighted, bool debug);

#endif //PRACTICAL5_LOADGRAPH_H
