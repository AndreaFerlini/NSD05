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

    Node();

    unsigned int getLastNeighbourPos();
    ostream& operator<<(ostream& out) const;

    // --- CLASS TO PROVIDE METHOD TO IMPLEMENT HEAP ---
    class LessByDegree{
    public:
        bool operator()(const Node* n1, const Node* n2){
            return n1->degree<n2->degree;
        }
    };

};


#endif //NSD05_NODE_H
