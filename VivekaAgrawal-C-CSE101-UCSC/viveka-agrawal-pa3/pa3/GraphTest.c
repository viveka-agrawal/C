/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa3
-----------------------------------------------------------------------------*/

#include "Graph.h"

int main() {

	int n = 7;
	List S = newList();
	Graph G = newGraph(n);

	addArc(G, 1, 2);
   	addArc(G, 2, 3);
   	addArc(G, 2, 5);
   	addArc(G, 2, 6);
   	addArc(G, 3, 4);
   	addArc(G, 3, 7);
   	addArc(G, 4, 3);
   	addArc(G, 5, 1);
   	addArc(G, 5, 6);
   	addArc(G, 6, 7);
   	addArc(G, 7, 6);

	printf("Graph G: \n");
   	printGraph(stdout, G);
   	fprintf(stdout, "\n");

   	for (int i = 1; i <= n; i++) {
   		append(S, i);
   	}

   	DFS(G, S);
   	fprintf(stdout, "i:  discover  finish  parent\n");

   	for(int i = 1; i <= n; i++) {
      		fprintf(stdout, "%d:     %2d       %2d      %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   	}

   	fprintf(stdout, "\n");
	printf("DFS on List S: ");
   	fprintf(stdout, "\n");
   	printList(stdout, S);
   	fprintf(stdout, "\n");

   	Graph T = transpose(G);
   	Graph C = copyGraph(G);

   	fprintf(stdout, "\n");
	printf("Graph C (copy of Graph G): ");
   	fprintf(stdout, "\n");
   	printGraph(stdout, C);
	
   	fprintf(stdout, "\n");
	printf("Graph T (transpose of Graph G): ");
   	fprintf(stdout, "\n");
   	printGraph(stdout, T);
   	fprintf(stdout, "\n");

   	DFS(T, S);

	printf("DFS on List S: ");
   	fprintf(stdout, "\n");
   	fprintf(stdout, "i:  discover  finish  parent\n");

   	for(int i = 1; i <= n; i++){
      		fprintf(stdout, "%d:     %2d       %2d      %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   	}

   	fprintf(stdout, "\n");
	printf("Final List S: ");
   	fprintf(stdout, "\n");
   	printList(stdout, S);
   	fprintf(stdout, "\n");

	return 0;
}

