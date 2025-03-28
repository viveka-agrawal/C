/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa4
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
	
	// open infile for reading
	FILE *in = fopen(argv[1], "r");
	
	// open outfile for writing
	FILE *out = fopen(argv[2], "w");

	// check for 3 command line arguments
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
   
   	int n = 0; // size of Matrix 
   	int a = 0; // stores number of non-zero entries in Matrix A 
   	int b = 0; // stores number of non-zero entries in Matrix B
   	int i = 0; // row index
   	int j = 0; // column index
   	double x = 0.0; // value 
   	char* s = NULL; // empty line in infile 
   
	// scan infile for Matrix size and number of non-zero entries in Matrices A and B
   	fscanf(in, "%d %d %d", &n, &a, &b); 

	// create 2 Matrices with the size passed in the infile
   	Matrix A = newMatrix(n);
   	Matrix B = newMatrix(n); 
   
	// scan infile for empty line
   	fscanf(in, "%s", s); 
   
	// iterates over the number of non-zero entries in Matrix A
   	for (int k = 0; k < a; k++) {
		// scan infile for row index, column index, and value
   		fscanf(in, "%d %d %lf", &i, &j, &x); 
		// change value of the ith row and jth column in Matrix A with value x
   		changeEntry(A, i, j, x); 
   	}
   
	// scan infile for empty line	
   	fscanf(in, "%s", s); 
   
	// iterates over the number of non-zero entries in Matrix B
   	for (int m = 0; m < b; m++) {
		// scan infile for row index, column index, and value
   		fscanf(in, "%d %d %lf", &i, &j, &x); 
		// change value of the ith row and jth column in Matrix B with value x
   		changeEntry(B, i, j, x); 
   	}
  
        // read the number of non-zero entries in Matrix A	
   	a = NNZ(A);

        // read the number of non-zero entries in Matrix B	
   	b = NNZ(B); 
  
        // print out number of non-zero entries in Matrix A	
   	fprintf(out, "A has %d non-zero entries:\n", a); 
        // print out non-zero entries in Matrix A	
   	printMatrix(out, A); 
   	fprintf(out, "\n"); 
        
	// print out number of non-zero entries in Matrix B	
   	fprintf(out, "B has %d non-zero entries:\n", b); 
        // print out non-zero entries in Matrix B	
   	printMatrix(out, B); 
   	fprintf(out, "\n");
  
        // Multiply Matrix A by scalar value 1.5	
   	fprintf(out, "(1.5)*A =\n"); 
   	Matrix MultA = scalarMult(1.5, A); 
	// print out resulting Matrix MultA
   	printMatrix(out, MultA); 
   	fprintf(out, "\n");
  
        // Add Matrices A and B together and store result in Matrix SumAB  	
   	fprintf(out, "A+B =\n"); 
   	Matrix SumAB = sum(A, B); 
	// print out resulting Matrix SumAB
   	printMatrix(out, SumAB); 
   	fprintf(out, "\n");
   
        // Add Matrix A with itself and store result in Matrix SumAA  	
   	fprintf(out, "A+A =\n");
   	Matrix SumAA = sum(A, A);
        // print out the new resulting Matrix SumAA	
   	printMatrix(out, SumAA); 
   	fprintf(out, "\n"); 
   
        // Subtract Matrix A from Matrix B and store result in Matrix DiffBA  	
   	fprintf(out, "B-A =\n"); 
   	Matrix DiffBA = diff(B, A); 
	// print out the new resulting Matrix DiffBA
   	printMatrix(out, DiffBA); 
   	fprintf(out, "\n"); 
   
        // Subtract Matrix A from itself and store result in Matrix DiffAA  	
   	fprintf(out, "A-A =\n"); 
   	Matrix DiffAA = diff(A, A); 
	// print out the new resulting Matrix DiffAA
   	printMatrix(out, DiffAA); 
   	fprintf(out, "\n"); 
   
	// Compute the transpose of Matrix A and store result in Matrix TransA
   	fprintf(out, "Transpose(A) =\n"); 
   	Matrix TransA = transpose(A); 
	// print out the new resulting Matrix TransA
   	printMatrix(out, TransA); 
   	fprintf(out, "\n"); 
   
	// Compute the product of Matrices A and B and store the result in Matrix ProdAB
   	fprintf(out, "A*B =\n"); 
   	Matrix ProdAB = product(A, B); 
	// print out the new resulting Matrix ProdAB
   	printMatrix(out, ProdAB); 
   	fprintf(out, "\n"); 
   
	// Compute the product of Matrix B with itself and store the result in Matrix ProdBB
   	fprintf(out, "B*B =\n"); 
   	Matrix ProdBB = product(B, B); 
	// print out the new resulting Matrix ProdBB
   	printMatrix(out, ProdBB); 
   	fprintf(out, "\n"); 
   
	// free all Matrices
	freeMatrix(&A); 
	freeMatrix(&B);
	freeMatrix(&MultA);
	freeMatrix(&SumAB);
	freeMatrix(&SumAA);
	freeMatrix(&DiffBA);
	freeMatrix(&DiffAA);
	freeMatrix(&TransA);
	freeMatrix(&ProdAB);
	freeMatrix(&ProdBB);

	// close open files
   	fclose(in);
   	fclose(out);
   
	return 0; 
}
