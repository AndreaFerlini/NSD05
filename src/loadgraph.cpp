//
// Created by Andrea Ferlini on 17/10/2017.
//

#include "loadgraph.h"

// Calculate the number of nodes and edges
int graphSize(string filename, unsigned int &num_nodes, unsigned int &num_edges, bool debug){
    if (debug) cout << "[Graph graph_size] Begin..." << endl;

    fstream graph;
    num_nodes = 0;
    num_edges = 0;

    if(debug) cout <<  "[Graph graph_size] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){

        if(debug)
            cout <<  "[Graph graph_size] Succeed! Counting..." << endl;

        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;

            if (debug)
                cout << node << " " << neighbour << endl;

            num_edges++;
            if (node > num_nodes){
                num_nodes = node;
            }
            if (neighbour > num_nodes){
                num_nodes = neighbour;
            }
        }

        if(debug) cout << "[Graph graph_size] Done!" << endl;
        graph.close();
    }else{
        cout << "[Graph graph_size] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}


void countDegree(fstream& graph, AdjacencyList& adjGraph, bool debug) {
    unsigned int node,
            neighbour;

    while (!graph.eof()) {
        node = 0;
        neighbour = 0;

        graph >> node >> neighbour;


        if (debug)
            cout << node << " " << neighbour << endl;

        // Increase the degree of the node
        if (node) {
            adjGraph.nodes[node].degree++;
            // Sum the degree of every node
            adjGraph.cumulative_degree++;
        }

        // Increase the degree of the neighbour
        if (neighbour) {
            adjGraph.nodes[neighbour].degree++;
            // Sum the degree of every node
            adjGraph.cumulative_degree++;
        }

    }
}

void storeNeighbours(fstream& graph, AdjacencyList& adjGraph, bool debug){
    unsigned int node,
            neighbour;

    while(!graph.eof()){
        node = 0;
        neighbour = 0;

        graph >> node >> neighbour;

        if (debug)
            cout << node << " " << neighbour << endl;

        if(node) {
            adjGraph.neighbours_list[adjGraph.nodes[node].first_neigh_pos] = neighbour;
            adjGraph.nodes[node].first_neigh_pos++;
        }

        if(neighbour) {
            adjGraph.neighbours_list[adjGraph.nodes[neighbour].first_neigh_pos] = node;
            // Increase cursor to write the next neighbour in the correct location
            adjGraph.nodes[neighbour].first_neigh_pos++;
        }


    }

    // Reset beginning position (going backwards of a nr of steps equal to the degree of the node)
    for (unsigned int node_idx=1; node_idx <= adjGraph.num_nodes; node_idx++){
        adjGraph.nodes[node_idx].first_neigh_pos -= adjGraph.nodes[node_idx].degree;
    }
}

// Loading the adjacency list & store it in memory
int loadAdjList(string filename, AdjacencyList& adjGraph, bool debug){
    fstream graph;
    unsigned int cursor;


    /// -------- STRUCTURE INIT -----------
    // Compute the size of the graph
    if (graphSize(filename, adjGraph.num_nodes, adjGraph.num_edges, debug))
        return -1;

    // Allocate array of nodes
    // ARRAYS STARTS FROM 0, THE INDEX OF ARRAY CORRESPOND TO THE NODE ID  (0 IS AN ERROR VALUE)
    adjGraph.nodes = new Node[adjGraph.num_nodes+1];
    // initialize nodes with their id
    for (unsigned int n=0; n<adjGraph.num_nodes+1; n++){
        adjGraph.nodes[n].ID = n;
    }

    if (debug)
        cout << "[Adjacency List] Opening the file..." << endl;

    graph.open(filename, ios::in);
    if (graph.is_open()){
        if (debug) cout << "[Adjacency List] Succeed! Counting neigbours..." << endl;

        countDegree(graph, adjGraph, debug);

        cout << "[Adjacency List] Done! Cumulative Degree: " << adjGraph.cumulative_degree << endl;
        graph.close();
    }else{
        cout << "[Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }


    // update total number of entry in the neighbours list, instantiate neighbour table
    adjGraph.neighbours_list = new unsigned int[adjGraph.cumulative_degree+1];   // List of neighbours in a way, 0 IS NOT USED

    // Initialize first_neigh_pos to point at the beginning of their list
    cursor = 1;
    for (unsigned int node_idx=1; node_idx <=  adjGraph.num_nodes; node_idx++){
        adjGraph.nodes[node_idx].first_neigh_pos = cursor;
        // move cursor forward of "node_degree" steps, so that it becomes the new starting position for the next node
        cursor += adjGraph.nodes[node_idx].degree;
    }

    if(debug) cout <<  "[Adjacency List] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << "[Adjacency List] Succeed! Building Adjacency List..." << endl;

        storeNeighbours(graph, adjGraph, debug);

        if(debug) cout << "[Adjacency List]  Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug){
            cout << "[Adjacency List] print Adj List..." << endl;
            adjGraph.print(debug);
        }
        graph.close();

    }else{
        cout << "[Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}