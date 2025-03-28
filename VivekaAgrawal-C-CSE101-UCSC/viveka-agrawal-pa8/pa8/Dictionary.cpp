/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa8
-----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

#define BLACK 0
#define RED 1

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = BLACK;
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
		// check if R is red
		if (R->color == RED) {
                        s += R->key + " (RED)" "\n";
                }
                else {
                        s += R->key + "\n";
                }

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

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
	// N becomes the left child of M
	Node* M = N->right; 
   	N->right = M->left; 
   
	// check if left child of node M exists
   	if (M->left != nil) {
		// updates the parent pointer of the left child of M to point to N
   		M->left->parent = N; 
   	}
   	
	// updates the parent pointer of node M to point to the parent of node N
   	M->parent = N->parent; 
   
	// check if node N is the root
   	if (N->parent == nil) {
		// updates the root of the tree to be node M
   		root = M; 
   	}

	// check if node N is the left child of its parent
   	else if (N == N->parent->left) {
		// updates the left child of N's parent to be M
   		N->parent->left = M; 
   	}

	// else node N is the right child of its parent 
   	else {
		// updates the right child of N's parent to be M
   		N->parent->right = M; 
   	}
   
	// completes the left rotation by updating the left child of M to be node N
   	M->left = N;
        // updates the parent pointer of node N to point to M	
   	N->parent = M; 
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
	// N becomes the right child of M
   	Node* M = N->left; 
   	N->left = M->right; 
   
	// check if right child of node M exists
   	if (M->right != nil) {
		// updates the parent pointer of the right child of M to point to N
   		M->right->parent = N; 
   	}
   
	// updates the parent pointer of node M to point to the parent of node N
   	M->parent = N->parent; 
   
	// check if node N is the root
   	if (N->parent == nil) {
		// updates the root of the tree to be node M
   		root = M; 
   	}
	
	// check if node N is the right child of its parent
   	else if (N == N->parent->right) {
		// updates the right child of N's parent to be M
   		N->parent->right = M; 
	}

	// else node N is the left child of its parent 
   	else {
		// updates the left child of N's parent to be M
   		N->parent->left = M; 
   	}
   
	// completes the right rotation by updating the right child of M to be node N
   	M->right = N; 
        // updates the parent pointer of node N to point to M	
   	N->parent = M; 
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
	// iterates as long as the parent of node N is the color red
	while (N->parent->color == RED) {
		// check if the parent of node N is the left child of its grandparent 
   		if (N->parent == N->parent->parent->left) {
			// creates and assigns pointer M the value of the right child of the grandparent of node N
   			// M represents the uncle of N in the red-black tree
			Node* M = N->parent->parent->right; 
   		
			// check if uncle (M) of node N is red
   			if (M->color == RED) {
				// parent and uncle are both red
				// colors are adjusted to restore the red-black tree properties
   				N->parent->color = BLACK; 
   				M->color = BLACK; 
   				N->parent->parent->color = RED; 
   				N = N->parent->parent; 
   			}

			// uncle (M) of node N is not red 
   			else {
				// parent and uncle have different colors
				// depending on relative positions of N, its parent, and its grandparent, 
				// rotation (either left or right) is performed to restore the red-black tree properties
				if (N == N->parent->right) {
   					N = N->parent; 
   					LeftRotate(N); 
   				}	
   				N->parent->color = BLACK; 
   				N->parent->parent->color = RED; 
   				RightRotate(N->parent->parent); 
   			}
   		}

		// check if the parent of node N is the right child of its grandparent 
   		else {
			// creates and assigns pointer M the value of the left child of the grandparent of node N
   			// M represents the uncle of N in the red-black tree
   			Node* M = N->parent->parent->left; 
   		
			// check if uncle (M) of node N is red
   			if (M->color == RED) {
				// parent and uncle are both red
				// colors are adjusted to restore the red-black tree properties
   				N->parent->color = BLACK; 
   				M->color = BLACK; 
   				N->parent->parent->color = RED; 
   				N = N->parent->parent; 
   			}
			
			// uncle (M) of node N is not red 
   			else {
				// parent and uncle have different colors
				// depending on relative positions of N, its parent, and its grandparent, 
				// rotation (either left or right) is performed to restore the red-black tree properties
   				if (N == N->parent->left) {
   					N = N->parent; 
   					RightRotate(N); 
   				}	
   				N->parent->color = BLACK; 
   				N->parent->parent->color = RED; 
   				LeftRotate(N->parent->parent); 
   			}
   		}
   	}
   	
	// color of root set to black as per RBT rules  
   	root->color = BLACK; 
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
	// check if node u is the root of the tree 
	if (u->parent == nil) {
		// updates the root of the tree to be node v
   		root = v; 
   	}
	// check if node u is the left child of its parent
   	else if (u == u->parent->left) {
		// updates the left child of u's parent to be node v
   		u->parent->left = v; 
   	}
	// else node u is the right child of its parent
   	else {
		// updates the right child of u's parent to be node v
   		u->parent->right = v; 
   	}
   
	// updates the parent pointer of node v to be the same as the parent pointer of node u
   	v->parent = u->parent; 
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
	// iterates as long as N is not the root and N has the color black
   	while (N != root && N->color == BLACK) {
		// check if N is the left child of its parent
   		if (N == N->parent->left) {
   			// create and assign pointer M and assigns it the value of the right child of the parent of node N
			// M represents the sibling of N
			Node* M = N->parent->right; 
			// check if sibling (M) of node N is red
   			if (M->color == RED) {
				// adjusts colors and performs a left rotation to make the sibling black
   				M->color = BLACK; 
   				N->parent->color = RED; 
   				LeftRotate(N->parent); 
   				M = N->parent->right; 
   			}
   		
			// check if both the left and right children of M are black
   			if (M->left->color == BLACK && M->right->color == BLACK) {
   				// changes the color of M to red and moves up the tree
				M->color = RED; 
   				N = N->parent; 
   			}
			// else if both are not black
   			else {
				// further checks and performs right rotations to balance the tree
   				if (M->right->color == BLACK) {
   					M->left->color = BLACK; 
   					M->color = RED; 
   					RightRotate(M); 
   					M = N->parent->right; 
   				}
   			
				// adjusts colors and performs a left rotation to make the sibling black
   				M->color = N->parent->color; 
   				N->parent->color = BLACK; 
   				M->right->color = BLACK; 
   				LeftRotate(N->parent); 
   				N = root; 
   			}
   		}

		// else N is the right child of its parent
   		else {
   			// create and assign pointer M and assigns it the value of the left child of the parent of node N
			// M represents the sibling of N
   			Node* M = N->parent->left; 
			// check if sibling (M) of node N is red
   			if (M->color == RED) {
				// adjusts colors and performs a right rotation to make the sibling black
   				M->color = BLACK; 
   				N->parent->color = RED; 
   				RightRotate(N->parent); 
   				M = N->parent->left; 
   			}
   		
			// check if both the left and right children of M are black
   			if (M->right->color == BLACK && M->left->color == BLACK) {
   				// changes the color of M to red and moves up the tree
   				M->color = RED; 
   				N = N->parent; 
   			}
			
			// else if both are not black
   			else {
				// further checks and performs left rotations to balance the tree
   				if (M->left->color == BLACK) {
   					M->right->color = BLACK; 
   					M->color = RED; 
   					LeftRotate(M); 
   					M = N->parent->left; 
   				}
				
				// adjusts colors and performs a right rotation to make the sibling black
   				M->color = N->parent->color; 
   				N->parent->color = BLACK; 
   				M->left->color = BLACK; 
   				RightRotate(N->parent); 
   				N = root; 
   			}
   		}
   	}
   
	// color of root set to black as per RBT rules  
   	N->color = BLACK; 
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
	// M set to the node N that will be deleted   
	Node* M = N; 
	// X will be used as a placeholder for the node to replace N
   	Node* X; 
	// c stores the color of node M before any changes
   	int c = M->color; 
   
	// check if left child of node N has either one child or no children at all on the left side
   	if (N->left == nil) {
		// assigns the right child of N to X
   		X = N->right;
	        // calls the RB_Transplant function to replace node N with its right child X	
   		RB_Transplant(N, N->right); 
   	}
	// check if right child of node N has either one child or no children at all on the right side
   	else if (N->right == nil) {
		// assigns the left child of N to X
   		X = N->left; 
	        // calls the RB_Transplant function to replace node N with its left child X	
   		RB_Transplant(N, N->left); 
   	}
	// else N has 2 children 
   	else {
		// find the minimum node in the right subtree of N
   		M = findMin(N->right); 
		// store color of node M before any changes
   		c = M->color; 
		// assigns right child of M to X
   		X = M->right; 
   	
		// check if the parent of M is N
   		if (M->parent == N) {
			// updates the parent pointer of X to M
   			X->parent = M; 
   		}
		// else parent of M is not N
   		else {
			// replaces M with its right child using RB_Transplant
   			RB_Transplant(M, M->right); 
   			M->right = N->right; 
   			M->right->parent = M; 
   		}
   	
		// adjusts the pointers and colors to move M into the position of N in the red-black tree
   		RB_Transplant(N, M); 
   		M->left = N->left; 
   		M->left->parent = M; 
   		M->color = N->color; 
   	}
   
	// check if color of the original node M was black
   	if (c == BLACK) {
		// calls the RB_DeleteFixUp function to fix any violations of the red-black tree properties
		// that may have occurred after the deletion
   		RB_DeleteFixUp(X); 
   	}
   
	// delete node N
   	delete N; 
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

	// remove the left and right children of N and set its color to red
	N->left = nil; 
	N->right = nil; 
	N->color = RED; 
	RB_InsertFixUp(N);

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
	RB_Delete(N); 
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

