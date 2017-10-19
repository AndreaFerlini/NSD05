//
// Created by Luca De Mori on 18/10/2017.
//

#include "DecomposableGraph.h"


ostream& operator<<(ostream& out, const HeapNode& obj){
    out << *(obj.g_node) << "\tdec_degree: " << obj.dec_degree << endl;
}

HeapNode::HeapNode(Node* _g_node) {
    this->g_node = _g_node;
    this->dec_degree = _g_node->degree;
}

bool HeapNode::operator<(const HeapNode &rhs) const {
    return this->dec_degree < rhs.dec_degree ;
}

unsigned int HeapNode::getID() {
    return g_node->ID;
}

uint16_t HeapNode::getC() {
    return g_node->c;
}

void HeapNode::setC(uint16_t _c) {
    g_node->c = _c;
}

DecomposableGraph::DecomposableGraph(string filename, bool debug): AdjacencyList(filename, debug) {
    this->initHeap();
    cout << "[DecomposableGraph] Graph loaded and heap successfully created!";
}

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
}


int DecomposableGraph::decomposeGraph() {

    HeapNode v;
    bool* removed = nullptr;
//    unsigned int *rank = nullptr;
//    rank = new unsigned int [this->num_nodes+1]();

    //load the nodes int the heap
    initHeap();

    //init array to track the removed nodes
    removed = new bool [this->num_nodes+1];


    while (!minHeap.empty()){
        v=minHeap.top();
        if ( v.dec_degree > v.getC()){
            v.setC(v.dec_degree);
        }

        //remove the node from the heap
        minHeap.pop();
        //update the removed array
        removed[v.getID()] = true;

        //update the degrees of the other nodes
            //loop on the nodes, check if v is in nodes[i]'s neigh list
            //if so, decrease its degree value in the heap

        for (unsigned int i = 0; i<v.g_node->degree; i++){
            Node* n = getNeighbour(v.getID(), i);
            if (n== nullptr){
                cout << "[DecomposableGraph::decomposeGraph] Neighbour not found... Aborting...";
                return -1;
            }

            HeapNode n_to_upd(n);
            if (!removed[n_to_upd.getID()]){  // if the n-th neighbur of v is not removed
                minHeap.remove(n_to_upd);
                n_to_upd.dec_degree --;
                minHeap.push(n_to_upd);
            }

        }

        cout << "[DecomposableGraph::decomposeGraph]  Node: " << v.getID() << " c: " << v.getC() << endl;


    }

    cout << "[DecomposableGraph::decomposeGraph] minHeap top: " << minHeap.top() << endl;

    return 0;

}