/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa8
-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {

	ifstream in;
   	ofstream out;

	// // check for 3 command line arguments
	if (argc != 3) {
      		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      		return(EXIT_FAILURE);
   	}

	// open infile for reading
   	in.open(argv[1]);
	// / if infile is not open, throw error
   	if (!in.is_open()) {
      		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      		return(EXIT_FAILURE);
   	}

	// open outfile for writing
   	out.open(argv[2]);
	// if outfile is not open, throw error
   	if(!out.is_open()) {
      		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      		return(EXIT_FAILURE);
   	}

	// initialize empty Dictionary D
   	Dictionary D;
	// initialize an empty string key
   	string key = "";
	// initialize the integer variable val to 1
   	int val = 1;

	// reads lines from the input stream in into the variable key
   	while (getline(in, key)) {
		// set the value associated with key to current value of val in dictionary D
   		D.setValue(key, val);
		// increment the value of val
   		val++;
   	}
	// outputs entire contents of dictionary D to output stream out
   	out << D << endl;
   	out << D.pre_string();

	// close open infile and outfile
   	in.close();
   	out.close();

	return 0;
}


