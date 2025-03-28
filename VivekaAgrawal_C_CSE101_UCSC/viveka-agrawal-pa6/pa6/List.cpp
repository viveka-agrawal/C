/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa6
-----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List() {
	// dummy value for frontDummy node
	frontDummy = new Node(1111);
	// dummy value for backDummy node
	backDummy = new Node(2222);
	
	// specify empty state of List

	// set front and back dummy nodes to point to each other
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	
	// set initial values of beforeCursor and afterCursor
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	
	// set initial position of cursor
	pos_cursor = 0;
	// set initial number of elements to 0
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
	// makes a copy of the passed in argument
	frontDummy = new Node(1111);
	backDummy = new Node(2222);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

	// create a pointer N to point to the first Node of List L to be copied
	Node* N = L.frontDummy->next;

	// traverse List L copying Nodes from List L to the newly created List N
   	while (N != L.backDummy) {
		// insert a new Node in the new List N copying the data from Node in List L to Node in List N 
      		this->insertBefore(N->data);
		// move to the next Node
      		N = N->next;
   	}
}

// Destructor
List::~List() {
	// delete all the elements in the List
	clear();
	delete frontDummy;
	delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
	if (num_elements <= 0) {
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::length_error("List: front(): empty list");
   	}
	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
	if (num_elements <= 0) {
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::length_error("List: back(): empty list");
   	}
	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	// can't peek at next element if at back of List
	if (pos_cursor >= num_elements) {
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: peekNext(): cursor at back");
   	}
   	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	// can't peek at previous element if at front of List
	if (pos_cursor <= 0){
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: peekPrev(): cursor at front");
   	}
   	return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	// move to the front of the List and start deleting elements in the List
	moveFront();
	while (num_elements > 0) {
		eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	pos_cursor = 0;
	// beforeCursor points to frontDummy node
	beforeCursor = frontDummy;
	// afterCursor points to first element in the List
	afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	pos_cursor = num_elements;
	// beforeCursor points to last element in the List
	beforeCursor = backDummy->prev;
	// afterCursor points to backDummy node
	afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
	// position of cursor can't be at the end of the List or beyond that
	if (pos_cursor >= num_elements) {
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: moveNext(): cursor at back");
   	}

   	pos_cursor++;
	// beforeCursor points to afterCursor
   	beforeCursor = afterCursor;
	// afterCursor points to the next node after afterCursor
   	afterCursor = afterCursor->next;

   	return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
	// position of cursor can't be at the front of the List or before that
	if (pos_cursor <= 0) {
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: movePrev(): cursor at front");
   	}

   	pos_cursor--;
	// beforeCursor points to the previous node before beforeCursor
   	beforeCursor = beforeCursor->prev;
	// afterCursor points to previous node before afterCursor
   	afterCursor = afterCursor->prev;

   	return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
	// allocate dynamic memory for new Node N
   	Node* N = new Node(x);

	// update beforeCursor and afterCursor pointers to point to new Node N
   	beforeCursor->next = N;
   	afterCursor->prev = N;

	// update the previous and next nodes of Node N to be beforeCursor and afterCursor
   	N->prev = beforeCursor;
   	N->next = afterCursor;

	// afterCursor then becomes N
   	afterCursor = N;
   	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
	// allocate dynamic memory for new Node N
	Node* N = new Node(x);

	// update beforeCursor and afterCursor pointers to point to new Node N
	beforeCursor->next = N;
   	afterCursor->prev = N;

	// update the previous and next nodes of Node N to be beforeCursor and afterCursor
   	N->prev = beforeCursor;
   	N->next = afterCursor;

	// beforeCursor then becomes N
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	// position of cursor can't be at the end of the List or beyond that
	if (pos_cursor >= num_elements){
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: setAfter(): cursor at back");
   	}
   	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	// position of cursor can't be at the front of the List or before that
	if (pos_cursor <= 0){
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: setBefore(): cursor at front");
   	}
   	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	// position of cursor can't be at the end of the List or beyond that
	if (pos_cursor >= num_elements){
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: eraseAfter(): cursor at back");
   	}

	// create a new pointer N to point to Node pointed to by afterCursor
   	Node* N = afterCursor;

	// need to delete the node pointed to by afterCursor
	
	// point the previous pointer of the node after afterCursor to beforeCursor  
   	afterCursor->next->prev = beforeCursor;
	// point afterCursor to the node after afterCursor
   	afterCursor = afterCursor->next;
	// point node after beforeCursor to the node which was after afterCursor
   	beforeCursor->next = afterCursor;

   	num_elements--;
   	delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	// position of cursor can't be at the front of the List or before that
	if (pos_cursor <= 0){
		// throw an error exception using the <stdexcept> c++ library 
      		throw std::range_error("List: eraseBefore(): cursor at front");
   	}

	// create a new pointer N to point to Node pointed to by beforeCursor
   	Node* N = beforeCursor;

	// need to delete the node pointed to by beforeCursor
	
	// point the previous pointer of the node before beforeCursor to afterCursor  
   	beforeCursor->prev->next = afterCursor;
	// point beforeCursor to the node before beforeCursor
   	beforeCursor = beforeCursor->prev;
	// point node before afterCursor to the node which was before beforeCursor
   	afterCursor->prev = beforeCursor;

   	pos_cursor--;
   	num_elements--;
   	delete N;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
	Node* N = afterCursor;

	// traverse the List starting at the node pointed to by afterCursor
	while (N != backDummy) {
		if (N->data == x) {
			moveNext();
			return pos_cursor;
		}

		// if x not found, keep traversing the List from left to right
		moveNext();
		N = N->next;
	}

	// place the cursor at position length()
	pos_cursor = num_elements;
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
	Node* N = beforeCursor;

	// traverse the List starting at the node pointed to by beforeCursor
	while (N != frontDummy) {
		if (N->data == x) {
			movePrev();
			return pos_cursor;
		}

		// if x not found, keep traversing the List from right to left
		movePrev();
		N = N->prev;
	}

	// place the cursor at position 0
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
	// start at the first element in the List
	Node* N = frontDummy->next;
	int cursor = 1;

	// traverse the List from front to back starting at the 1st element in the List
	while (N != backDummy) {
		Node* M = N->next;
		int current_cursor = cursor + 1;

		// traverse the List starting from the 2nd element in the List
		while (M != backDummy) {
			if (M->data == N->data) {
				// if node M is the node before the cursor decrement the cursor 
				// and update this List to skip repeated element
				if (M == beforeCursor) {
					beforeCursor->prev->next = afterCursor;
   					beforeCursor = beforeCursor->prev;
   					afterCursor->prev = beforeCursor;
   					pos_cursor--;
				}
				// if node M is the node after the cursor 
				// update this List to skip repeated element
				else if (M == afterCursor) {
					afterCursor->next->prev = beforeCursor;
   					afterCursor = afterCursor->next;
   					beforeCursor->next = afterCursor;
				}
				// if node M is before the cursor decrement the cursor position
				else if (current_cursor < pos_cursor) {
					pos_cursor--;
				}

				// remove repeated element M from this List 
				M->prev->next = M->next;
				M ->next->prev = M->prev;
				// decrement the number of elements 
				num_elements--;
				Node* D = M;
				M = M->next;
				// free the memory for the deleted node
				delete D;
			}
			// if elements are not equal move to the next element
			else {
				M = M->next;
			}
			current_cursor++;
		}
		N = N->next;
		cursor++;
	}
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
	// create a new object K of type List
	List K;
	// create a pointer N to point to the 1st element of List K
   	Node* N = this->frontDummy->next;
	// create a pointer M to point to the 1st element of List L
   	Node* M = L.frontDummy->next;

	// traverse List K starting from the 1st element in the List until 
	// backDummy element is reached
   	while (N != backDummy) {
		// add the elements from List K to the concatenated List
      		K.insertBefore(N->data);
      		N = N->next;
   	}
	
	// traverse List L starting from the 1st element in the List until 
	// backDummy element is reached
   	while (M != L.backDummy) {
		// add the elements from List L to the concatenated List
      		K.insertBefore(M->data);
      		M = M->next;
   	}
	// move to the front of the concatenated List at position 0
   	K.moveFront();
   	return K;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
	// create a pointer N to point to the 1st element of the List
	Node* N = frontDummy->next;
	// create a new string s with opening parentheses
   	std::string s = "(";

	// traverse the List starting from the 1st element in the List until 
	// backDummy element is reached
   	while (N != backDummy) {
		// check if at the end of the List
   		if (N->next == backDummy) {
   			s += std::to_string(N->data) + ")";
   		}
		// check for multiple elements in the List
		// add them to string s separated by commas
   		else {
   			s += std::to_string(N->data) + ", ";
   		}
		// move to the next element in the List
   		N = N->next;
   	}
   	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	bool equal = false;
	// create a pointer N to point to the 1st element of this List
   	Node* N = this->frontDummy->next;
	// create a pointer M to point to the 1st element of List R
   	Node* M = R.frontDummy->next;

	// check if number of elements in this List and List R are the same
	// if they are, set equal to the number of elements in the List
   	equal = (this->num_elements == R.num_elements);

	// traverse this List and List R from left to right
	// if number of elements in this List and List R are the same
   	while (equal && N != backDummy) {
		// compare each element in this List and List R
      		equal = (N->data == M->data);
      		N = N->next;
      		M = M->next;
   	}
   	return equal;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B) {
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L) {
	// only the attributes of this List are set as the same attributes of List L
	if (this != &L) {
      		List temp = L;
      		std::swap(frontDummy, temp.frontDummy);
      		std::swap(backDummy, temp.backDummy);
      		std::swap(beforeCursor, temp.beforeCursor);
      		std::swap(afterCursor, temp.afterCursor);
      		std::swap(pos_cursor, temp.pos_cursor);
      		std::swap(num_elements, temp.num_elements);
   	}
	// the elements of this List are not overwritten with elements of List L
   	return *this;
}


