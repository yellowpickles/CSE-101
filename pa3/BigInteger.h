#ifndef _BIGINTEGER_H_INCLUDE_
#define _BIGINTEGER_H_INCLUDE_

//BigInteger reference type
typedef struct BigIntegerObj* BigInteger;

//Constructors-Destructors---------------------------------------------------------------

//newBigInteger()
//Returns a reference to a new BigInteger object in the zero state
BigInteger newBigInteger();

//freeBigInteger()
//Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN);

//Access functions-----------------------------------------------------------------------

//sign()
//Returns -1 if N is negative, 1 if N is postive, 0 if N is in zero state
int sign(BigInteger N);

//compare()
//returns -1 if A<B, 1 if A>B, 0 if A=B
int compare(BigInteger A, BigInteger B);

//equals()
//Return true(1) if A & B are equal, false(0) otherwise
int equals(BigInteger A, BigInteger B);

//Manipulation procedures----------------------------------------------------------------

//makeZero()
//resets N to the zero state
void makeZero(BigInteger N);

//negate()
//reverses the sign of N: positive <-> negative
//does nothing if N is in zero state
void negate(BigInteger N);

//BigInteger Arithmetic operations-------------------------------------------------------

//stringToBigInteger()
//returns a reference to a new BigInteger object representing the
//decimal integer represented in base 10 by the string s.
//Pre: s is a non-empty string containing only base 10 digits
//(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) and an optional sign(+, -) prefix
BigInteger stringToBigInteger(char* s);

//copy()
//Returns a reference to a new BigInteger object in the same state as N
BigInteger copy(BigInteger N);

//add()
//Places the sum of A and B in existing BigInteger S, overwriting its
//current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B);

//sum()
//returns a reference to a new BigInteger object representing A+B
BigInteger sum(BigInteger A, BigInteger B);

//subtract()
//places the difference of A&B in the existing BigInteger D, overwriting
//its current state: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B);

//diff()
//returns a reference to a new BigInteger object representing A-B
BigInteger diff(BigInteger A, BigInteger B);

//multiply()
//places the product of A&B in the existing BigInteger P, overwriting
//its curent state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);

//prod()
//returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B);

//Other Operations----------------------------------------------------------------------

//printBigInteger()
//Prints a base 10 string representation of N to filestream out
void printBigInteger(FILE* out, BigInteger N);

#endif