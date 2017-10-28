//
// Created by Andrea Ferlini on 28/10/2017.
//

#include "HeapNode.h"

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