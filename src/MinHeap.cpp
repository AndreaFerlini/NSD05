//
// Created by Andrea Ferlini on 27/10/2017.
//

#include "MinHeap.h"

MinHeap::MinHeap(unsigned int _max_size){
    max_size = _max_size;
    size = 0;
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
        cout << "[DEBUG] " << container[i].getID() << endl;
        idx_container[(_nodes+i)->ID] = i;
        size = i; // increase the size at every insert
        bubble_up(i);
    }
}


void MinHeap::bubble_down() {
    unsigned int i = 0;
    unsigned int j1 = 1;
    unsigned int j2 = 2;
    unsigned int j;
    while (j1 < size+1){
        j=( (j2<size+1) && (container[j2].dec_degree < container[j1].dec_degree) ) ? j2 : j1 ;
        if (container[j].dec_degree < container[i].dec_degree) {
            swap(i,j);
            i=j;
            j1=2*i+1;
            j2=j1+1;
            continue;
        }
        break;
    }
}

void MinHeap::update(unsigned int _id) {
    //argument is node id
    unsigned int pos;
    pos = idx_container[_id];
    if (pos != -1 && container[pos].dec_degree != 0){
        cout << "[TEST before] " << container[pos].dec_degree;
        container[pos].dec_degree--;
        cout << "[TEST after] " << container[pos].dec_degree << endl;
        bubble_up(pos);
    }
}


HeapNode MinHeap::pop_min() {
    HeapNode root = container[0];
    idx_container[root.getID()] = -1;
    container[0] = container[--size+1]; //update position of the root
    //update idx_container with new position of root
    idx_container[container[0].getID()] = 0;
    bubble_down();
    //cout << root.getID();
    return root;
}

void MinHeap::print_container() {
    cout << "[PRINT CONTAINER] size " << size << endl;
    for (unsigned int i = 0; i < size+1; i ++){
        cout << container[i].getID() << "-" << container[i].dec_degree << " ";
    }
    cout << endl;
}

//TODO do not remove all the nodes
void MinHeap::flush_heap() {
    HeapNode min;
    //cout << "[EXECTUION] ";
    while (size != 0){
        print_container();
        min = pop_min();

        //cout << " " << min.getID();
    }
}

MinHeap::~MinHeap() {
    delete [] container;
    delete [] idx_container;
}


bool MinHeap::empty()const {
    return size == 0;
}

unsigned int MinHeap::getSize() const {
    return size;
}

HeapNode MinHeap::top() const {
    return container[0];
}