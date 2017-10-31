//
// Created by Andrea Ferlini on 31/10/2017.
//

#include "HeapNodeDouble.h"

ostream& operator<<(ostream& out, const HeapNodeDouble& obj){
    out << "ID: " << obj.n_ID << " value:" << obj.value;
}

HeapNodeDouble::HeapNodeDouble(const Node& _node, double _score) {
    n_ID = _node.ID;
    value = _score;
}

bool HeapNodeDouble::operator<(const HeapNodeDouble &rhs) const {
    return this->value < rhs.value ;
}

bool HeapNodeDouble::operator()(const HeapNodeDouble &lhs, const HeapNodeDouble &rhs) {
    return lhs.value > rhs.value;
}


bool operator==(const HeapNodeDouble &lhs, const unsigned int &_ID) {
    return lhs.n_ID==_ID;
}