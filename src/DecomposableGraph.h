//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <ctime>

class HeapNode{
public:
    HeapNode() : g_node(nullptr), dec_degree(0) {}
    HeapNode(Node* g_node);

    unsigned int getID() const;

    bool operator<(const HeapNode& rhs) const;
    bool operator()(const HeapNode& lhs, const HeapNode& rhs);
    friend ostream& operator<< (ostream& out, const HeapNode& obj);
    friend bool operator== ( const HeapNode& lhs, const unsigned int &_ID);

    Node* g_node;
    unsigned int dec_degree;

};

class my_min_heap : public priority_queue<HeapNode, vector<HeapNode>, HeapNode >{
public:

    void remake(){
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }

    void update(const unsigned int ID){
        auto it = find(this->c.begin(), this->c.end(), ID);
        if (it != this->c.end()) {
            //cout << "[my_min_heap::update] current it: " << *it << "->" << it->dec_degree-1<< endl;
            it->dec_degree--;
            return;
        }
        else {
            cout << "[ERROR] - my_min_heap::update(): end of heap or node not found" <<  *it << endl;
            return;
        }
    }

    void clear_top(){
        if (this->c.begin()!=this->c.end())
            this->c.erase(this->c.begin());
    }

    void print(){
        for (auto it=this->c.begin(); it!=this->c.end(); it++){
            cout << *it << endl;
        }
        cout << endl;
    }
};

class Subgraph {
public:

    Subgraph(): avg_deg_dens(), edge_density(), size() {};

    void print(){
        cout << endl;
        cout << "avg degree density: " << this->avg_deg_dens<< endl
             << "edge density:       " << this->edge_density << endl
             << "size:               " << this->size << endl;
    }

    float avg_deg_dens;
    float edge_density;
    unsigned int size;
};

class DecomposableGraph : public AdjacencyList {
public:
    Subgraph densest_prefix;

    DecomposableGraph(string filename, bool debug);
    ~DecomposableGraph();
    void flushHeap(bool debug);
    int decomposeGraph(bool debug);

    void update(int i){
        minHeap.update(i);
    }

    void heapTest(){
        minHeap.print();
        update(1);
        minHeap.clear_top();
        minHeap.clear_top();
        cout << "update(1);" << endl;
        cout << "minHeap.clear_top();" << endl;
        cout << "minHeap.clear_top();" << endl;
        minHeap.print();
        minHeap.remake();
        cout << "minHeap.remake();" << endl;
        minHeap.print();
        update(3);
        update(3);
        update(2);
        update(6);
        cout << "update(3);" << endl;
        cout << "update(3);" << endl;
        cout << "update(2);" << endl;
        cout << "update(6);" << endl;
        minHeap.print();
        minHeap.remake();
        cout << "minHeap.remake();" << endl;
        minHeap.print();
    }


    int findDensestPrefix(bool debug);

    int writeCorenessDegreeFile(const string filename, const bool debug) const;

    void print_prefix(unsigned int p=0){
        cout << "prefix:             ";
        if (!p)
            p=num_nodes;
        for (unsigned int n=1; n<=p; n++){
            cout << ordered_n[n]->ID << ", ";
        }
    }


private:

    bool decomposed;
    my_min_heap minHeap;
    unsigned int *c;
    Node **ordered_n;

    void initHeap();

};


#endif //NSD05_DECOMPOSABLEGRAPH_H
