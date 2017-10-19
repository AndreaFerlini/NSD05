//
// Created by Andrea Ferlini on 18/10/2017.
//

#include "kdecomposition.h"

int initMinHeap(custom_priority_queue &minHeap, AdjacencyList &adjList, bool debug){
    for (unsigned int i=1; i < adjList.num_nodes+1; i++){
        if(adjList.nodes[i].id != 0)
            minHeap.push(&adjList.nodes[i]);
    }
    if (debug)
        cout << "[DEBUG] initMinHeap(): root node is: " << *minHeap.top() << endl;
    return 0;
}

int computeKCoreDecomposition(AdjacencyList &adjList, string filename, bool debug){

    custom_priority_queue minHeap;
    Node v;

    bool* removed = nullptr;
    unsigned int *rank = nullptr;

    loadAdjListContiguous(filename, adjList, false);
    adjList.print();

    unsigned int c = 0;
    unsigned int i = adjList.num_nodes;

    rank = new unsigned int [adjList.num_nodes+1]();

    //load the nodes int the heap
    initMinHeap(minHeap, adjList, debug);

    //init array to track the removed nodes
    removed = new bool [adjList.num_nodes+1];
    for (unsigned int b=1; b < adjList.num_nodes+1; b++){
        removed[b] = false;
    }

    while (!minHeap.empty()){
        v = *minHeap.top();

        if (v.degree > c){
            c = v.degree;
        }

        //remove the node from the heap
        minHeap.pop();
        //update the removed array
        removed[v.id] = true;

        //update the degrees of the other nodes
            //loop on the nodes, check if v is in nodes[i]'s neigh list
            //if so, decrease its degree value in the heap
        Node *node_to_update = nullptr;

        for (unsigned int idx = 0; idx < adjList.nodes[v.id].degree; idx++){
            if(debug){
                cout << "[DEBUG] computeKCoreDecomposition(): position of first neighbour of v=" << v.id << ": "
                     << v.first_neighbour << endl;
                cout << "[DEBUG] computeKCoreDecomposition(): neighbour of v=" << v.id << " is: "
                     << adjList.neighbours_list[v.first_neighbour + idx] << endl;
                cout << "[DEBUG] computeKCoreDecomposition(): printing the adjacency list" << endl;
                adjList.print();
            }

            if ( !removed[ adjList.neighbours_list[v.first_neighbour+idx] ]){
                node_to_update = &adjList.nodes[ adjList.neighbours_list[v.first_neighbour+idx] ];
                if (debug)
                    cout << "[DEBUG] computeKCoreDecomposition(): updating node: " << node_to_update->id << endl;
                minHeap.remove(node_to_update);
                node_to_update->degree --;
                minHeap.push(node_to_update);
            }
        }
        rank[v.id] = i;
        i --;
        cout << "[DEBUG] computeKCoreDecomposition(): core value c for node " << v.id << " is: " << c << endl;
    }

    if (debug)
        cout << "[TEST] " << *minHeap.top() << endl;

    return 0;
}