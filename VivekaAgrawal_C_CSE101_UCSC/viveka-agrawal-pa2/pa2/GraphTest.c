/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa2
-----------------------------------------------------------------------------*/

#include "Graph.h"

int main() {
	int n = 36;
	Graph G = newGraph(n);
	List L = newList();

	for (int i = 1; i < n; i++) {
		if (i % 12 != 0) {
			addEdge(G, i, i + 1);
		}
		if (i <= 24) {
			addEdge(G, i, i + 12);
		}
	}

	printf("before BFS\n");
	printf("order: %d\n", getOrder(G));
	printf("size: %d\n", getSize(G));
	printf("source: %d\n", getSource(G));
	printf("parent: %d\n", getParent(G, 8));
	printf("distance: %d\n", getDist(G, 8));
	printf("\n");

	BFS(G, 8);
	printf("after BFS\n");
	printf("source: %d\n", getSource(G));
	printf("parent: %d\n", getParent(G, 8));
	printf("distance: %d\n", getDist(G, 8));

	printf("\n");
	printGraph(stdout, G);

	addEdge(G, 24, 8);
	addEdge(G, 1, 28);
	addEdge(G, 3, 13);
	printf("\n");

	printf("new edges\n");
	printf("order: %d\n", getOrder(G));
	printf("size: %d\n", getSize(G));
	printf("source: %d\n", getSource(G));
	printf("parent: %d\n", getParent(G, 8));
	printf("distance: %d\n", getDist(G, 8));

	printf("\n");
	printGraph(stdout, G);
	printf("\n");

	BFS(G, 8);
	getPath(L, G, 21);
	printf("List: ");
	printList(stdout, L);
	printf("\n");
	clear(L);

	BFS(G, 13);
	getPath(L, G, 18);
	printf("List: ");
	printList(stdout, L);
	printf("\n");
	clear(L);

	freeList(&L);
	freeGraph(&G);

	return 0;
}

