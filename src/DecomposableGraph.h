//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include <queue>

class custom_priority_queue : public priority_queue<Node*, vector<Node*>, Node>
{
public:
    bool remove(Node* value){
        auto it = find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
        else {
            return false;
        }
    }
};


// TODO: agree on structure, methods, and everything...
class DecomposableGraph : public AdjacencyList {
public:
    DecomposableGraph(string filename, bool debug);
    //~DecomposableGraph();

    void flushHeap(bool debug);

private:
    minHeap nodesHeap;

    void makeHeap();
    void decomposeGraph();

};


#endif //NSD05_DECOMPOSABLEGRAPH_H
