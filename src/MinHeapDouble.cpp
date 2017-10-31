//
// Created by Andrea Ferlini on 31/10/2017.
//

#include "MinHeapDouble.h"

MinHeapDouble::MinHeapDouble(unsigned int _max_size){
    max_size = _max_size;
    size = 0;
    container = new HeapNodeDouble[max_size];
    idx_container = new unsigned int[max_size];

}

void MinHeapDouble::swap(unsigned int _i, unsigned int _j) {
    HeapNodeDouble i_copy;
    unsigned int i_idx_copy;
    unsigned int i_id,
            j_id;


    i_copy = container[_i];
    i_id = i_copy.n_ID;
    i_idx_copy = idx_container[i_id];

    j_id = container[_j].n_ID;

    idx_container[i_id] = idx_container[j_id];
    container[_i] = container[_j];

    idx_container[j_id] = i_idx_copy;
    container[_j] = i_copy;
}

void MinHeapDouble::bubble_up(unsigned int _index){
    unsigned int j = (_index-1)/2;
    while (_index > 0){
        if (container[j].value > container[_index].value){
            swap(_index, j);
            _index = j;
            j = (_index-1)/2;
        } else{
            break;
        }
    }
}

void MinHeapDouble::make_heap(Node *_nodes, double *_score) {
    for (unsigned int i=0; i < max_size; i++){
        container[i] = HeapNodeDouble(_nodes[i], _score[i]);
        //cout << "[DEBUG] " << container[i].n_ID << endl;
        idx_container[(_nodes+i)->ID] = i;
        size = i; // increase the size at every insert
        bubble_up(i);
    }
    size ++;
}


void MinHeapDouble::bubble_down() {
    unsigned int i = 0;
    unsigned int j1 = 1;
    unsigned int j2 = 2;
    unsigned int j;
    while (j1 < size){
        j=( (j2<size) && (container[j2].value < container[j1].value) ) ? j2 : j1 ;
        if (container[j].value < container[i].value) {
            swap(i,j);
            i=j;
            j1=2*i+1;
            j2=j1+1;
            continue;
        }
        break;
    }
}

void MinHeapDouble::update(unsigned int _id) {
    //argument is node id
    unsigned int pos;
    pos = idx_container[_id];
    if (pos != -1 && container[pos].value != 0){
        //cout << "[DEBUG] - MinHeap::update(): decrementing node " << container[pos].n_ID << " from " << container[pos].value;
        container[pos].value--;
        //cout << " to " << container[pos].value << endl;
        bubble_up(pos);
    }
}


void MinHeapDouble::pop_min() { //TODO FIX
    if (empty()){
        //cout << "[ERROR] - MinHeap::pop_min(): heap empty, impossible to pop! Aborting..." << endl;
        return;
    }
    idx_container[container[0].n_ID] = -1;
    container[0] = container[--size]; //update position of the root
    //update idx_container with new position of root
    idx_container[container[0].n_ID] = 0;
    bubble_down();
    //cout << "[DEBUG] - MinHeap::pop_min(): final size=" << size << endl;
}

void MinHeapDouble::print_container() {
    cout << endl << "heap size: " << size << endl;
    for (unsigned int i = 0; i < size; i++){
        cout << "ID: " << container[i].n_ID << " d:" << container[i].value << endl;
    }
}

//TODO do not remove all the nodes
void MinHeapDouble::flush_heap() {
    HeapNodeDouble min;

    while (!empty()){
        //print_container();
        min=top();
        pop_min();
        cout << "ID: " << min.n_ID << " d: " << min.value << endl;
    }
}

MinHeapDouble::~MinHeapDouble() {
    delete [] container;
    delete [] idx_container;
}


bool MinHeapDouble::empty()const {
    return size == 0;
}

unsigned int MinHeapDouble::getSize() const {
    return size;
}


HeapNodeDouble MinHeapDouble::top() const {
    return container[0];
}
