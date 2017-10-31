//
// Created by Andrea Ferlini on 28/10/2017.
//

#include "HeapNode.h"

ostream& operator<<(ostream& out, const HeapNode& obj){
    out << "ID: " << obj.n_ID << " dec_degree:" << obj.dec_degree;
}

HeapNode::HeapNode(const Node& _node) {
    n_ID = _node.ID;
    dec_degree = _node.degree;
}

bool HeapNode::operator<(const HeapNode &rhs) const {
    return this->dec_degree < rhs.dec_degree ;
}

bool HeapNode::operator()(const HeapNode &lhs, const HeapNode &rhs) {
    return lhs.dec_degree > rhs.dec_degree;
}


bool operator==(const HeapNode &lhs, const unsigned int &_ID) {
    return lhs.n_ID==_ID;
}