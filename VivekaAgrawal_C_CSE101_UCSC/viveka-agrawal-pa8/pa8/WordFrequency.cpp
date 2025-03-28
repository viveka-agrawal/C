/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa8
-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {

	ifstream in;
   	ofstream out;

	// check for 3 command line arguments	
	if (argc != 3) {
      		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      		return(EXIT_FAILURE);
   	}
  
        // open infile for reading	
   	in.open(argv[1]);
	// if infile is not open, throw error
   	if (!in.is_open()) {
      		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      		return(EXIT_FAILURE);
   	}
   
	// open outfile for writing
   	out.open(argv[2]);
	// if outfile is not open, throw error
   	if (!out.is_open()) {
      		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      		return(EXIT_FAILURE);
   	}

        // define set of delimiters for tokenizing the input string
	// declare variables for processing lines, tokenization, and creating a Dictionary object (D)	
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
	string line = ""; 
	size_t len, begin, end; 
	string buffer; 
	string token; 
	Dictionary D; 
	locale loc; 
	
	// read lines from the input file (in) and processes each line
	while (getline(in, line)) {
		len = line.length(); 
		// use find_first_not_of and find_first_of to find the beginning and end of each token 
		// in the line based on the specified delimiters
		begin = min(line.find_first_not_of(delim, 0), len); 
		end = min(line.find_first_of(delim, begin), len); 
		token = line.substr(begin, end - begin); 

		// iterate while token is not an empty		
		while (token != "") {
			// convert each token to lowercase using transform
			transform(token.begin(), token.end(), token.begin(), ::tolower);
		
			// update Dictionary object (D) with the frequency of each token	
			if (D.contains(token)) {
				D.setValue(token, D.getValue(token) + 1); 
			}
			else {
				D.setValue(token, 1); 
			}
			
			begin = min(line.find_first_not_of(delim, end + 1), len); 
			end = min(line.find_first_of(delim, begin), len); 
			token = line.substr(begin, end - begin); 
		}
	}
	
	// writes the contents of the Dictionary object to the output file
	out << D << endl; 
   
	// close open infile and outfile
   	in.close();
   	out.close();

	return 0; 
}
