/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa6
-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

int main(int argc, char * argv[]) {

	ifstream in;
   	ofstream out;

	// check for 3 command line arguments: Arithmetic <input file> <output file>
	if (argc != 3) {
      		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      		return (EXIT_FAILURE);
   	}

	// open infile for reading
   	in.open(argv[1]);
	// if infile is not open, throw error
   	if (!in.is_open()) {
      		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      		return (EXIT_FAILURE);
   	}

	// open outfile for writing
   	out.open(argv[2]);
	// if outfile is not open, throw error
   	if (!out.is_open()) {
      		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      		return (EXIT_FAILURE);
   	}

   	string firstbigint;
   	string blankline;
   	string secondbigint;

   	getline(in, firstbigint);
   	getline(in, blankline);
   	getline(in, secondbigint);

   	BigInteger A = BigInteger(firstbigint);
   	BigInteger B = BigInteger(secondbigint);
   	BigInteger C; // result of arithmetic operations

	// output the following quantities to the outfile: A, B, A + B, A - B, A - A, 3A - 2B, AB, A^2 B^2, 9A^4 + 16B^5
	// in order and separated by blank lines
	
   	out << A << endl;
  	out << endl;
   	out << B << endl;
   	out << endl;

   	C = A + B;

   	out << C << endl;
   	out << endl;

   	C = A - B;

   	out << C << endl;
   	out << endl;

   	C = A - A;

   	out << C << endl;
   	out << endl;

   	C = (A + A + A) - (B + B);

   	out << C << endl;
   	out << endl;

   	C = A * B;

   	out << C << endl;
   	out << endl;

   	C = A * A;

   	out << C << endl;
   	out << endl;

   	C = B * B;

   	out << C << endl;
   	out << endl;

   	BigInteger D = A * A * A * A;
   	BigInteger E = B * B * B * B * B;

   	C = D + D + D + D + D + D + D + D + D + E + E + E + E + E + E + E + E + E +
   	E + E + E + E + E + E + E;

   	out << C << endl;
   	out << endl;

	// close open infile and outfile
   	in.close();
   	out.close();

	return 0;
}
