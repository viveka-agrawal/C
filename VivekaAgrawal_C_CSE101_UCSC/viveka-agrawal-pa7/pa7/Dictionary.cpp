/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa7
-----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	// check if R has children
	if (R != nil) {
		// left subtree is processed before the current node
		inOrderString(s, R->left);
		// represents the key-value pair of the current node in the correct format
		s += R->key;
		s += " : ";
		s += std::to_string(R->val);
		s += "\n";
		// right subtree is processed after the current node
		inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
	// check if R has children
	if (R != nil) {
		// appends the key of the current node and a newline character to string s
		s += R->key + "\n";
		// process left subtree before right subtree
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
	// base case
	if (R == N) {
		return;
	}

	// set the key-value pair in the current node 
	setValue(R->key, R->val);

	// process left subtree before right subtree
	preOrderCopy(R->left, N);
	preOrderCopy(R->right, N);
}

void Dictionary::transplant(Node* U, Node* V) {
	// check if node U has no parent
	if (U->parent == nil) {
		root = V;
	}
	// check if node U is the left child of its parent
	else if (U == U->parent->left) {
		U->parent->left = V;
	}
	// else node U is the right child of its parent
	else {
		U->parent->right = V;
	}
	// updates parent of node V to be parent of node U
	if (V != nil) {
		V->parent = U->parent;
	}
}

void Dictionary::deleteNode(Node* N) {
	// check if node N has no left child
	if (N->left == nil) {
		// replace node N with its right child
		transplant(N, N->right);
	}
	// check if node N has no right child
	else if (N->right == nil) {
		// replace node N with its left child
		transplant(N, N->left);
	}
	// node N has both left and right children
	else {
		// find node with minimum key in right subtree of N and assign it to node M
		Node* M = findMin(N->right);

		// if M is not right child of N
		if (M->parent != N) {
			transplant(M, M->right);
			M->right = N->right;
			M->right->parent = M;
		}

		// replace N with M
		transplant(N, M);
		M->left = N->left;
		M->left->parent = M;
	}
	// delete node N
	delete N;
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
	// check if R has children
	if (R != nil) {
		// deletion process is performed after the left and right subtrees have been deleted 
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		deleteNode(R);
	}
	// R has no children and is nil
	R = nil;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	// check if R has no children or if the key of node R is equal to the passed in key k
	if (R == nil || R->key == k) {
   		return R;
   	}
	// check if the key of Node R is greater than the passed in key k
   	else if (R->key > k) {
		// the key is in the left subtree 
   		return search(R->left, k);
   	}
	// check if the key of Node R is less than the passed in key k
   	else if (R->key < k) {
		// the key is in the right subtree
   		return search(R->right, k);
   	}
	// passed in key k was not found in the subtree
   	return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
	// iterate while a left child of R exists
   	while (R->left != nil) {
		// keep finding left children until no more left children exist
   		R = R->left;
   	}
	// return the leftmost (minimum) child
   	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
	// iterate while a right child of R exists
	while (R->right != nil) {
		// keep finding right children until no more right children exist
   		R = R->right;
   	}
	// return the rightmost (maximum) child
   	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Node* N) {
	// check if node N has a right child
	if (N->right != nil) {
		// find the node with the minimum key in the right subtree
		return findMin(N->right);
	}

	// new node M equal the parent node of N
	Node* M = N->parent;

	// iterate while there is a parent node and while N is the right child of M
	while (M != nil && N == M->right) {
		N = M;
		M = M->parent;
	}
	return M;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
	// check if node N has a left child
	if (N->left != nil) {
		// find the node with the maximum key in the left subtree
		return findMax(N->left);
	}

	// new node M equal the parent node of N
	Node* M = N->parent;

	// iterate while there is a parent node and while N is the left child of M
	while (M != nil && N == M->left) {
		N = M;
		M = M->parent;
	}
	return M;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state.
Dictionary::Dictionary() {
	nil = new Node("", 0);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
   	root = nil;
   	current = nil;
   	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
	nil = new Node("", 0);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
   	root = nil;
   	current = nil;
   	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
	postOrderDelete(root);
	delete nil;
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
	// initialize Node N to store the value of the node with key k in the tree
	Node* N = search(root, k);

	// check if node N contains the key k
	if (N != nil) {
		// node N does have key k
		return true;
	}
	// node N does not have key k
	return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
	// checks if the key k exists in the dictionary
	if (contains(k) == false) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
   	}
	// find the node corresponding to the key k in the tree and store it in new node N
   	Node* N = search(root, k);
	// return the value associated with the key k
   	return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {
	// check if current iterator is defined
	if (current == nil) {
		return false;
	}
	return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
	// check if current iterator is defined
	if (hasCurrent() == false) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::logic_error("Dictionary: currentKey(): current undefined");
   	}
	// return the current key 
   	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
	// check if current iterator is defined
	if (hasCurrent() == false) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::logic_error("Dictionary: currentVal(): current undefined");
   	}
	// return the current value 
   	return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
	// delete all nodes in the subtree 
	postOrderDelete(root);
	num_pairs = 0;
	root = nil;
	current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
	// dynamically allocates a new Node with key k and value v; initialize its left and right children to nil
	Node* N = new Node(k, v);
	N->left = nil;
	N->right = nil;
	// node R is set to the root
	Node* R = root;
	Node* S = nil;

	// iterate while the root is not null
	while (R != nil) {
		S = R;

		// check if key k equals the current node R's key
		if (k == R->key) {
			// set node R's value to the value v
			R->val = v;
			// delete node N
			delete N;
			return;
		}

		// check if node N's key is less than node R's key
		if (N->key < R->key) {
			// set node R equal to its left child
			R = R->left;
		}
		else {
			// set node R equal to its right child
			R = R->right;
		}
	}

	// set the parent of node N to node S
	N->parent = S;

	// check if node N does not have a parent
	if (S == nil) {
		// set N to be the root of the tree
		root = N;
	}
	// check if N's key is less than S's key
	else if (N->key < S->key) {
		// set the left child of S to N
		S->left = N;
	}
	// else N's key is greater than S's key
	else {
		// set the right child of S to N
		S->right = N;
	}

	// increment the number of key-value pairs
	num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
	// check if key k is in the tree
	if (contains(k) == false) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
   	}

	// initialize Node N to store the value of the node with key k in the tree
   	Node* N = search(root, k);

	// check if N is the node that needs to be removed 
   	if (N == current) {
   		current = nil;
   	}

	// delete node N
   	deleteNode(N);
	// decrement the number of key-value pairs
   	num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
	current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
	current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
	// check if the current iterator is defined
	if (hasCurrent() == false) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::logic_error("Dictionary: next(): current not defined");
   	}
	// set the current iterator to the next current
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
	// check if the current iterator is defined
	if (hasCurrent() == false) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::logic_error("Dictionary: prev(): current not defined");
   	}
	// set the current iterator to the previous current
   	current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
	// initialize an empty string to store the string representation of the dictionary
	std::string s = "";
	// append each key-value pair to the string using in-order traversal
	inOrderString(s, root);
	// return the resulting string
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
	// initialize an empty string to store the string representation of the dictionary
	std::string s = "";
	// append each key-value pair to the string using pre-order traversal
	preOrderString(s, root);
	// return the resulting string
	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
	// initialize 2 empty strings; will be used to store string representations of current dictionary and dictionary D 
	std::string s = "";
	std::string d = "";

	// append key-value pairs to both strings
	inOrderString(s, root);
	D.inOrderString(d, D.root);

	// check if the two dictionaries have the same key-value pairs
	bool eq = (s == d);

   	return eq;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary& A, const Dictionary& B) {
	return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=(const Dictionary& D) {
	// check if this Dictionary does equal the state of D
	if (this != &D) {
		// overwrite the state of this Dictionary with the state of D
      		Dictionary temp = D;
      		std::swap(nil, temp.nil);
      		std::swap(root, temp.root);
      		std::swap(current, temp.current);
      		std::swap(num_pairs, temp.num_pairs);
   	}
	// return the reference to current object this
   	return *this;
}
