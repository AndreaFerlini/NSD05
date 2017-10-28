//
// Created by Andrea Ferlini on 27/10/2017.
//

#include "MinHeap.h"

MinHeap::MinHeap(unsigned int _max_size){
    max_size = _max_size;
    container = new HeapNode [max_size];
    idx_container = new unsigned int [max_size];
}

void MinHeap::swap(unsigned int _i, unsigned int _j) {
    HeapNode tmp_node;
    unsigned int tmp_idx;

    tmp_node = container[_i];
    tmp_idx = idx_container[tmp_node.getID()];

    idx_container[container[_i].getID()] = idx_container[container[_j].getID()];
    container[_i] = container[_j];

    idx_container[container[_j].getID()] = tmp_idx;
    container[_j] = tmp_node;
}

void MinHeap::bubble_up(unsigned int _index){
    unsigned int j = (_index-1)/2;
    while (_index > 0){
        if (container[j].dec_degree > container[_index].dec_degree){
            swap(_index, j);
            _index = j;
            j = (_index-1)/2;
        } else{
            break;
        }
    }
}

void MinHeap::make_heap(Node *_nodes) {
    for (unsigned int i=0; i < max_size; i++){
        container[i] = HeapNode(_nodes+i);
        idx_container[(_nodes+i)->ID] = i;
        bubble_up(i);
    }
}

//TODO bubble down

void MinHeap::update(unsigned int _id) {
    //argument is node id
    unsigned int pos;
    pos = idx_container[_id];
    if (pos != -1 && container[pos].dec_degree != 0){
        container[pos].dec_degree --;
        bubble_up(pos);
    }
}

//TODO pop

void MinHeap::print_container() {
    for (unsigned int i = 0; i < max_size; i ++){
        cout << container[i].getID() << endl;
    }
}
