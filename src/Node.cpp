//
// Created by Luca De Mori on 18/10/2017.
//

#include "Node.h"

Node::Node(){
    ID =0;
    degree=0;
    first_neigh_pos=0;
}

unsigned int Node::getLastNeighbourPos(){
    return first_neigh_pos+degree;
}

ostream& Node::operator<<(ostream &out) const{
    out << "ID: " << this->ID << "\td: " << this->degree;
}