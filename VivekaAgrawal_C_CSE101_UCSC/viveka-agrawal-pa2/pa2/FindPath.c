/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa2
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {

	// check for 3 command line arguments: FindPath input_file output_file
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
	}

	// open input file for reading
	FILE *in = fopen(argv[1], "r");
	
	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
    		exit(1);
	}

	// open outfile file for writing
	FILE *out = fopen(argv[2], "w");
	
	if (out == NULL) {
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
    		exit(1);
	}

   	int numv = 0; // number of vertices in the Graph
   	int vert1 = 0; // vertex 1
   	int vert2 = 0; // vertex 2
   	int src = 0; // source vertex
   	int dest = 0; // destination vertex

   	fscanf(in, "%d", &numv);
   	Graph G = newGraph(numv);

	// add the edges in the Graph based on vertices in the input file
   	while (fscanf(in, "%d %d", &vert1, &vert2) == 2) {
   		if (vert1 == 0 && vert2 == 0) {
   			break;
   		}
   		addEdge(G, vert1, vert2);
   	}

   	printGraph(out, G);
   	List L = newList();

	// read the source and destination vertex pairs from the input file
   	while (fscanf(in, "%d %d", &src, &dest)) {
   		if (src == 0 && dest == 0) {
   			break;
   		}

   		fprintf(out, "\n");
   		BFS(G, src);
   		getPath(L, G, dest);

   		fprintf(out, "The distance from %d to %d is ", src, dest);  
		// get the distance to the destination vertex
		int dist = getDist(G, dest);

   		if (dist == INF) {
   			fprintf(out, "infinity\n");
   			fprintf(out, "No %d-%d path exists\n", src, dest);
   		}
   		else {
   			fprintf(out, "%d\n", dist);
   			fprintf(out, "A shortest %d-%d path is: ", src, dest);
   			printList(out, L);
   			fprintf(out, "\n");
   		}

   		clear(L);
   	}

	// close open files
   	fclose(in);
   	fclose(out);

	// free List and Graph memory
   	freeList(&L);
   	freeGraph(&G);

	return 0;
}
