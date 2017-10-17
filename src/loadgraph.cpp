//
// Created by Andrea Ferlini on 17/10/2017.
//

#include "loadgraph.h"

// Calculate the number of nodes and edges in the graph
int graphSize(string filename, AdjacencyList& adjList , bool debug){
    fstream graph;
    adjList.num_nodes = 0;
    adjList.num_edges = 0;

    graph.open(filename, ios::in);
    if (graph.is_open()){
        unsigned int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            adjList.num_edges++;

            if (node > adjList.num_nodes){
                adjList.num_nodes = node;
            }
            if (neighbour > adjList.num_nodes){
                adjList.num_nodes = neighbour;
            }
        }

        if(debug) cout << "[SUCCESS] graphSize()" << endl;
        graph.close();
    }else{
        cout << "[ERROR] graphSize(): unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}

// Compute the degree of each node
int computeDegree(string filename, AdjacencyList& adjList, bool debug){
    unsigned int node, neighbour;
    fstream graph;

    graph.open(filename, ios::in);
    if (graph.is_open()){

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            // assign id to the node and increase its degree
            if (node){
                adjList.nodes[node].id = node;
                adjList.nodes[node].degree++;
                if(debug)
                    cout << "[DEBUG] " << adjList.nodes[node].id << " " << adjList.nodes[node].degree<< endl;
            }
            // assign id to the neighbour and increase its degree
            if (neighbour){
                adjList.nodes[neighbour].id = neighbour;
                adjList.nodes[neighbour].degree++;
                if(debug)
                    cout << "[DEBUG] " << adjList.nodes[neighbour].id << " " << adjList.nodes[neighbour].degree<< endl;
            }
            if(debug)
                cout << "[DEBUG] " << adjList.nodes[node].id << " " << adjList.nodes[neighbour].id<< endl;

        }
        /// DEBUG
        if (debug){
            cout << "[SUCCESS] computeDegree()" << endl;
            for(unsigned int i=1; i<adjList.num_nodes+1; i++){
                cout << "[DEBUG] " << i << " has degree " << adjList.nodes[i].degree << endl;
            }
        }
        graph.close();
    }else{
        cout << "[ERROR] computeDegree(): unable to open the file" << filename << endl;
        return -1;
    }
    return 0;
}

// Compute cumulative degree
int computeCumulativeDegree(AdjacencyList& adjList, bool debug){
    for (unsigned int i=1; i < adjList.num_nodes+1; i++){
        adjList.size_neighbour_list += adjList.nodes[i].degree;
    }
    if(debug) cout << "[SUCCESS] computeCumulativeDegree()" << endl;
    return 0;
}

// Compute first_neighbour of each node
int computeFirstNeighbour(AdjacencyList& adjList, bool debug){
    unsigned int pos=1;

    for (unsigned int node_idx=1; node_idx < adjList.num_nodes+1; node_idx++){
        if (adjList.nodes[node_idx].degree){
            adjList.nodes[node_idx].first_neighbour = pos;
            pos += adjList.nodes[node_idx].degree;
        }else{
            adjList.nodes[node_idx].first_neighbour = 0;
        }
        if(debug)
            cout << "[DEBUG] " << adjList.nodes[node_idx].id
                 << " first_position: " << adjList.nodes[node_idx].first_neighbour << endl;
    }
    if(debug) cout << "[SUCCESS] computeFirstNeighbour()" << endl;
    return 0;
}

// Loading the adjacency list & store it in memory
int loadAdjListContiguous(string filename, AdjacencyList& adjList, bool debug){
    unsigned int node, neighbour;

    fstream graph;
    graph.open(filename, ios::in);

    // init adjList.num_nodes, adjList.num_edges
    graphSize(filename, adjList, debug);

    adjList.nodes = new Node [adjList.num_nodes+1]();
    adjList.neighbours_list = new unsigned int[adjList.size_neighbour_list];

    // set id and degree of each node in the nodes list
    computeDegree(filename, adjList, debug);
    // set size_neighbour_list
    computeCumulativeDegree(adjList, debug);
    // set first_neighbour to point at the beginning of node's list of neighbours
    computeFirstNeighbour(adjList, debug);

    if (graph.is_open()){

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;

            if (debug){
                cout << "[DEBUG] ---------------------------------- "<< endl;
                cout << "[DEBUG] node: " << node << endl;
                cout << "[DEBUG] neighbour: " << neighbour << endl;
            }

            if(node) {
                adjList.neighbours_list[adjList.nodes[node].first_neighbour] = neighbour;
                // Increase cursor to write the next neighbour in the correct location
                if (debug){
                    cout << "[DEBUG] neighbours_list of " << node << ": "
                         << adjList.neighbours_list[adjList.nodes[node].first_neighbour] << endl;
                    cout << "[DEBUG] first_neighbour index of " << node << ": "
                         << adjList.nodes[node].first_neighbour << endl;
                }
                adjList.nodes[node].first_neighbour++;

            }
            if(neighbour) {
                adjList.neighbours_list[adjList.nodes[neighbour].first_neighbour] = node;
                if (debug){
                    cout << "[DEBUG] neighbours_list of " << neighbour << ": "
                         << adjList.neighbours_list[adjList.nodes[neighbour].first_neighbour] << endl;
                    cout << "[DEBUG] first_neighbour index of " << neighbour << ": "
                         << adjList.nodes[neighbour].first_neighbour << endl;
                }
                // Increase cursor to write the next neighbour in the correct location
                adjList.nodes[neighbour].first_neighbour++;
            }

        }

        // Reset beginning position (going backwards of a nr of steps equal to the degree of the node)
        for (unsigned int node_idx=1; node_idx < adjList.num_nodes+1; node_idx++){
            adjList.nodes[node_idx].first_neighbour -=  adjList.nodes[node_idx].degree;
        }

        if(debug)
            cout << "[SUCCESS] loadAdjListContiguous()" << endl;

        graph.close();
    }else{
        cout << "[ERROR] loadAdjListContiguous(): unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}