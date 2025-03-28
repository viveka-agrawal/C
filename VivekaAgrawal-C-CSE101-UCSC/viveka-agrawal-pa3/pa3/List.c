/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa3
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

// Structs -------------------------------------------------------------------

typedef struct NodeObj {
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int cursorIndex;
    int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// creates and returns a new Node
Node newNode(int data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return N;
}

// frees a Node and sets its pointer to NULL
void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(struct ListObj));
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    L->cursor = NULL;
    L->cursorIndex = -1;
    return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL) {
   if (pL != NULL && *pL != NULL) { 
      while (length(*pL) > 0) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) {
	if (L == NULL) {
		printf("List Error: calling length() on NULL List reference. \n");
      		exit(EXIT_FAILURE);
	}	
	return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
	if (L->cursor == NULL) {
		return -1;
  	}
	else {
		return (L->cursorIndex);
  	}
}

// Returns front element of L. Pre: length()>0
int front(List L) {
	if (L == NULL) {
		printf("List Error: calling front() on NULL List reference. \n");
      		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
      		printf("List Error: calling front() on an empty List. \n");
      		exit(EXIT_FAILURE);
   	}
   	return L->front->data; 
}

// Returns back element of L. Pre: length()>0
int back(List L) {
	if (L == NULL) {
		printf("List Error: calling back() on NULL List reference. \n");
      		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
      		printf("List Error: calling back() on an empty List. \n");
      		exit(EXIT_FAILURE);
   	}
	return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
	if (L == NULL) {
		printf("List Error: calling get() on NULL List reference. \n");
      		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
      		printf("List Error: calling get() on an empty List. \n");
      		exit(EXIT_FAILURE);
   	}
   	if (index(L) < 0) {
   		printf("List Error: calling get() on undefined curser. \n");
   	}
	return L->cursor->data; 
}

// Returns true iff Lists A and B are in same state, and returns false otherwise.
int equals(List A, List B) {
    	Node a = A->front;
    	Node b = B->front;

    	if (A == NULL || B == NULL) {
        	printf("List Error: calling equals() on NULL List reference. \n");
        	return(0);
    	}
    	// the length of the two lists has to be the same
    	if (A->length != B->length) {
      		return 0;
    	}
    	while (a != NULL && b != NULL) {
        	if (a->data != b->data) {
            		return 0;
        	}
        	a = a->next;
        	b = b->next;
    	}
	return (1);
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
	if (L == NULL || L->front == NULL || L->back == NULL) {
		return;
  	}
  	while (L->front != NULL) {
	  	deleteFront(L);
  	}
}
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x) {
	if (L == NULL) {
		printf("List Error: calling set() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		printf("List Error: calling set() on an empty List\n");
      		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling set() on an undefined index\n");
      		exit(EXIT_FAILURE);
	}

	L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
	// check for empty List
    	if (L->length <= 0) {
        	return;
    	}
    	L->cursor = L->front;
    	L->cursorIndex = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    	if (L->length <= 0) {
        	printf("Error: calling moveBack() function on empty list. \n");
        	exit(EXIT_FAILURE);
    	}
    	L->cursor = L->back;
    	L->cursorIndex = (L->length - 1);
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    	int cursorIndex = index(L);

    	// if the cursor is defined and is not at the front of the List, move the cursor one step towards the front ot it
    	if (cursorIndex != -1 && cursorIndex != 0) { 
        	L->cursorIndex -= 1;
        	L->cursor = L->cursor->prev;
    	}
    	// if the cursor is defined and is at the front, the cursor becomes undefined and the List is empty
    	else if (cursorIndex != -1 && cursorIndex == 0) {
        	L->cursorIndex = -1;
        	L->cursor = NULL;
    	}
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    	int cursorIndex = index(L);
    	// if the cursor is defined and it is not at the back, move the cursor one step towards the back of the List
    	if (cursorIndex != -1 && cursorIndex != (L->length -1)) { 
        	L->cursorIndex += 1;
        	L->cursor = L->cursor->next;
    	}
    	// if the cursor is defined and it is at the back, the cursor becomes undefined
    	else if (cursorIndex != -1 && cursorIndex == (L->length - 1)) {
        	L->cursorIndex = -1;
        	L->cursor = NULL;
    	}
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	
	Node pre = newNode(data);

	if (length(L) == 0) {
    		L->front = pre;
    		L->back = pre;
	}
	else if (length(L) > 0) {
		pre->next = L->front;
		L->front->prev = pre;
		L->front = pre;
	}
	if (index(L) != -1) {
		L->cursorIndex = index(L) + 1;
	}

	L->length = length(L) + 1;
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int data) {
	if(L->length == 0) {
    		// create a new node and add it to the List
    		Node app = newNode(data); 
    		L->front = app;
    		L->back = app;
  	}
	else if(L->length > 0) {
		Node save = newNode(data);
		save->prev = L->back;
		L->back->next = save;
		L->back = save;
  	}
    	L->length++;
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
  	if(length <= 0) {
    		printf("List Error: calling insertBefore() on an empty List. \n");
    		return;
  	}
  	if (L->cursor == NULL) {
    		printf("List Error: calling insertBefore() on NULL List reference \n");
    		return;
  	}
	else {
    		Node insertb = newNode(data);
    		Node previous = L->cursor->prev;
    		insertb->prev = previous;
    		insertb->next = (L->cursor);
    		if (previous != NULL) {
      			previous->next = insertb;
    		}
    		L->cursor->prev = insertb;
    		if (L->cursor == L->front){
      			L->front = insertb;
      		}
    		L->length++; 
    		L->cursorIndex += 1;
	}
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
  	if(length <= 0) {
    		printf("List Error: calling insertAfter() on an empty List. \n");
    		return;
  	}
  	if (L->cursor == NULL) {
    		return;
  	}
  	else {
     		Node inserta = newNode(data);
     		Node nexthold = L->cursor->next;
     		inserta->prev = L->cursor;
     		inserta->next = nexthold;
     		L->cursor->next = inserta;
     		if(L->cursor == L->back) {
       			L->back = inserta;
     		}
		if (nexthold != NULL) {
       			nexthold-> prev = inserta;
     		}
		L->length++;
  	}
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  	if (length(L) == 0) {
    		printf("List Error: calling deleteFront() on an empty List. \n");
    		return;
  	}
  	if (L->front == L->back) {
    		freeNode(&(L->back));
    		L->front = NULL;
    		L->back = NULL;
    		L->length = 0;
    		L->cursorIndex = -1;
    		return;
  	}

  	Node newfront = L->front->next;

  	// If the cursor is at the front
  	if (L->front == L->cursor) {
    		L->cursor = NULL;
  	}

  	freeNode(&(L->front));
  	L->front = newfront;
  	L->length--;
  	L->cursorIndex -= 1;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  	if (L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference. \n");
      		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
    		printf("List Error: calling deleteBack() on an empty List. \n");
      		exit(EXIT_FAILURE);
  	}
	if (length(L) == 1) {
		Node deleteb = L->back;
		L->back = NULL;
		freeNode(&deleteb);
	}
	else {
		Node deleteb = L->back;
		Node new = L->back->prev;
		new->next = NULL;
		L->back = new;

		if (L->cursor == deleteb) {
			L->cursorIndex = -1;
		}
		freeNode(&deleteb);
	}
	L->length = length(L) - 1;
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
  	if (L == NULL || (L->front == NULL)) {
    		printf("List Error: calling delete() on NULL List reference. \n");
    		exit(EXIT_FAILURE);
  	}

  	//when the node trying to be deleted is the last in the list, delete it and return the item inside
  	Node del = L->cursor;
  	if (del == L->front) {
    		deleteFront(L);
  	}
  	else if (del == L->back) {
    		deleteBack(L);
  	}
  	else {
    		Node before = del->prev;
    		Node after = del->next;
    		freeNode(&del);
    		before->next = after;
    		after->prev = before;
		L->length--;
  	}
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
   	for (Node n = L->front; n != NULL; n = n->next) {
    	fprintf(out,"%d " , n->data);
  	}
  	//fprintf(out, "%d ",  front(L));
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
	Node traverse = L->front;
    	List listcopy = newList();
    	while (traverse != NULL) {
        	int copy = traverse->data;
        	traverse = traverse->next;
        	append(listcopy, copy);
    	}
    	return(listcopy);
}


