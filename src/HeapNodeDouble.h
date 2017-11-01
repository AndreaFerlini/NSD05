//
// Created by Andrea Ferlini on 31/10/2017.
//

#ifndef PRACTICAL5_HEAPNODEDOUBLE_H
#define PRACTICAL5_HEAPNODEDOUBLE_H

#include "Node.h"

class HeapNodeDouble{
public:
    HeapNodeDouble() : n_ID(0), value(0) {}
    HeapNodeDouble(const Node& _node, double _score);

    bool operator<(const HeapNodeDouble& rhs) const;
    bool operator()(const HeapNodeDouble& lhs, const HeapNodeDouble& rhs);
    friend ostream& operator<< (ostream& out, const HeapNodeDouble& obj);
    friend bool operator== ( const HeapNodeDouble& lhs, const unsigned int &_ID);

    ///--- arguments ---
    unsigned int n_ID;
    double value;

};



#endif //PRACTICAL5_HEAPNODEDOUBLE_H
