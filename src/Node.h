//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_NODE_H
#define NSD05_NODE_H

#include <iostream>

using namespace std;
/*
class Node{
public:
    unsigned int ID;
    unsigned int degree;
    unsigned int first_neigh_pos;

    Node();

    unsigned int getLastNeighbourPos();

    friend ostream& operator<<(ostream& out, const Node& _node_ptr);

    struct LessByDegree
    {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->degree > rhs->degree ;
        }
    };

};*/

struct Node {
    unsigned int ID;
    unsigned int degree;
    unsigned int first_neigh_pos;

    Node(){
        ID = 0;
        degree = 0;
        first_neigh_pos = 0;
    }

    friend ostream& operator<< (ostream &out, const Node& n){
        if (n.ID)
            out << "node " << n.ID << " with degree: " << n.degree << endl;
        else
            out << "node with degree 0" << endl;
        return out;
    }

    bool operator() (const Node* n1, const Node *n2){
        return n1->degree > n2->degree;
    }
};


#endif //NSD05_NODE_H
