//
// Created by Andrea Ferlini on 17/10/2017.
//

#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(){
    neighbours_list = nullptr;
    cumulative_degree = 0;
    num_nodes = 0;
    num_edges = 0;
}

AdjacencyList::AdjacencyList(string filename) {
    AdjacencyList();
    this->loadFromFile(filename, false);
}

AdjacencyList::~AdjacencyList() {
    if (neighbours_list != nullptr){
        delete[] neighbours_list;
    }
    if (nodes != nullptr) {
        delete[] nodes;
    }
}

int AdjacencyList::loadFromFile(string filename, bool debug) {
    fstream graph;
    unsigned int cursor;

    if (debug) cout << "[loadFromFile] Begin..." << endl;

    if (debug)
        cout << "[loadFromFile] Opening the file..." << endl;

    graph.open(filename, ios::in);

    // --- MEASURE SIZE AND VOLUME ---
    if (graph.is_open()) {
        if(debug) cout <<  "[loadFromFile] Succeed! Measuring size and volume..." << endl;
        measureGraph(graph, debug);
        if(debug) cout << "[loadFromFile] Done!" << endl;
        graph.close();

    } else {
        cout << "[loadFromFile] Error! Unable to open the file " << filename << endl;
        return -1;
    }

    /// --- ALLOCATE VECTORS ---
    // ARRAYS STARTS FROM 0, THE INDEX OF ARRAY CORRESPOND TO THE NODE ID  (0 IS AN ERROR VALUE)
    this->nodes = new Node[this->num_nodes+1];
    // initialize nodes with their id
    for (unsigned int id=0; id<=this->num_nodes; id++){
        this->nodes[id].ID = id;
    }


    /// --- COUNTING NEIGHBOURS ---
    if (debug)
        cout << "[loadFromFile] Opening the file..." << endl;

    graph.open(filename, ios::in);
    if (graph.is_open()){
        if (debug) cout << "[loadFromFile] Succeed! Counting neigbours..." << endl;
        countDegree(graph, debug);
        if (debug) cout << "[loadFromFile] Done! Cumulative Degree: " << this->cumulative_degree << endl;
        graph.close();
    }else{
        cout << "[loadFromFile] Error! Unable to open the file " << filename << endl;
        return -1;
    }

    /// --- INITIALIZE NEIGHBOUR LIST ---
    // update total number of entry in the neighbours list, instantiate neighbour table
    this->neighbours_list = new unsigned int[this->cumulative_degree+1];   // List of neighbours in a way, 0 IS NOT USED

    // FOR EACH NODE, Initialize first_neigh_pos to point at the beginning of their list
    cursor = 1;
    for (unsigned int node_idx=1; node_idx <=  this->num_nodes; node_idx++){
        this->nodes[node_idx].first_neigh_pos = cursor;
        // move cursor forward of "node_degree" steps, so that it becomes the new starting position for the next node
        cursor += this->nodes[node_idx].degree;
    }

    /// --- READ NODES AND FILL THE NEIGHBOUR LIST ---
    if(debug) cout <<  "[loadFromFile] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << "[loadFromFile] Succeed! Building Adjacency List..." << endl;
        storeNeighbours(graph, debug);
        if(debug) cout << "[loadFromFile]  Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug){
            cout << "[loadFromFile] print Adj List..." << endl;
            this->print(debug);
        }
        graph.close();

    }else{
        cout << "[loadFromFile] Error! Unable to open the file " << filename << endl;
        return -1;
    }

    return 0;
}

unsigned int AdjacencyList::getNumNodes() {
    return this->num_nodes;
}
unsigned int AdjacencyList::getNumEdges() {
    return this->num_nodes;
}

void AdjacencyList::print(bool debug) {

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

void AdjacencyList::countDegree(fstream &graph, bool debug) {
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
            this->nodes[node].degree++;
            // Sum the degree of every node
            this->cumulative_degree++;
        }

        // Increase the degree of the neighbour
        if (neighbour) {
            this->nodes[neighbour].degree++;
            // Sum the degree of every node
            this->cumulative_degree++;
        }

    }
}

int AdjacencyList::measureGraph(fstream &graph, bool debug) {
    unsigned int node,
            neighbour;

    while(!graph.eof()){
        node = 0;
        neighbour = 0;

        graph >> node >> neighbour;

        if (debug)
            cout << node << " " << neighbour << endl;

        this->num_edges++;
        if (node > num_nodes){
            this->num_nodes = node;
        }
        if (neighbour > num_nodes){
            this->num_nodes = neighbour;
        }
    }

}

void AdjacencyList::storeNeighbours(fstream &graph, bool debug) {
        unsigned int node,
                neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;

            if (debug)
                cout << node << " " << neighbour << endl;

            if(node) {
                this->neighbours_list[this->nodes[node].first_neigh_pos] = neighbour;
                this->nodes[node].first_neigh_pos++;
            }

            if(neighbour) {
                this->neighbours_list[this->nodes[neighbour].first_neigh_pos] = node;
                // Increase cursor to write the next neighbour in the correct location
                this->nodes[neighbour].first_neigh_pos++;
            }


        }

        // Reset beginning position (going backwards of a nr of steps equal to the degree of the node)
        for (unsigned int node_idx=1; node_idx <= this->num_nodes; node_idx++){
            this->nodes[node_idx].first_neigh_pos -= this->nodes[node_idx].degree;
        }
    }

unsigned int AdjacencyList::getNeighbour(unsigned int node_id, unsigned int neighbour_number) {
    if (nodes[node_id].ID == node_id){
        return neighbours_list[nodes[node_id].first_neigh_pos+neighbour_number];
    }
    else{
        cout << "[AdjacencyList] - Error, node list corrupted";
        return 0;
    }

}



// Loading the adjacency list & store it in memory
int loadAdjList(string filename, AdjacencyList& adjGraph, bool debug){










    return 0;
}