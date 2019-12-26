//------------------------------------------------------------------------------------------
//Andy He
//ahe206
//October 20th, 2019
//Sparse.c
//Uses the Matrix ADT and reads in an input file to perform Matrix operations on
//------------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include"Matrix.h"

int main(int argc, char* argv[])
{
	FILE* in;
	FILE* out;

	int n;
	int A_NNZ;
	int B_NNZ;

	if( argc != 3 )
	{
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if( (in=fopen(argv[1], "r")) == NULL )
	{
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if( (out=fopen(argv[2], "w")) == NULL )
	{
		printf("Unable to read from file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	fscanf(in, "%d %d %d", &n, &A_NNZ, &B_NNZ);

	// printf("size of both matrices are n = %d\n", n);
	// printf("NNZ of a is %d\n", A_NNZ);
	// printf("NNZ of b is %d\n", B_NNZ);
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);

	//got the solution of skipping a line from:
	//https://stackoverflow.com/questions/2799612/how-to-skip-the-first-line-when-fscanning-a-txt-file
	//fscanf(in, "%*[^\n]\n", NULL);

	for(int i = 1; i <= A_NNZ; i++)
	{
		int row;
		int column;
		double value;
		fscanf(in, "%d %d %lf", &row, &column, &value);
		//printf("%d %d %0.1f\n", row, column, value);
		changeEntry(A, row, column, value);
	}

	//fscanf(in, )
	for(int i = 1; i <= B_NNZ; i++)
	{
		int row;
		int column;
		double value;
		fscanf(in, "%d %d %lf", &row, &column, &value);
		changeEntry(B, row, column, value);
	}

	fprintf(out, "A has %d non-zero entries:\n", A_NNZ);
	printMatrix(out, A);

	fprintf(out, "B has %d non-zero entries:\n", B_NNZ);
	printMatrix(out, B);

	fprintf(out, "(1.5)*A =\n");
	Matrix scaled_A = scalarMult(1.5, A);
	printMatrix(out, scaled_A);

	fprintf(out, "A+B =\n");
	Matrix A_add_B = sum(A, B);
	printMatrix(out, A_add_B);

	fprintf(out, "A+A =\n");
	Matrix A_add_A = sum(A, A);
	printMatrix(out, A_add_A);

	fprintf(out, "B-A = \n");
	Matrix B_sub_A = diff(B, A);
	printMatrix(out, B_sub_A);

	fprintf(out, "A-A =\n");
	Matrix A_sub_A = diff(A, A);
	printMatrix(out, A_sub_A);

	fprintf(out, "Transpose(A) =\n");
	Matrix A_T = transpose(A);
	printMatrix(out, A_T);

	fprintf(out, "A*B =\n");
	Matrix AB = product(A, B);
	printMatrix(out, AB);

	fprintf(out, "B*B =\n");
	Matrix BB = product(B,B);
	printMatrix(out, BB);

	fclose(in);
	fclose(out);

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&scaled_A);
	freeMatrix(&A_add_B);
	freeMatrix(&A_add_A);
	freeMatrix(&B_sub_A);
	freeMatrix(&A_sub_A);
	freeMatrix(&A_T);
	freeMatrix(&AB);
	freeMatrix(&BB);

	return(EXIT_SUCCESS);
}