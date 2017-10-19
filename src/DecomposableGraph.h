//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include <queue>

template<typename T>
class min_heap : public priority_queue<T, vector<T>>{
public:
    bool remove(const T& value){
        auto it = find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
        else {
            return false;
        }
    }
};


class HeapNode{
public:
    HeapNode() : g_node(nullptr), dec_degree(0) {}
    HeapNode(Node* g_node);

    unsigned int getID();
    uint16_t getC();
    void setC(uint16_t _c);

    Node* getNeighbour(unsigned int number);
    bool operator<(const HeapNode& rhs) const;
    friend ostream& operator<<(ostream& out, const HeapNode& obj);

    Node* g_node;
    unsigned int dec_degree;

};

// TODO: agree on structure, methods, and everything...
class DecomposableGraph : public AdjacencyList {
public:
    DecomposableGraph(string filename, bool debug);
    //~DecomposableGraph();
    void flushHeap(bool debug);
    int decomposeGraph();

private:
    min_heap<HeapNode> minHeap;

    void initHeap();

};


#endif //NSD05_DECOMPOSABLEGRAPH_H
