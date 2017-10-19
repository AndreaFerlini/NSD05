//
// Created by Luca De Mori on 18/10/2017.
//

#include "Node.h"

Node::Node(){
    ID =0;
    degree=0;
    first_neigh_pos=0;
}
/*
void Node::setC(uint16_t _c) {
    this->c = _c;
}*/

unsigned int Node::getLastNeighbourPos(){
    return first_neigh_pos+degree;
}

bool Node::operator()(const Node& lhs, const Node& rhs) const {
    return lhs.degree > rhs.degree ;
}

ostream& operator<<(ostream& out, const Node& _node_ptr){
    out << "ID: " << _node_ptr.ID << "\td: " << _node_ptr.degree;
}

