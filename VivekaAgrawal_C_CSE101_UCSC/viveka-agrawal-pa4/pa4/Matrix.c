/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa4
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj {
	int col; 
	double val; 
} EntryObj; 

typedef EntryObj* Entry; 

typedef struct MatrixObj {
	List* row; 
	int size; 
	int NNZ; 
} MatrixObj; 

Entry newEntry(int j, double x) {
	Entry E = malloc(sizeof(EntryObj)); 
	E->col = j; 
	E->val = x; 	
	return E; 
}

void freeEntry(Entry* eN) {
    if(eN != NULL && *eN != NULL){
        free(*eN);
        *eN = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));  
	M->row = calloc(n + 1, sizeof(List)); 

	// create List for each row in Matrix M	
	for (int i = 1; i <= n; ++i) {
		M->row[i] = newList();
	}
	// set the size of the Matrix (number of rows) to n
	M->size = n; 
	// set the number of non-zero elements in the Matrix to 0
	M->NNZ = 0; 	
	return M; 
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
	int n = (*pM)->size;
	// for each row in the Matrix, free the memory allocated to the List
	for (int i = 1; i <= n; ++i) {
		freeList(&(*pM)->row[i]); 
	} 	
	free((*pM)->row);
	(*pM)->row = NULL; 
	free(*pM); 
	(*pM) = NULL;
	
}

// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}	
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}	
	return M->NNZ;
}

// equals()
// Return true if matrices A and B are equal, false otherwise.
bool equals(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}
	// check that the size of Matrices A and B are equal
	// and the number of non-zero elements in Matrices A and B are equal
	if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
		return false; 
	}
	// check for all the rows in Matrices A and B
	for (int i = 1; i <= size(A); ++i) {
		List ListA = A->row[i]; 
		List ListB = B->row[i]; 
		
		// check that ListA has the same number of elements as ListB
		if (length(ListA) != length(ListB)) {
			return false; 
		}
		else if (length(ListA) == length(ListB) && length(ListA) > 0) {
			// check for all the List entries in ListA and ListB
			for (moveFront(ListA), moveFront(ListB); index(ListA) != -1 && index(ListB) != -1; moveNext(ListA), moveNext(ListB)) {
				Entry EntryA = get(ListA); 
				Entry EntryB = get(ListB); 
			
				// check that the column number and the value are the same in both of the Entry objects
				if ((EntryA->col != EntryB->col) || (EntryA->val != EntryB->val)) {
					return false; 
				}
			}
		}
	}	
	return true;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
	for (int i = 1; i <= size(M); ++i) {
		clear(M->row[i]); 
	}	
	M->NNZ = 0; 
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
		printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}
	if (i < 1 || i > size(M)) {
		printf("Matrix Error: calling changeEntry() on invalid row\n");
		exit(EXIT_FAILURE); 
	}
	if (j < 1 || j > size(M)) {
		printf("Matrix Error: calling changeEntry() on invalid column\n");
		exit(EXIT_FAILURE); 
	}

	// get the List at the ith row in Matrix M	
	List L = M->row[i]; 
	moveFront(L); 
	bool found = false; 

	// traverse through the List at the ith row
	while (length(L) > 0 && index(L) != -1) {
		// get the pointer to the Entry object at the current index in the List
		Entry T = get(L); 
		if (T->col == j) {
			found = true; 
		}
		moveNext(L);
	}
	// element i,j not found in Matrix, but value is 0
	// do not store 0 values in Matrix 
	if (found == false && x == 0) {
		return; 
	}
	// element i,j not found in Matrix, but value is non-zero
	// store non-zero value in Matrix 
	else if (found == false && x != 0) {
		// create a new Entry object to store column j and value x
		Entry E = newEntry(j, x); 	
		if (length(L) == 0) {
			// current List is empty
			append(L, E); 
			M->NNZ++; 
			return; 
		}
		// List is not empty, columns are stored in sorted order
		// traverse through List to get to the correct column location
		for (moveFront(L); index(L) != -1; moveNext(L)) {
			Entry T = get(L); 
			if (T->col > j) {
				insertBefore(L, E); 
				M->NNZ++; 
				return;
			}
		}
		// append Entry object at end of List as all current columns in List are less than j
		if (index(L) == -1) {
			append(L, E); 
			M->NNZ++; 
			return; 
		}
	}
	// element i,j found in Matrix, change value at i,j to x
	else if (found == true && x != 0) {
		for (moveFront(L); index(L) != -1; moveNext(L)) {
			Entry T = get(L); 	
			if (T->col == j) {
				T->val = x; 
				return; 
			}
		}
	}
	// element i,j found in Matrix, but new value of x is 0
	// delete the current non-zero value at i,j
	else if (found == true && x == 0) {
		for (moveFront(L); index(L) != -1; moveNext(L)) {
			Entry T = get(L); 
			if (T->col == j) {
				delete(L); 
				M->NNZ--; 
				return; 
			}
		}
	}
}

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	// create a new Matrix M with the same size as Matrix A
	Matrix M = newMatrix(size(A));

     	// iterates through each row of Matrix A	
	for (int i = 1; i <= size(A); ++i) {
		List L = A->row[i]; 
		moveFront(L); 
	
		// traverse through the List at the ith row 
		while (length(L) > 0 && index(L) != -1) {
			Entry EntA = get(L);
		        // create a new Entry object with the column and value obtained from Matrix A	
			Entry EntM = newEntry(EntA->col, EntA->val);
			// appends the new Entry object to the List of the ith row of the Matrix M
			append(M->row[i], EntM); 
			M->NNZ++; 
			moveNext(L); 
		}
	}
	return M;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A) {
	// create a new Matrix T with the same size as Matrix A
	Matrix T = newMatrix(size(A));
        
	// iterate through each row of Matrix A	
	for (int i = 1; i <= size(A); ++i) {
		List L = A->row[i]; 
		moveFront(L); 
		
		// traverse through the List at the ith row 
		while (length(L) > 0 && index(L) != -1) {
			Entry EntA = get(L);
		        // creates a new Entry object with row i of Matrix A as new column of Matrix T and original value of Matrix A 
			// represents transposed entry	
			Entry N = newEntry(i, EntA->val); 
			// appends transposed Entry object to the row of new Matrix T
			append(T->row[EntA->col], N); 
			T->NNZ++; 
			moveNext(L); 
		}
	}
	return T;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	if (A == NULL) {
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}

	// create a new Matrix S with the same size as Matrix A
	Matrix S = newMatrix(size(A)); 

	// return new empty Matrix S if value x is 0	
	if (x == 0) {
		return S; 
	}
	 
	// iterate through each row of Matrix A	
	for (int i = 1; i <= size(A); ++i) {
		List L = A->row[i]; 
		moveFront(L); 
		
		// traverse through the List at the ith row 
		while (length(L) > 0 && index(L) != -1) {
			Entry EntA = get(L);
		        // creates new Entry object with same column index as Matrix A and value obtained by 
			// multiplying original value of Matrix A with value x
			Entry EntS = newEntry(EntA->col, x * EntA->val); 
			// appends Entry object to the List of the ith row of Matrix S
			append(S->row[i], EntS); 
			S->NNZ++; 
			moveNext(L); 
		}
	}	
	return S;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}
	if (size(A) != size(B)) {
		printf("Matrix Error: calling sum() on incompatible Matrix references\n");
      		exit(EXIT_FAILURE);
	}

	// checks if matrices A and B have equal values 
	// if equal, function creates new Matrix M by multiplying Matrix A by 2 
	if (equals(A, B)) {
		Matrix Sum = scalarMult(2, A); 
		return Sum; 
	}
	
	// create a new Matrix Sum with the same size as Matrix A
	Matrix Sum = newMatrix(size(A)); 

	// iterates through each row of matrices A and B 
	for (int i = 1; i <= size(A); i++) {
		List L = Sum->row[i]; 
		List ListA = A->row[i]; 
		List ListB = B->row[i];
		moveFront(ListA); 
		moveFront(ListB); 
		
		// iterates through Lists A and B while there are elements in each List 
		while (index(ListA) != -1 && index(ListB) != -1) {
			Entry EntryA = get(ListA); 
			Entry EntryB = get(ListB); 
			
			// checks if column index of EntryA is less than column index of EntryB 
			// if true, append new Entry object with col,val values from Matrix A to the List of the ith row in Matrix Sum
			if (EntryA->col < EntryB->col) {
				append(L, newEntry(EntryA->col, EntryA->val)); 
				Sum->NNZ++; 
				moveNext(ListA); 
			}

			// checks if column index of EntryA is greater than column index of EntryB 
			// if true, append new Entry object with col,val values from Matrix B to the List of the ith row in Matrix Sum
			else if(EntryA->col > EntryB->col) {
				append(L, newEntry(EntryB->col, EntryB->val)); 
				Sum->NNZ++; 
				moveNext(ListB); 
			}
			else {
				// if column index of EntryA equals column index of EntryB add their values together 
				// if sum is not zero, create new Entry object with same column index as Matrix A 
				// and sum value of Matrices A and B is appended to the List of the ith row in Matrix Sum
				if ((EntryA->val + EntryB->val) != 0) {
					append(L, newEntry(EntryA->col, EntryA->val + EntryB->val)); 
					Sum->NNZ++; 
				}
				moveNext(ListA); 
				moveNext(ListB); 
			}
		}

		// processes remaining elements in ListA from Matrix A and appends them to the List of the ith row in Matrix Sum 
		while (index(ListA) != -1) {
			Entry EntryA = get(ListA); 
			append(L, newEntry(EntryA->col, EntryA->val)); 
			Sum->NNZ++; 
			moveNext(ListA); 
		}
		
		// processes remaining elements in ListB from Matrix B and appends them to the List of the ith row in Matrix Sum 
		while (index(ListB) != -1) {
			Entry EntryB = get(ListB); 
			append(L, newEntry(EntryB->col, EntryB->val)); 
			Sum->NNZ++; 
			moveNext(ListB); 
		}
	}
	return Sum;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling diff() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}
	if (size(A) != size(B)) {
		printf("Matrix Error: calling diff() on incompatible Matrix references\n");
      		exit(EXIT_FAILURE);
	}
	// create new Matrix Mult by multiplying Matrix B with -1; makes all elements in Matrix B negative
	Matrix Mult = scalarMult(-1, B); 
	// calculate sum of Matrix A and Matrix Mult (which is A + (-B), same as A - B) 
	Matrix Diff = sum(A, Mult); 
	freeMatrix(&Mult);
	return Diff;
}

// vectorDot() 
// helper function for product()
double vectorDot(List P, List Q) {
	double d = 0; 

	// iterate through elements of List P	
	for (moveFront(P); index(P) != -1; moveNext(P)) {
		Entry EntryP = get(P); 
		
		// iterates through elements of List Q
		for (moveFront(Q); index(Q) != -1; moveNext(Q)) {
			Entry EntryQ = get(Q); 
			
			// checks if column indices of current entries in Lists P and Q are equal
			if (EntryP->col == EntryQ->col) {
				// product of the elements of List P and Q are added to d	
				d += EntryP->val * EntryQ->val;
				break;
			}
		}
	}
	return d; 
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
      		exit(EXIT_FAILURE);
	}
	if (size(A) != size(B)) {
		printf("Matrix Error: calling product() on incompatible Matrix references\n");
      		exit(EXIT_FAILURE);
	}

	// creates new Matrix M with same size as Matrix A	
	Matrix M = newMatrix(size(A));

	// creates transposed Matrix T from Matrix B
	Matrix T = transpose(B);

	// iterates through each row of Matrix A 
	for (int i = 1; i <= size(A); ++i) {
		List ListA = A->row[i]; 
	
		// checks if ListA is not empty	
		if (length(ListA) > 0) { 
			// iterate through each row of transposed Matrix T
			for (int j = 1; j <= size(A); ++j) {
				List ListT = T->row[j];
				// checks if current row of transposed Matrix T is not empty
				if (length(ListT) > 0) {
					// calculates dot product of current row of Matrix A and current row of transposed Matrix T
					double x = vectorDot(ListA, ListT);
					// if dot product is non-zero
					if (x != 0) {
						// creates new Entry object with column index j and dot product value x 
						// and appends it to current List of the ith row of Matrix M
						Entry E = newEntry(j, x); 
						append(M->row[i], E); 
						M->NNZ++;
					} 
				} 
			}
		}
	} 	
	freeMatrix(&T); 
	return M;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	// iterate through all rows of Matrix M
	for (int i = 1; i <= size(M); ++i) {
		List L = M->row[i]; 
		moveFront(L); 
		
		// check that ith row of Matrix M is not empty
		if (length(L) > 0) {
			fprintf(out, "%d: ", i); 
		
			// traverse through List of ith row
			while (index(L) != -1) {
				Entry E = get(L); 
				fprintf(out, "(%d, %0.1f) ", E->col, E->val); 
				moveNext(L); 
			}
			fprintf(out, "\n"); 
		}
	}
}
