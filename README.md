--------------------
NSD: Practical 2
--------------------

Authors:
- ANDREA FERLINI
- LUCA DE MORI

Content:

This repository contains the code to solve the exercises of Practical5 (NSD-TME, M2 UPMC).

Fall Semester 2017/18


1. FOLDER STRUCTURE

The main directory contains the following folders:
	
a. /src   	: Contains all the functions
b. /graphs 	: Where to put graph files.
c. /plots 	: Where to save the program outputs. Contains the gnuplot script to plot the files plot_coreness_degree.plt
	

2. CODE STRUCTURE

2.1 FILE ARTICULATION

AdjacencyList.cpp, AdjacencyList.h
Class to load the adjacency list of a graph from a file in the format: 
"x y" (with x, y integers >1)

DecomposableGraph.cpp, DecomposableGraph.h
Inherits AdjacencyList. It adds methods to decompose the graph and calculate:
- coreness (unsigned int - array)
- mkscore (double - array)
- node ordering [ordered_n - array of pointers]
- densest subgraph [both coreness and degree friendly]
	-> average degree density
	-> edge density
	-> size

HeapNode.cpp, HeapNode.h
Nodes of the heap structure used to efficiently decompose the graph. It contains:
- Node ID (unsigned int)
- "Temporary" degree (unsigned int)

HeapNodeDouble.cpp, HeapNodeDouble.h
Nodes used in the heap to efficiently ordinate nodes using mkscore (which type is 'double')
- Node ID (unsigned int)
- score (double)

MinHeap.cpp, MinHeap.h
Class to create a minHeap of HeapNodes

MinHeapDouble.cpp, MinHeapDouble.h
Class to create a minHeap of HeapNodesDouble

Node.cpp, Node.h
A single graph vertex:
- ID (unsigned int)
- degree ()

main.cpp
Contains the instructions to complete exercises 1, 2 and 3.

	

3. USAGE
	
	3.1 GRAPH FILE FORMAT

	- Our program works with graphs stored in a file as a list of edges identified by its vertex (node) id separaded by a space:
		x y

	where x and y are POSITIVE INTEGERS GREATER THAN 1.

	3.2 LAUNCH THE PROGRAM

	The file main.cpp contains already the code to run some calculations.

	Follow the steps:
		a. Uncomment the required section.
		b. Edit the variables "filename", "outfilename", "rankfilename" with:
			- the relative path to the graph file;
			- the relative path to the desired output file (containing plot data)
			- the relative plot to the desired file containing the nodesranks
		c. Compile everything in the folder "/src"
		d. Run ./program_name
		e. modify in "/plost/plot_coreness_degree.plt"
		 - output filename
		 - path to file to plot 
		f. run ./plot_coreness_degree.plt

	3.3 OUTPUT FILEs FORMAT
	- Data to plot Coreness/Degree histogram (heatmap)
	<degree> <coreness> <occurrencies>
	- Nodes properties (coreness, score, degree)
	<ID> <degree> <coreness> <mkscore>


