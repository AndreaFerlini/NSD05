//
// Created by Andrea Ferlini on 28/10/2017.
//

#include "HeapNode.h"

ostream& operator<<(ostream& out, const HeapNode& obj){
    out << "ID: " << obj.n_ID << " value:" << obj.value;
}

HeapNode::HeapNode(const Node& _node) {
    n_ID = _node.ID;
    value = _node.degree;
}

bool HeapNode::operator<(const HeapNode &rhs) const {
    return this->value < rhs.value ;
}

bool HeapNode::operator()(const HeapNode &lhs, const HeapNode &rhs) {
    return lhs.value > rhs.value;
}


bool operator==(const HeapNode &lhs, const unsigned int &_ID) {
    return lhs.n_ID==_ID;
}