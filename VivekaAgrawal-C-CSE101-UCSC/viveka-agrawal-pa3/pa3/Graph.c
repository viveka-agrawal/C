/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa3
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphObj {
	List* neighbors;
	int* color;
	int* parents;
	int* discover;
	int* finish;
	int order;
	int size;
} GraphObj;

/*** Constructors-Destructors ***/

// creates and returns a new Graph
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parents = calloc(n + 1, sizeof(int));
	G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
	G->order = n;
	G->size = 0;

	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parents[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
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

	free((*pG)->discover);
	(*pG)->discover = NULL;

	free((*pG)->finish);
	(*pG)->finish = NULL;
	
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

// returns the parent of vertex u
// pre: 1 <= u <= n = getOrder(G)
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

// returns the discover time of vertex u
// pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDiscover() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	return G->discover[u];
}

// returns the finish time of vertex u
// pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getFinish() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	return G->finish[u];
}

/*** Manipulation procedures ***/

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

// helper function to check if arc already exists
bool check(Graph G, int u, int v) {
	List L = G->neighbors[u];
        if (length(L) <= 0) { 
		return false;
	}	
	for (moveFront(L); index(L) != -1; moveNext(L)) {
		if (get(L) == v) {
			return true; 
		}
	}	
	return false; 
}

// inserts a new edge joining u to v
// pre: 1 <= u <= n, 1 <= v <= n
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addEdge() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}

	orderList(G->neighbors[v], u);
	orderList(G->neighbors[u], v);

	// increment the size of the Graph to account for the new edge created
	G->size = getSize(G) + 1;
}

// inserts a new directed edge from u to v
// pre: 1 <= u <= n, 1 <= v <= n
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addArc() on invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	if (check(G, u, v) == false) {
		orderList(G -> neighbors[u], v);
		G->size = getSize(G) + 1;
	}
}

// helper function for DFS time
void Visit(Graph G, List S, int u, int* time) {
	G->discover[u] = ++(*time);
	G->color[u] = GRAY;
	List L = G->neighbors[u];

	for (moveFront(L); index(L) != -1; moveNext(L)) {
		int y = get(L);
		if (G->color[y] == WHITE) {
			G->parents[y] = u;
			Visit(G, S, y, time);
		}
	}
	G->color[u] = BLACK;
	G->finish[u] = ++(*time);
	prepend(S, u);
}

// runs the DFS algorithm on Graph G
// pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
	if (G == NULL) {
		printf("Graph Error: calling DFS() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	if (S == NULL) {
		printf("Graph Error: calling DFS() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if (length(S) != getOrder(G)) {
		printf("Graph Error: calling DFS() on incompatible Graph or List\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] = WHITE;
		G->parents[i] = NIL;
	}

	int time = 0;
	List T = copyList(S);
	clear(S);

	for (moveFront(T); index(T) != -1; moveNext(T)) {
		int u = get(T);

		if (G->color[u] == WHITE) {
			Visit(G, S, u, &time);
		}
	}
	freeList(&T);
}

/*** Other Functions ***/

// returns a new Graph which is the transpose of Graph G
Graph transpose(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling transpose() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}

	Graph T = newGraph(getOrder(G));

	for (int i = 1; i <= getOrder(G); i++) {
		List L = G->neighbors[i];

		for (moveFront(L); index(L) != -1; moveNext(L)) {
			addArc(T, get(L), i);
		}
	}
	return T;
}

// returns a copy of Graph G
Graph copyGraph(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}

	Graph C = newGraph(getOrder(G));

	for (int i = 1; i <= getOrder(G); i++) {
		List L = G -> neighbors[i];
		for (moveFront(L); index(L) != -1; moveNext(L)) {
			addArc(C, i, get(L));
		}
	}
	return C;
}

// prints the adjacency list representation of Graph G to file out
void printGraph(FILE* out , Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
