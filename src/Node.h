//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_NODE_H
#define NSD05_NODE_H

#include <iostream>

using namespace std;

class Node{
public:
    unsigned int ID;
    unsigned int degree;
    unsigned int first_neigh_pos;
    uint16_t c;

    Node();

    unsigned int getLastNeighbourPos();
    //void setC(uint16_t);
    bool operator()(const Node& lhs, const Node& rhs) const;
    friend ostream& operator<<(ostream& out, const Node& _node_ptr);

};


#endif //NSD05_NODE_H
