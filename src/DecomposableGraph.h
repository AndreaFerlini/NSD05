//
// Created by Luca De Mori on 18/10/2017.
//

#ifndef NSD05_DECOMPOSABLEGRAPH_H
#define NSD05_DECOMPOSABLEGRAPH_H


#include "AdjacencyList.h"
#include <queue>
#include <algorithm>


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

    bool update(const unsigned int ID){
        auto it = find(this->c.begin(), this->c.end(), ID);
        if (it != this->c.end()) {
            //cout << "[my_min_heap::update] current it: " << *it << endl;
            it->dec_degree--;
            this->remake();
            return true;
        }
        else {
            cout << "[my_min_heap::update] *** END OR NOT FOUND *** " <<  *it << endl;
            return false;
        }
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

    //no need for overriding operator <<
    /*friend ostream& operator<< (ostream& out, const Subgraph& obj){
        out << "avg degree density: " << obj.avg_deg_dens << endl
            << "edge density:       " << obj.edge_density << endl
            << "size:               " << obj.size << endl
            << "nodes accounted: ";
    }*/

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

    /*    void heapTest(){
        minHeap.print();
        minHeap.pop();
        minHeap.print();
        update(3);
        minHeap.print();
        minHeap.remake();
        minHeap.print();
    }*/

    int findDensestPrefix();

    void print_prefix(unsigned int p){
        cout << "prefix:             ";
        for (unsigned int n=1; n<=p; n++){
            cout << ordered_n[n]->ID << ", ";
        }
    }


private:

    my_min_heap minHeap;
    unsigned int *c;
    Node **ordered_n;

    void initHeap();

};


#endif //NSD05_DECOMPOSABLEGRAPH_H
