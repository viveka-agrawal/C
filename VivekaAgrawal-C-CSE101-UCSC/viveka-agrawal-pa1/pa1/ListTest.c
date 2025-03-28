/*----------------------------------------------------------------------------
   Viveka Agrawal
   cruzID: viagrawa
   pa1
----------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
	
	List A = newList();
	List B = newList();
	
	// printf("length of empty list: %d\n", length(A));
	// printf("undefined index: %d\n", index(A)); 
	
	for (int i = 0; i < 15; i++) {
	append(A, i); 
	}
	
	for (int i = 10; i < 25; i++) {
	prepend(B, i); 
	}
	
	printf("appended list: "); 
	printList(stdout, A); 
	printf("\n"); 
	
	printf("prepended list: "); 
	printList(stdout, B); 
	printf("\n"); 
	
	moveFront(A); 
	printf("moveFront(A) value: %d\n", get(A));
	moveFront(B); 
	printf("moveFront(B) value: %d\n", get(B));
	
	moveBack(A); 
	printf("moveBack(A) value: %d\n", get(A));
	moveBack(B); 
	printf("moveBack(B) value: %d\n", get(B));
	
	insertBefore(A, 79); 
	insertAfter(A, -51); 
	printf("inserted elements in A: ");
	printList(stdout, A); 
	printf("\n"); 
	insertBefore(B, -8); 
	insertAfter(B, 32); 
	printf("inserted elements in B: ");
	printList(stdout, B); 
	printf("\n"); 
	
	movePrev(A); 
	printf("List A movePrev element and index: %d, %d\n", get(A), index(A)); 
	moveNext(B); 
	printf("List B moveNext element and index: %d, %d\n", get(B), index(B)); 
	 
	deleteFront(A); 
	deleteBack(A); 
	printf("List A after deleting front and back: ");
	printList(stdout, A); 
	printf("\n");	
	
	delete(B); 
	printf("List B deleted cursor index: %d\n", index(B));
	

	return 0; 		
}
