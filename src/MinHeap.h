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
        unsigned int max_size;
        //unsigned int size;


    public:
        explicit MinHeap(unsigned int _max_size);
        void swap(unsigned int _i, unsigned int _j);
        void bubble_up(unsigned int _id);
        //TODO bubble down
        void bubble_down();

        void make_heap(Node *_nodes);
        void update(unsigned int _id);

        //TODO pop min
        void pop_min();
        void print_container();
};



#endif //PRACTICAL5_MINHEAP_H
