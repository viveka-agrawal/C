/*----------------------------------------------------------------------------- 
Viveka Agrawal 
viagrawa@ucsc.edu 
pa6
-----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <ctype.h>
#include <regex>
#include "BigInteger.h"

const ListElement base = 1000000000;
const int power = 9; 

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
	signum = 0;
        List digits;	
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
	// string cannot be empty
	if (empty(s)) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::invalid_argument("BigInteger: Constructor: empty string");
   	}
	// string cannot include non-numeric values
	if (s == "+" || s == "-") {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   	}

   	const std::regex pattern("(\\+|-)?[[:digit:]]+");
	// string has to match regex pattern in order to be considered a valid string 
   	if (!std::regex_match(s, pattern)) {
		// throw an error exception using the <stdexcept> c++ library
      		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   	}

	// check if first element of string is a digit	
	if (isdigit(s[0])) {
		// sign of the number is positive
		signum = 1; 
	}
	// check if first element of string is negative sign
	else if (s[0] == '-') {
		// sign of the number is negative
		signum = -1;
	       	// strip off any leading zeros	
		s.erase(0, 1); 
	}
	// check if first element of string is positive sign
	else if (s[0] == '+') {
		// sign of the number is positive
		signum = 1; 
	       	// strip off any leading zeros	
		s.erase(0, 1); 
	}
	
	// strip off any leading zeros	
	const std::regex patterns("^0+(?!$)");
	s = std::regex_replace(s, patterns, "");

	// variable that iterates over substrings of length power in reverse order	
	int l = s.length() - power; 

	// express string as base postional number system  	
	while (l >= 0) {
		digits.insertAfter(stol(s.substr(l, power)));
		l -= power;
	}

	// insert leading zeroes if number of digits is less than length power	
	if (l != 0) {
		l += power; 
		digits.insertAfter(stol(s.substr(0, l)));
	} 
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum;
	digits = N.digits; 
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
	return signum; 
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
	// comparing the signs of passed in BigInteger N and this BigInteger
	
	if (signum == 0 && N.signum == 0) {
		return 0; 
	}
	else if (signum < N.signum) {
		return -1; 
	}
	else if (signum > N.signum) {
		return 1; 
	}
	
	// comparing the digits of passed in BigInteger N and this BigInteger
	
	List A = digits; // stores digits of this BigInteger
	List B = N.digits; // stores digits of passed in BigInteger N  
	
	if (A.equals(B)) {
		return 0; 
	}
	
	if (A.length() < B.length()) {
		return -1; 
	}
	else if (A.length() > B.length()) {
		return 1; 
	}
	
	// move to the front of both Lists
	A.moveFront(); 
	B.moveFront(); 
	
	// traverse List A from left to right
	while (A.position() <= A.length()) {
		// check if the element in List A is less than the element in List B
		if (A.peekNext() < B.peekNext()) {
			return -1; 
		}
		// check if the element in List A is greater than the element in List B
		else if (A.peekNext() > B.peekNext()) {
			return 1; 
		}
		// move to the next element in both Lists	
		A.moveNext(); 
		B.moveNext(); 
	}	
	return 0; 
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
	signum = 0; 
	digits.clear(); 
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
	signum *= -1;
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger sum; 
	List L; // List to store added values
	List A = digits; 
	List B = N.digits; 
	long carryover = 0; 

	// sign of both this and N are negative	
	if (signum == -1 && N.signum == -1) {
		sum.signum = -1; 
	}
	// only this BigInteger is negative
	else if (signum == -1) {
		BigInteger C = *this; 
		C.signum = 1; 
		// subtract C from N since C is negative to mimic addition (N-(-C) == N + C) 
		BigInteger D = N - C; 
		return D; 
	}
	// only passed in BigInteger N is negative
	else if (N.signum == -1) {
		BigInteger C = N; 
		C.signum = 1; 
		// subtract C from *this since C is negative to mimic addition (*this-(-C) == *this + C) 
		BigInteger D = *this - C; 
		return D; 
	}
	// BigInteger sum is positive otherwise
	else {
		sum.signum = 1; 
	}

	// move to the end of both Lists
	A.moveBack(); 
	B.moveBack(); 
	
	// iterate from right to left over both Lists adding the elements and carryovers if any
	while (A.position() > 0 && B.position() > 0) {
		long addvalue = A.peekPrev() + B.peekPrev() + carryover; 
		
		if (addvalue >= base) {
			carryover = 1; 
			addvalue -= base; 
		}
		else {
			carryover = 0; 
		}
		
		L.insertAfter(addvalue);

	        // move to previous elements in both Lists	
		A.movePrev(); 
		B.movePrev(); 
	}
	
	// iterate from right to left in List A over the remaining elements in List A
	while (A.position() > 0) {
		long addvalue = A.peekPrev() + carryover; 
		
		if (addvalue >= base) {
			carryover = 1; 
			addvalue -= base; 
		}
		else {
			carryover = 0; 
		}
		
		L.insertAfter(addvalue); 
	        // move to previous element in List A	
		A.movePrev(); 
	}
	
	// iterate from right to left in List B over the remaining elements in List B
	while (B.position() > 0) {
		long addvalue = B.peekPrev() + carryover; 
		
		if (addvalue >= base) {
			carryover = 1; 
			addvalue -= base; 
		}
		else {
			carryover = 0; 
		}
		
		L.insertAfter(addvalue);
	        // move to previous element in List B	
		B.movePrev(); 
	}
	
	// add any remaining carryovers
	if (carryover == 1) {
		L.insertAfter(carryover); 
	}
	
	// set the digits of added BigInteger sum to List L
	sum.digits = L; 
	return sum;  
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger diff; 
	List L, A, B; 
	long carryover = 0;
        // compare this BigInteger with passed in BigInteger N	
	int i = compare(N); 
	
	// sign of both this and N are negative	
	if (signum == -1 && N.signum == -1) {
		BigInteger C = N;
	        // make C positive to add a negative and a positive number together to mimic subtraction	
		C.signum = 1; 
		// -*this - (-C) turns into -this* + C  
		BigInteger D = *this + C; 
		return D; 
	}
	// sign of this is negative and sign of N is positive
	else if (signum == -1 && N.signum == 1) {
		BigInteger C = N; 
	        // make C negative to add a negative and a positive number together to mimic subtraction	
		C.signum = -1; 
		// -*this - C turns into -this* - (-C) which is -*this + C  
		BigInteger D = *this + C; 
		return D; 
	}
	// only sign of passed in BigInteger N is negative 
	else if (N.signum == -1) {
		BigInteger C = N; 
	        // make C negative to add a negative and a positive number together to mimic subtraction	
		C.signum = 1; 
		// -*this - C turns into -this* - (-C) which is -*this + C  
		BigInteger D = *this + C; 
		return D; 
	}
	// if this BigInteger and BigInteger N have the same number of digits
	if (i == 0) {
		return diff; 
	}
	// if BigInteger N has more digits than this BigInteger
	else if (i == -1) {
		A = N.digits; 
		B = digits; 
		diff.signum = -1; 
	}
	// if BigInteger N has less digits than this BigInteger	
	else {
		A = digits; 
		B = N.digits; 
		diff.signum = 1; 
	}

	// move to the end of both Lists	
	A.moveBack(); 
	B.moveBack(); 
	
	// iterate from right to left over both Lists subtracting the elements and adding carryovers if any
	while (A.position() > 0 && B.position() > 0) {
		long subvalue = A.peekPrev() - B.peekPrev() + carryover; 
		carryover = 0; 
		
		while (subvalue < 0) {
			carryover--; 
			subvalue += base; 
		}
		
		L.insertAfter(subvalue);
	        // move to previous element in both Lists	
		A.movePrev(); 
		B.movePrev(); 
	}
	
	// iterate from right to left in List A over the remaining elements in List A
	while (A.position() > 0) {
		long subvalue = A.peekPrev() + carryover; 
		carryover = 0; 
		
		while (subvalue < 0) {
			carryover--; 
			subvalue += base; 
		}
		
		L.insertAfter(subvalue); 
	        // move to previous element in List A	
		A.movePrev(); 
	}
	
	// iterate from right to left in List B over the remaining elements in List B
	while (B.position() > 0) {
		long subvalue = B.peekPrev() + carryover; 
		carryover = 0; 
		
		while (subvalue < 0) {
			carryover--; 
			subvalue += base; 
		}
		
		L.insertAfter(subvalue); 
	        // move to previous element in List B	
		B.movePrev(); 
	}
	
	// set the digits of subtracted BigInteger diff to List L
	diff.digits = L; 
	return diff; 
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger product; 
	// if sign of this or N are 0	
	if (signum == 0 || N.signum == 0) {
		return product; 
	}
	
	BigInteger temp; 
	List L; 
	List A = digits; 
	List B = N.digits; 
	int end = 0; 
	long carryover = 0; 

	// move to last element in List A	
	A.moveBack(); 

	// iterate from right to left in List A	
	for (int i = 0; i < A.length(); i++) {
		long a = A.peekPrev(); 
		// move to last element in List B
		B.moveBack(); 
		// insert 0's in the List to mimic multiplication
		for (int j = 0; j < end; j++) {
			L.insertAfter(0); 
		}
		// iterate from right to left in List B
		for (int k = 0; k < B.length(); k++) {
			// multiply element from List A with element from List B and add any carryovers
			long p = (a * B.peekPrev()) + carryover; 
			
			// check if there are any carryovers
			if (p >= base) {
				long t = p;  
				p %= base; 
				carryover = (t - p) / base; 
			}
			else {
				carryover = 0; 
			}
			
			L.insertAfter(p);
		        // move to previous element in List B	
			B.movePrev(); 
		}
		// add carryover to List L
		if (carryover != 0) {
			L.insertAfter(carryover); 
		}
		// reset carryover		
		carryover = 0; 
		// move to previous element in List A
		A.movePrev(); 
		end++; 
		// store digits from List L into BigInteger temp
		temp.digits = L;
	        // add value of BigInteger temp to the final BigInteger product	
		product += temp; 
		// clear List L
		L.clear(); 
	}

	// multiply the sign of BigIntegers this and N to find out sign of BigInteger product	
	product.signum = signum * N.signum; 
	return product; 
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
	// initialize s to empty string
	std::string s = ""; 
	// if sign of this BigInteger is negative add a "-" at the beginning of the string
	if (signum == -1) {
		s += "-";
	}
	// if this BigInteger is 0 return the character '0' only
	else if (signum == 0) {
		s += "0";
		return s; 
	}
	// store digits in List L
	List L = digits;
        // move to front of List L	
	L.moveFront();
        // initialize t to empty string	
	std::string t = ""; 

	// iterate over List L from left to right
	while (L.position() < L.length()) {
		// if at first element in the List
		if (L.position() == 0) {
			// add elements from List L to string t in order
			t += std::to_string(L.peekNext()); 
			L.moveNext(); 
		}
		// process remaining elements in the List
		else {
			t += std::string(power - std::to_string(L.peekNext()).length(), '0');
			t += std::to_string(L.peekNext()); 
			L.moveNext(); 
		}
	}
	
	// remove all non-digit values and 0 from the string if any
	const std::regex patterns("^0+(?!$)");
	t = std::regex_replace(t, patterns, "");

	// combine strings s and t into string s	
	s += t; 
	
	return s; 
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
	return stream << N.BigInteger::to_string(); 
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
	if (A.BigInteger::compare(B) == 0) {
		return true; 
	}
	else {
		return false; 
	}
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
	if (A.BigInteger::compare(B) == -1) {
		return true; 
	}
	else {
		return false; 
	}
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
	if (A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0) {
		return true; 
	}
	else {
		return false; 
	}
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
if (A.BigInteger::compare(B) == 1) {
		return true; 
	}
	else {
		return false; 
	}
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
if (A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0) {
		return true; 
	}
	else {
		return false; 
	}
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
	return A.BigInteger::add(B); 
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
 	A = A + B; 
 	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
	return A.BigInteger::sub(B); 
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
	A = A - B; 
	return A; 
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
	return A.BigInteger::mult(B); 
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
	A = A * B; 
	return A; 
}
