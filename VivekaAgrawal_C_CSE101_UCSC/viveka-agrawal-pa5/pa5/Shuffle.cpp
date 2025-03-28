/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa5
-----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "List.h"

using namespace std;

void shuffle(List& D) {
	int len = D.length(); // stores length of the passed in List
	int left, right; // represent the left and the right side of the deck after the split
	List A, B, C; // creating 3 new objects of type List

	// check if the length of the List is odd
	if (len % 2 == 1) {
		left = len / 2;
		// right side of the split will have 1 more element than the left side
		right = left + 1;
	}

	// check if the length of the List is even
	else {
		// left side and right side of the split will be equal 
		left = right = len / 2;
	}

	// move to the front of the passed in List
	D.moveFront();

	// add cards to the left deck A from the passed in List D 
	for (int i = 0; i < left; i++) {
		// insert in List A the element which is next to the cursor in the passed in List  
		A.insertBefore(D.peekNext());
		// move to the next element in the passed List
		D.moveNext();
	}

	// add cards to the right deck B from the passed in List D 
	for (int i = 0; i < right; i++) {
		// insert in List B the element which is next to the cursor in the passed in List  
		B.insertBefore(D.peekNext());
		// move to the next element in the passed List
		D.moveNext();
	}

	// move to front of Lists A and B
	A.moveFront(); // left deck
	B.moveFront(); // right deck

	// merge the left deck and right deck to create List C
	// for number of cards in the left deck
	for (int i = 0; i < left; i++) {
		// insert in List C the element which is next to the cursor in the right deck  
		C.insertBefore(B.peekNext());
		// insert in List C the element which is next to the cursor in the left deck  
		C.insertBefore(A.peekNext());
		// move to next element in the left deck
		A.moveNext();
		// move to next element in the right deck
		B.moveNext();
	}

	// if the length of the passed in List is odd
	// the right deck will have 1 more card than the left deck  
	if (right > left) {
		// insert in List C the last element which is next to the cursor in the right deck  
		C.insertBefore(B.peekNext());
	}

	// set the passed in List equal as the shuffled List C
	D = C;
}

int main(int argc, char * argv[]) {

	// check for 2 command line arguments
	if (argc != 2) {
		// write the error message to the error stream
      		cerr << "Usage: " << argv[0] << " <positive integer>" << endl;
      		return(EXIT_FAILURE);
   	}

	// read the maximum number of cards in the deck
	// store that value as an integer
   	int number = stoi(argv[1]);

        // print to standard output 	
   	cout << "deck size       shuffle count\n";
   	cout << "------------------------------\n";

	// perform shuffles in the range 1 up to the maximum number 
   	for (int i = 1; i <= number; i++) {
   		int shuffle_count = 1;
   		List A, B; // create 2 objects of type List

		// create deck size 
   		for (int j = 1; j <= i; j++) {
			// List A stores original order
   			A.insertBefore(j);
			// List B is shuffled
   			B.insertBefore(j);
   		}

		// perform shuffle on List B
   		shuffle(B);

		// check if the List B is brought back to its original order as List A
		// if not, keep performing shuffles on List B
   		while (!A.equals(B)) {
   			shuffle(B);
   			shuffle_count++;
   		}

		// print deck size and number of shuffles to standard output
   		cout << " " << i << setw(15) << shuffle_count << endl;
   	}
	return 0;
}
