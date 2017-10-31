//
// Created by Andrea Ferlini on 28/10/2017.
//

#ifndef PRACTICAL5_HEAPNODE_H
#define PRACTICAL5_HEAPNODE_H

#include "Node.h"

class HeapNode{
public:
    HeapNode() : n_ID(0), value(0) {}
    HeapNode(const Node& _node);

    bool operator<(const HeapNode& rhs) const;
    bool operator()(const HeapNode& lhs, const HeapNode& rhs);
    friend ostream& operator<< (ostream& out, const HeapNode& obj);
    friend bool operator== ( const HeapNode& lhs, const unsigned int &_ID);

    unsigned int n_ID;
    unsigned int value;

};

#endif //PRACTICAL5_HEAPNODE_H
