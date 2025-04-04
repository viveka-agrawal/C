/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa7
-----------------------------------------------------------------------------*/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   	string s;
   	int x;
   	string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};

   	Dictionary A;
   	Dictionary B;

   	cout << endl;

   	// insert some pairs into A
   	for (int i=0; i<8; i++) {
      		A.setValue(S[i], i + 1);
   	}
   
   	// call operator=()
   	B = A;

   	cout << "A.size() = " << A.size() << endl  << A << endl;
   	cout << "B.size() = " << B.size() << endl  << B << endl;

   	B.setValue("bar", 9);

   	// call copy constructor
   	Dictionary C = B;

   	cout << "B.size() = " << B.size() << endl  << B << endl;
   	cout << "C.size() = " << C.size() << endl  << C << endl;

   	// check operator==()
   	cout << "A==B is " << (A==B?"true":"false") << endl;
   	cout << "B==C is " << (B==C?"true":"false") << endl;
   	cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   	// perform alterations on A
   	cout << A.getValue("happy") << endl;
   	A.getValue("happy") *= 10; // change the value associated with "happy"
   	cout << A.getValue("happy") << endl << endl;
   	A.remove("one");
   	A.remove("two");

   	// check state of A
   	cout << "A.size() = " << A.size() << endl  << A << endl;
   	cout << A.pre_string() << endl;

   	// do forward iteration on B
   	for (B.begin(); B.hasCurrent(); B.next()) {
      		s = B.currentKey();
      		x = B.currentVal();
      		cout << "("+s+", " << x << ") ";
   	}
   	cout << endl << endl;

   	// do reverse iteration on C
   	for (C.end(); C.hasCurrent(); C.prev()) {
      		s = C.currentKey();
      		x = C.currentVal();
      		cout << "("+s+", " << x << ") ";
   	}
   	cout << endl << endl;
   
   	// check exceptions
   	try {
      		A.getValue("four");
   	} catch(logic_error& e) {
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try {
      		A.remove("four");
   	} catch(logic_error& e) {
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try {
      		A.currentKey();
   	} catch(logic_error& e) {
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try {
      		A.currentVal();
   	} catch(logic_error& e) {
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}  
   	try {
      		A.next();
   	} catch(logic_error& e) {
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try {
      		A.prev();
   	} catch(logic_error& e) {
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}

   	cout << endl;  
   
   	A.clear(); 
   	B.clear(); 
   	C.clear(); 
   
   	cout << "empty size: " << A.size() << endl; 
   	cout << "empty contains: " << A.contains("x1") << endl; 
   	cout << "empty hasCurrent: " << A.hasCurrent() << endl; 
   
   	A.setValue("x1", 1109); 
   	A.setValue("x2", 2001); 
   	A.setValue("x3", 2002); 
   	A.setValue("x4", 620); 
   	A.setValue("x5", 723); 
   
   	cout << A << endl; 
   	
   	cout << "A size: " << A.size() << endl; 
   	cout << "contains: " << A.contains("x1") << endl; 
   
   	A.begin(); 
   	
   	cout << "hasCurrent: " << A.hasCurrent() << endl; 
   	cout << "currentKey: " << A.currentKey() << endl; 
   	cout << "currentVal: " << A.currentVal() << endl; 
   	cout << "getValue: " << A.getValue("x4") << endl; 
   
   	A.remove("x1"); 
   
   	cout << A << endl;
   
   	A.end(); 
   
   	cout << "hasCurrent: " << A.hasCurrent() << endl; 
   	cout << "currentKey: " << A.currentKey() << endl; 
   	cout << "currentVal: " << A.currentVal() << endl; 
   
   	A.prev(); 
   
   	cout << "hasCurrent: " << A.hasCurrent() << endl; 
   	cout << "currentKey: " << A.currentKey() << endl; 
   	cout << "currentVal: " << A.currentVal() << endl; 
   
   	A.next(); 
   
   	cout << "hasCurrent: " << A.hasCurrent() << endl; 
   	cout << "currentKey: " << A.currentKey() << endl; 
   	cout << "currentVal: " << A.currentVal() << endl; 
   
   	cout << (A == B) << endl;
   
   	B = A; 
   
   	cout << (A == B) << endl; 
   
   	cout << B.pre_string() << endl;

   	return( EXIT_SUCCESS );
}
