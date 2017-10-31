//
// Created by Andrea Ferlini on 31/10/2017.
//

#ifndef PRACTICAL5_MINHEAPDOUBLE_H
#define PRACTICAL5_MINHEAPDOUBLE_H
#include "AdjacencyList.h"
#include "HeapNodeDouble.h"

class MinHeapDouble {
private:
    //HeapNodeDouble *container;
    unsigned int *idx_container;
    unsigned int size;
    unsigned int max_size;
    //unsigned int size;


public:
    HeapNodeDouble *container;

    explicit MinHeapDouble(unsigned int _max_size);
    void swap(unsigned int _i, unsigned int _j);
    void bubble_up(unsigned int _id);
    bool empty()const;
    unsigned int getSize()const;
    void bubble_down();
    HeapNodeDouble top()const;

    void make_heap(Node *_nodes, double *_score);
    void update(unsigned int _id);

    void pop_min();
    void print_container();

    void flush_heap();

    ~MinHeapDouble();
};


#endif //PRACTICAL5_MINHEAPDOUBLE_H
