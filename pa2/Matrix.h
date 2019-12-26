//-----------------------------------------------------------
//Andy He
//ahe206
//101
//Oct 13, 2019
//Matrix.h
//header file for Matrix.c
//-----------------------------------------------------------

#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_

typedef struct MatrixObj* Matrix;

Matrix newMatrix(int n);

void freeMatrix(Matrix* pM);

//ACCESS FUNCTIONS

//size()
//returns the size of square Matrix M
int size(Matrix M);

//NNZ()
//returns the number of non-zero elements in M
int NNZ(Matrix M);

//equals()
//return true(1) if matrices A and B are equal, false(0) otherwise
int equals(Matrix A, Matrix B);

//MANIPULATION PROCEDURES

//makeZero()
//resets M to the zero matrix
void makeZero(Matrix M);

//changeEntry()
//Changes the i'th row, j'th column of M to the value x
//Pre: 1 <= i <= size(M), 1 <= j <= size(M)
void changeEntry(Matrix M, int i, int j, double x);

//MATRIX ARITHMETIC OPERATIONS

//copy()
//returns a reference to a new Matrix object having the same entries as A
Matrix copy(Matrix A);

//transpose()
//returns a reference to a new Matrix object represeting the 
//transpose of A
Matrix transpose(Matrix A);

//scalarMult()
//returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A);

//sum()
//returns a reference to a new Matrix object representing A + B
//pre: size(A) == size(B)
Matrix sum(Matrix A, Matrix B);

//diff()
//returns a reference to a new matrix object representing A - B
//pre: size(A) == size(B)
Matrix diff(Matrix A, Matrix B);

//product()
//returns a reference to a new Matrix object representing AB
//pre: size(A) == size(B)
Matrix product(Matrix A, Matrix B);

//printMatrix()
//Prints a string representation of Matrix M to filestream out.
//Zero rows are not printed. Each non-zero is represented as one
//line consisting of the row number, followed by a colon, a space,
//then a space separated list of pairs "(col, val)" giving the 
//column numbers and non-zero values in that row. The double val
//will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);

#endif