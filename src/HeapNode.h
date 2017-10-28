//
// Created by Andrea Ferlini on 28/10/2017.
//

#ifndef PRACTICAL5_HEAPNODE_H
#define PRACTICAL5_HEAPNODE_H

#include "Node.h"

class HeapNode{
public:
    HeapNode() : g_node(nullptr), dec_degree(0) {}
    HeapNode(Node* g_node);

    unsigned int getID() const;

    bool operator<(const HeapNode& rhs) const;
    bool operator()(const HeapNode& lhs, const HeapNode& rhs);
    friend ostream& operator<< (ostream& out, const HeapNode& obj);
    friend bool operator== ( const HeapNode& lhs, const unsigned int &_ID);

    Node* g_node;
    unsigned int dec_degree;

};

#endif //PRACTICAL5_HEAPNODE_H
