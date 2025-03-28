/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa2
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj {
	List* neighbors;
	int* color;
	int* parents;
	int* distance;
	int order;
	int size;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/

// creates and returns a new Graph
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parents = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;

	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parents[i] = NIL;
		G->distance[i] = INF;
	}
	return G;
}

// frees Graph pG and sets its pointer to NULL
void freeGraph(Graph* pG) {
	for (int i = 1; i <= getOrder(*pG); i++) {
		freeList(&(*pG)->neighbors[i]);
	}

	free((*pG)->neighbors);
	(*pG)->neighbors = NULL;

	free((*pG)->color);
	(*pG)->color = NULL;

	free((*pG)->parents);
	(*pG)->parents = NULL;

	free((*pG)->distance);
	(*pG)->distance = NULL;

	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/

// returns the order of the Graph
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	return G->order;
}

// returns the size of the Graph
int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	return G->size;
}

// returns the most recently used source vertex
int getSource(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	return G->source;
}

// returns the parent of vertex u in the BFS tree
// pre: 1 < u < getOrder(G)
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getParent() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	return G->parents[u];
}

// returns the distance from the most recent BFS source to vertex u
// pre: 1 < u < getOrder(G)
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	return G->distance[u];
}

// appends the vertices of a shortest path in G from the source to u to the List L
// pre: getSource(G) != NIL, 1 < u < getOrder(G)
void getPath(List L, Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL) {
		printf("Graph Error: calling getPath() on undefined vertex\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getPath() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	if (G->source == u) {
		append(L, u);
	}
	// check if the parents of vertex u are defined   
	else if (G->parents[u] != NIL) {
		getPath(L, G, G->parents[u]);
		append(L, u);
	}
	// else the parents of vertex u are undefined
	else {
		append(L, NIL);
	}
}

/*** Manipulation procedures ***/

// deletes all edges of Graph G
void makeNull(Graph G) {
	for (int i = 1; i <= G->order; i++) {
		clear(G->neighbors[i]);
	}
	G->size = 0;
}

// helper function to insert vertices into sorted List
void orderList(List L, int v) {
	// check if the List is empty
	if (length(L) == 0) {
		append(L, v);
	}
	// iterate through the List and insert the vertex v at the sorted location 
	else {
		for (moveFront(L); index(L) != -1; moveNext(L)) {
			if (v < get(L)) {
				insertBefore(L, v);
				break;
			}
		}
		if (index(L) == -1) {
			append(L, v);
		}
	}
}

// inserts a new edge joining u to v
// pre: 1 < u < getOrder(G), 1 < v < getOrder(G)
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addEdge() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}

	List V = G->neighbors[v];
	orderList(V, u);

	List U = G->neighbors[u];
	orderList(U, v);

	// increment the size of the Graph to account for the new edge created
	G->size = getSize(G) + 1;
}

// inserts a new directed edge from u to v
// pre: 1 < u < getOrder(G), 1 < v < getOrder(G)
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addArc() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}

	List U = G->neighbors[u];
	orderList(U, v);

	// increment the size of the Graph to account for the new edge created
	G->size = getSize(G) + 1;
}

// runs the BFS algorithm on the Graph G with source s
void BFS(Graph G, int s) {
   if (G == NULL) {
		printf("Graph Error: calling BFS() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	
   	G->source = s;

	// color all the vertices of the Graph
	for (int x = 1; x <= getOrder(G); x++) {
		G->distance[x] = INF;
		G->parents[x] = NIL;
		G->color[x] = WHITE;
	}

	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parents[s] = NIL;

	List L = newList();
	prepend(L, s);

	// run the loop while the List is not empty
	while (length(L) != 0) {
		// dequeue the last element in the List
		int i = back(L);
		deleteBack(L);
		List N = G->neighbors[i];

		for (moveFront(N); index(N) != -1; moveNext(N)) {
			int v = get(N);
			if (G->color[v] == WHITE) {
				G->color[v] = GRAY;
				G->distance[v] = G->distance[i] + 1;
				G->parents[v] = i;
				prepend(L, v);
			}
		}
		// vertex i and all its neighbors have been discovered
		G->color[i] = BLACK;
	}
	freeList(&L);
}

/*** Other operations ***/

// prints the adjacency list representation of Graph G to file out
void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}

	for (int i = 1; i <= G -> order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G -> neighbors[i]);
		fprintf(out, "\n");
	}
}
