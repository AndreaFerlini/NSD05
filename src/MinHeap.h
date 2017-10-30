//
// Created by Andrea Ferlini on 27/10/2017.
//

#ifndef PRACTICAL5_MINHEAP_H
#define PRACTICAL5_MINHEAP_H

//#include "DecomposableGraph.h"
#include "AdjacencyList.h"
#include "HeapNode.h"

class MinHeap {
private:
    HeapNode *container;
    unsigned int *idx_container;
    unsigned int size;
    unsigned int max_size;
    //unsigned int size;


public:
    explicit MinHeap(unsigned int _max_size);
    void swap(unsigned int _i, unsigned int _j);
    void bubble_up(unsigned int _id);
    bool empty()const;
    unsigned int getSize()const;
    void bubble_down();
    HeapNode top()const;

    void make_heap(Node *_nodes);
    void update(unsigned int _id);

    HeapNode pop_min();
    void print_container();

    void flush_heap();

    ~MinHeap();
};



#endif //PRACTICAL5_MINHEAP_H
