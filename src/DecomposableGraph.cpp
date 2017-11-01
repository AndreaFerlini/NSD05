//
// Created by Luca De Mori on 18/10/2017.
//

#include "DecomposableGraph.h"

DecomposableGraph::DecomposableGraph(string filename, bool debug): AdjacencyList(filename, debug), densest_prefix(), decomposed(false), minHeap(this->num_nodes) {
    minHeap.make_heap(this->nodes+1);
    this->c = new unsigned int [this->num_nodes+1]();
    this->ordered_n = new Node*[this->num_nodes+1]();
    this->score = new double [this->num_nodes+1]();

    cout << "[SUCCESS] - DecomposableGraph(): graph loaded and heap successfully created" << endl;

}

DecomposableGraph::~DecomposableGraph() {
    if (c!= nullptr)
        delete [] c;

    if (score!= nullptr)
        delete [] score;

    if (ordered_n!= nullptr)
        delete [] ordered_n;
};

int DecomposableGraph::decomposeGraph(bool debug) {

    float perc;
    unsigned resolution;
    const int start = time(nullptr);

    unsigned int c;  // core value
    unsigned int prefix_counter;
    Node* v;   // min node in heap
    unsigned int d;  // value of v
    bool* removed = nullptr;

    //init array to track the removed nodes
    removed = new bool [num_nodes+1]();

    if (debug) cout << "[DEBUG] - DecomposableGraph::decomposeGraph(): starting the decomposition" << endl;

    // initialize variables to calculate prefix
    prefix_counter = num_nodes;


    c = 0;
    while (!minHeap.empty()){
        // extract minimum remaining degree node in heap and remove node
        v= nodes + minHeap.top().n_ID;
        d= minHeap.top().value;
        minHeap.pop_min();
        // update the removed array
        removed[v->ID] = true;


        // update c value in the corresponding node in adjList
        if ( d > c) {
            c = d;
        }

        this->c[v->ID] = c;

        this->ordered_n[prefix_counter] = v;

        // REMOVE EDGES OF v
        //update the degrees of the other nodes
            //loop on the nodes, check if v is in nodes[i]'s neigh list
            //if so, decrease its degree value in the heap
        for (unsigned int i = 0; i<v->degree; i++){
            unsigned int neigh = getNeighbour(v->ID, i)->ID;
            if (debug)
                cout << "[DEBUG] - DecomposableGraph::decomposeGraph(): neighbour #" << i << " of " << v->ID
                 << " is " << *getNeighbour(v->ID, i) << " removed:" << removed[neigh] << endl;

            if (neigh<1){
                cout << "[ERROR] - DecomposableGraph::decomposeGraph(): neighbour #" << i << " of " << v->ID << " not found... Aborting...";
                return -1;
            }

            if (!removed[neigh]){       // if the n-th neighbur of v is not removed update it in the heap
                minHeap.update(neigh);      // update
            }
        }

        if (debug)
            cout << "[DEBUG] - DecomposableGraph::decomposeGraph():  removed ID: " << v->ID
                 << " with c: " << this->c[v->ID] << ". Remaining heap size: " << minHeap.getSize() << endl;

        resolution = num_nodes/100;
        perc = (float)100*prefix_counter/num_nodes;
        if (((int)(resolution*perc))%resolution==0) {
            printf("%.1f%% - elapsed: %d heap_size: %d\n", perc, (int)time(NULL)-start, minHeap.getSize());
        }

        prefix_counter--;
    }
    cout << endl;

    if (debug){
        cout << "[DEBUG] ordered_n: " << endl;
        for (unsigned int i =1; i<=num_nodes; i++){
            cout  << ordered_n[i]->ID << ", ";
        }
        cout << endl;
    }

    this->decomposed = true;

    return 0;

}

int DecomposableGraph::findDensestPrefix(bool debug) {
    if (!decomposed)
        this->decomposeGraph(debug);


    float new_density;
    unsigned int added_node;

    unsigned int m_h, // number of edges of the subgraph
                neigh_ID,
                n_h;

    bool *left_nodes;
    left_nodes = new bool [num_nodes+1]();

    densest_prefix.reset();

    m_h = 0;
    left_nodes[ordered_n[1]->ID] = true;
    // cycle over all the nodes
    for (n_h=2; n_h<num_nodes; n_h++){
        added_node = ordered_n[n_h]->ID;
        left_nodes[added_node] = true;
        if (debug)
            cout << "[DEBUG] - DecomposableGraph::findDensestPrefix(): prefix length: " << n_h
             << " node to add: " << added_node << endl;

        // cycle over all the neighbour of the current nodes and increment m_h for each neighbour in the prefix
        for (unsigned int neigh = 0; neigh<nodes[added_node].degree; neigh++){
            neigh_ID = getNeighbour(added_node, neigh)->ID;
            if (debug)
                cout << "[DEBUG] - DecomposableGraph::findDensestPrefix(): looking for neighbour: " << neigh_ID << "... ";
            if (left_nodes[neigh_ID]){
                m_h++;
                if (debug)
                    cout << "found, m_h++ = " << m_h << endl;
            } else {
                if (debug)
                    cout << "not in prefix, skip" << endl;
            }

        }

        new_density = (float)m_h/n_h;
        if (debug)
            cout << "[DEBUG] - DecomposableGraph::findDensestPrefix(): new density: " << new_density << endl;


        if (new_density >= densest_prefix.avg_deg_dens){
            densest_prefix.avg_deg_dens = new_density;
            densest_prefix.size = n_h;
            densest_prefix.edge_density = (float)2*m_h/(n_h*(n_h-1));
        }

    }
    
    delete [] left_nodes;

    return 0;

}

int DecomposableGraph::writeCorenessDegreeFile(const string filename, const bool debug) const {

    float perc;
    unsigned resolution;
    const int start = time(nullptr);

    fstream ofile;
    unsigned int coreness;
    unsigned int p;     // scan the ordered array
    unsigned int* occurrencies = nullptr;
    unsigned int occ_size;
    unsigned int temp_c;

    if (debug)
        cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): opening file..." << endl;
    ofile.open(filename, ios::out);

    if (ofile.is_open()){
        if (debug)
            cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): Succeed, processing... " << endl;


        p=1;
        temp_c = c[ordered_n[p]->ID];
        while(p<=num_nodes){
            coreness=c[ordered_n[p]->ID];
            occ_size = 1;

            if (occurrencies!= nullptr)
                delete [] occurrencies;

            occurrencies = new unsigned int[occ_size]();
            if (debug)
                cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): parsing " << coreness << "-core..." << endl;


            // count occurrencies with same coreness and degree
            while (temp_c == coreness ){
                if (debug)
                    cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): node: " << ordered_n[p]->ID
                     << " d:" << ordered_n[p]->degree << endl;
                if (ordered_n[p]->degree<coreness){
                    if (debug)
                        cout <<  "[ERROR] - DecomposableGraph::writeCorenessDegreeFile(): node with degree ("
                         << ordered_n[p]->degree << ") higher than core value (" << coreness << ")" << endl;
                    return -1;
                }

                if (1+ordered_n[p]->degree-coreness > occ_size){        // if no space, realloc
                    if (debug)
                        cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): realloc occurrencies "
                         << occ_size << "->" << 1+ordered_n[p]->degree-coreness << endl;
                    unsigned int* temp = new unsigned int[1 + ordered_n[p]->degree-coreness]();
                    std::copy(occurrencies, occurrencies + occ_size, temp);
                    occ_size = 1 + ordered_n[p]->degree-coreness;
                    delete [] occurrencies;
                    occurrencies = temp;

                }
                occurrencies[ordered_n[p]->degree-coreness]++;
                if (++p<=num_nodes){
                    temp_c = c[ordered_n[p]->ID];
                } else {
                    break;
                }

                resolution = num_nodes/100;
                perc = (float)100*p/num_nodes;
                if (((int)(resolution*perc))%resolution==0) {
                    printf("%.1f%% - elapsed: %d\n", perc, (int)time(NULL)-start);
                }



            }
            if (debug)
                cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): writing [d c o], occ_size: " << occ_size << endl;

            for (unsigned int d=0; d<occ_size; d++){
                if (occurrencies[d]>0) {
                    ofile  << d + coreness << " " << coreness << " " << occurrencies[d] << endl;
                    if (debug)
                        cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile():         [" << d + coreness << " "
                         << coreness << " " << occurrencies[d] << "] " << endl;
                }
            }

        }
        if (debug)
            cout << "[DEBUG] - DecomposableGraph::writeCorenessDegreeFile(): done! " << endl;
        ofile.close();
        return 0;

    } else {
        cout << "[ERROR] - DecomposableGraph::writeCorenessDegreeFile(): cannot open the file: " << filename << endl;
        return -1;
    }

}

void DecomposableGraph::mkscore(int iterations, bool debug) {
    float perc;
    unsigned resolution;
    const int start = time(nullptr);

    for (unsigned int t = 0; t<iterations; t++ ){
        // loop on nodes
        for (unsigned int node = 1; node <=num_nodes; node ++){
            // loop on neigh of selected node
            for (unsigned int j=0; j < nodes[node].degree; j++){
                unsigned int neigh = getNeighbour(node, j)->ID;
                // graph is not directed, consider every edge once
                if (node < neigh){
                    score[node] <= score[neigh] ? score[node]++ : score[neigh]++;
                }
            }
        }
        resolution = 1;
        perc = (float)100*t/iterations;
        if (((int)(resolution*perc))%resolution==0) {
            printf("%.1f%% - elapsed: %d\n", perc, (int)time(NULL)-start);
        }
    }

    if (debug)
        cout << "[TEST] " << endl;

    for (unsigned int k=1; k < this->num_nodes+1; k++){
        score[k] /= (double) iterations;
        if (debug)
            cout << score[k] << endl;
    }

}


MinHeapDouble DecomposableGraph::heapSort() {
    MinHeapDouble minHeapDouble(this->num_nodes);
    minHeapDouble.make_heap(this->nodes, this->score);

    for (unsigned int h = minHeapDouble.getSize() - 1; h > 0; --h) {
        minHeapDouble.swap(h, 0);
        minHeapDouble.bubble_down();
    }
    return minHeapDouble;
}

void DecomposableGraph::findDensityFriendlyDensestPrefix(bool debug){

    mkscore(100, debug);

    MinHeapDouble scoreMinHeap(num_nodes);
    scoreMinHeap.make_heap(nodes+1, score+1);

    unsigned int n = num_nodes;
    while (!scoreMinHeap.empty()){
        ordered_n[n] = nodes + scoreMinHeap.top().n_ID;
        if (debug)
            cout << "[DEBUG] - DecomposableGraph::findDensityFriendlyDensestPrefix(): ID:" << ordered_n[n]->ID
                 << " score:" << scoreMinHeap.top().value << " heap size:" << scoreMinHeap.getSize() << endl;
        scoreMinHeap.pop_min();
        n--;
    }

    findDensestPrefix(debug);
}


bool DecomposableGraph::isDecomposed() const {
    return decomposed;
}

int DecomposableGraph::writeAllInFile(const string filename, const bool debug) {

    float perc;
    unsigned resolution;
    const int start = time(nullptr);


    fstream ofile;

    if (debug)
        cout << "[DEBUG] - DecomposableGraph::writeAllInFile(): opening file..." << endl;
    ofile.open(filename, ios::out);

    if (ofile.is_open()){
        if (debug)
            cout << "[DEBUG] - DecomposableGraph::writeAllInFile(): Succeed, writing... " << endl;

            for (unsigned int n=1; n<=num_nodes; n++){
                ofile << nodes[n].ID << " " << nodes[n].degree << " " << c[n] << " " << score[n] << endl;

                resolution = num_nodes/100;
                perc = (float)100*n/num_nodes;
                if (((int)(resolution*perc))%resolution==0) {
                    printf("%.1f%% - elapsed: %d\n", perc, (int)time(NULL)-start);
                }

            }


        if (debug)
            cout << "[DEBUG] - DecomposableGraph::writeAllInFile(): done! " << endl;
        ofile.close();
        return 0;

    } else {
        cout << "[ERROR] - DecomposableGraph::writeAllInFile(): cannot open the file: " << filename << endl;
        return -1;
    }

}