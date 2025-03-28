/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa3
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {

	// open infile for reading
	FILE *in = fopen(argv[1], "r");
	
	// open outfile for writing
	FILE *out = fopen(argv[2], "w");
	
	// check for 3 command line arguments: FindComponents infile outfile
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}	
	
	// check for empty infile
	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
    		exit(1);
	}
	
	// check for empty outfile
	if (out == NULL) {
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
    		exit(1);
	}

   	int numvertices = 0; // number of vertices in the Graph
   	int vert1 = 0; // vertex 1
   	int vert2 = 0; // vertex 2

   	fscanf(in, "%d", &numvertices);
   	Graph G = newGraph(numvertices);
	
   	while (fscanf(in, "%d %d", &vert1, &vert2) == 2) {
   		if (vert1 == 0 && vert2 == 0) {
   			break;
   		}
   		addArc(G, vert1, vert2);
   	}
	
   	List S = newList();
	
   	for (int i = 1; i <= numvertices; i++) {
   		append(S, i);
   	}

   	fprintf(out, "Adjacency list representation of G:\n");
   	printGraph(out, G);
   	fprintf(out, "\n");

   	DFS(G, S);
   	Graph T =  transpose(G);
   	DFS(T, S);

   	int numcomponents = 0;

	for (int i = 1; i <= numvertices; i++) {
		if (getParent(T, i) == NIL) {
			numcomponents++;
		}
	}

	fprintf(out, "G contains %d strongly connected components:\n", numcomponents);

	List C = newList();

	for (int i = 1; i <= numcomponents; i++) {
		fprintf(out, "Component %d: ", i);

		while (getParent(T, back(S)) != NIL) {
			moveFront(C);
			prepend(C, back(S));
			deleteBack(S);
		}
		moveFront(C);
		prepend(C, back(S));
		deleteBack(S);
		printList(out, C);
		fprintf(out, "\n");
		clear(C);
	}

   	freeGraph(&G);
   	freeGraph(&T);
   	freeList(&S);
   	freeList(&C);

	// close open files
   	fclose(in);
   	fclose(out);

	return 0;
}
