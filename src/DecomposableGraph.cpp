//
// Created by Luca De Mori on 18/10/2017.
//

#include "DecomposableGraph.h"


ostream& operator<<(ostream& out, const HeapNode& obj){
    out << *(obj.g_node) << " dec_degree:" << obj.dec_degree;
}

HeapNode::HeapNode(Node* _g_node) {
    this->g_node = _g_node;
    this->dec_degree = _g_node->degree;
}

bool HeapNode::operator<(const HeapNode &rhs) const {
    return this->dec_degree < rhs.dec_degree ;
}

bool HeapNode::operator()(const HeapNode &lhs, const HeapNode &rhs) {
    return lhs.dec_degree > rhs.dec_degree;
}

unsigned int HeapNode::getID()const {
    return g_node->ID;
}

bool operator==(const HeapNode &lhs, const unsigned int &_ID) {
    return lhs.getID()==_ID;
}

DecomposableGraph::DecomposableGraph(string filename, bool debug): AdjacencyList(filename, debug), densest_prefix() {
    this->initHeap();
    this->c = new unsigned int [this->num_nodes+1]();
    this->ordered_n = new Node*[this->num_nodes+1]();
    cout << "[SUCCESS] - DecomposableGraph(): graph loaded and heap successfully created" << endl;

}

DecomposableGraph::~DecomposableGraph() {
    if (c!= nullptr)
        delete [] c;
    if (ordered_n!= nullptr)
        delete [] ordered_n;
};

void DecomposableGraph::initHeap() {
    // connect link all the nodes of the graph in the heap
    for (unsigned int i = 1; i <= this->num_nodes; i++){
        minHeap.push(HeapNode(this->nodes+i));
    }
}

void DecomposableGraph::flushHeap(bool debug) {
    while (!this->minHeap.empty()){
        if (debug) cout << this->minHeap.top() << endl;
        this->minHeap.pop();
    }
    cout << "[SUCCESS] - flushHeap(): the heap is empty" << endl;
}


int DecomposableGraph::decomposeGraph(bool debug) {

    unsigned int c;
    unsigned int prefix_counter;
    HeapNode v;
    bool* removed = nullptr;
//    unsigned int *rank = nullptr;
//    rank = new unsigned int [this->num_nodes+1]();

    //init array to track the removed nodes
    removed = new bool [num_nodes+1]();

    if (debug) cout << "[DEBUG] - DecomposableGraph::decomposeGraph(): starting the decomposition" << endl;

    // initialize variables to calculate prefix
    prefix_counter = num_nodes;


    c = 0;
    while (!minHeap.empty()){
        // extract minimum remaining degree node in heap
        v=minHeap.top();

        // REMOVE v
        minHeap.pop();
        // update the removed array
        removed[v.getID()] = true;


        // update c value in the corresponding node in adjList
        if ( v.dec_degree > c) {
            c = v.dec_degree;
        }

        this->c[v.getID()] = c;
        this->ordered_n[prefix_counter] = v.g_node;

        // REMOVE EDGES OF v
        //update the degrees of the other nodes
            //loop on the nodes, check if v is in nodes[i]'s neigh list
            //if so, decrease its degree value in the heap
        for (unsigned int i = 0; i<v.g_node->degree; i++){
            Node* n = this->getNeighbour(v.getID(), i);

            // cout << "[DecomposableGraph::decomposeGraph] Neighbour #" << i << " of " << v.getID()
            // << " is " << *n << " removed:" << removed[n->ID] << endl;

            if (n== nullptr){
                // cout << "[DecomposableGraph::decomposeGraph] Neighbour not found... Aborting...";
                return -1;
            }

            if (!removed[n->ID]){       // if the n-th neighbur of v is not removed update it in the heap
                minHeap.update(n->ID);
            }
        }

        cout << "[EXECUTION] - DecomposableGraph::decomposeGraph():  Node: " << v.getID()
             << " c: " << this->c[v.getID()] << " prefix: " << prefix_counter << endl;

        prefix_counter--;
    }



    //if (debug) cout << "[DecomposableGraph::decomposeGraph] minHeap top: " << minHeap.top() << endl;

    return 0;

}

int DecomposableGraph::findDensestPrefix() {

    float new_density;
    unsigned int added_node;

    unsigned int m_h, // number of edges of the subgraph
                neigh_ID,
                n_h;

    bool *left_nodes;
    left_nodes = new bool [num_nodes+1]();

    m_h = 0;
    left_nodes[ordered_n[1]->ID] = true;
    // cycle over all the nodes
    for (n_h=2; n_h<num_nodes; n_h++){
        added_node = ordered_n[n_h]->ID;
        left_nodes[added_node] = true;

        cout << "[DEBUG] - DecomposableGraph::findDensestPrefix(): prefix length: " << n_h
             << " node to add: " << added_node << endl;

        // cycle over all the neighbour of the current nodes and increment m_h for each neighbour in the prefix
        for (unsigned int neigh = 0; neigh<nodes[added_node].degree; neigh++){
            neigh_ID = getNeighbour(added_node, neigh)->ID;
            cout << "[DEBUG] - DecomposableGraph::findDensestPrefix(): looking for neighbour: " << neigh_ID << "... ";
            if (left_nodes[neigh_ID]){
                m_h++;
                cout << "found, m_h++ = " << m_h << endl;
            } else {
                cout << "not in prefix, skip" << endl;
            }

        }

        new_density = (float)m_h/n_h;
        cout << "[DEBUG] - DecomposableGraph::findDensestPrefix(): new density: " << new_density << endl;


        if (new_density >= densest_prefix.avg_deg_dens){
            densest_prefix.avg_deg_dens = new_density;
            densest_prefix.size = n_h;
            densest_prefix.edge_density = (float)2*m_h/(n_h*(n_h-1));
        }

    }




    delete [] left_nodes;

    return 0;

}