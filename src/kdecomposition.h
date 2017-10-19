//
// Created by Andrea Ferlini on 18/10/2017.
//

#ifndef PRACTICAL5_KDECOMPOSITION_H
#define PRACTICAL5_KDECOMPOSITION_H

#include "loadgraph.h"
#include <queue>
#include <vector>

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

int computeKCoreDecomposition(AdjacencyList &adjList, string filename, bool debug);
int initMinHeap(custom_priority_queue &minHeap, AdjacencyList &adjList, bool debug);

#endif //PRACTICAL5_KDECOMPOSITION_H
