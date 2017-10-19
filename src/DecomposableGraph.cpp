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

uint16_t HeapNode::getC() {
    return g_node->c;
}

void HeapNode::setC(uint16_t _c) {
    g_node->c = _c;
}


bool operator==(const HeapNode &lhs, const unsigned int &_ID) {
    return lhs.getID()==_ID;
}

DecomposableGraph::DecomposableGraph(string filename, bool debug): AdjacencyList(filename, debug) {
    this->initHeap();
    cout << "[DecomposableGraph] Graph loaded and heap successfully created!" << endl;
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
    cout << "heap empty" << endl;
}


int DecomposableGraph::decomposeGraph(bool debug) {

    uint16_t c;
    HeapNode v;
    bool* removed = nullptr;
//    unsigned int *rank = nullptr;
//    rank = new unsigned int [this->num_nodes+1]();

    //init array to track the removed nodes
    removed = new bool [num_nodes+1]();

    if (debug) cout << "[DecomposableGraph::decomposeGraph] start decomposition..." << endl;

    c = 0;
    while (!minHeap.empty()){

        // cout << endl << "***MINHEAP TOP = " << minHeap.top() << endl;

        // extract minimum remaining degree node in heap
        v=minHeap.top();
        minHeap.pop();
        // update the removed array
        removed[v.getID()] = true;

        // if (debug) cout << "***MINHEAP TOP (after pop) = " << minHeap.top() << endl;

        // update c value in the corresponding node in adjList
        if ( v.dec_degree > c) {
            c = v.dec_degree;
        }

        v.setC(c);

        //update the degrees of the other nodes
            //loop on the nodes, check if v is in nodes[i]'s neigh list
            //if so, decrease its degree value in the heap
        for (unsigned int i = 0; i<v.g_node->degree; i++){
            Node* n = this->getNeighbour(v.getID(), i);

            // cout << "[DecomposableGraph::decomposeGraph] Neighbour #" << i << " of " << v.getID() << " is " << *n << " removed:" << removed[n->ID] << endl;

            if (n== nullptr){
                // cout << "[DecomposableGraph::decomposeGraph] Neighbour not found... Aborting...";
                return -1;
            }

            if (!removed[n->ID]){       // if the n-th neighbur of v is not removed update it in the heap
                minHeap.update(n->ID);
            }
        }

        cout << "[DecomposableGraph::decomposeGraph]  Node: " << v.getID() << " c: " << v.getC() << endl;

    }

    //if (debug) cout << "[DecomposableGraph::decomposeGraph] minHeap top: " << minHeap.top() << endl;

    return 0;

}