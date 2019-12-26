#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main()
{
	Matrix A = newMatrix(4);
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 3);
	changeEntry(A, 2, 1, 4);
	changeEntry(A, 2, 2, 5);
	changeEntry(A, 2, 3, 6);
	changeEntry(A, 3, 1, 7);
	changeEntry(A, 3, 2, 8);
	changeEntry(A, 3, 3, 9);

	// changeEntry(A, 3, 3, 0);
	// changeEntry(A, 1, 1, 0);
	// changeEntry(A, 2, 2, 0);

	Matrix C = newMatrix(4);
	changeEntry(C, 3, 3, 9);
	changeEntry(C, 1, 3, 3);
	changeEntry(C, 2, 3, 6);
	changeEntry(C, 2, 2, 5);
	changeEntry(C, 3, 2, 8);
	changeEntry(C, 1, 2, 2);
	changeEntry(C, 1, 1, 1);
	changeEntry(C, 3, 1, 7);
	changeEntry(C, 2, 1, 4);

	Matrix B = transpose(A);
	Matrix A_copy = copy(A);
	// Matrix A_copy = newMatrix(4);
	//changeEntry(A_copy, 3, 2, 7);
	Matrix AB = product(A, B);

	// Matrix A_B = sum(A, B);

	// Matrix difference = diff(A, B);

	Matrix A_T = transpose(A);

	fprintf(stdout, "A:\n");
	printMatrix(stdout, A);
	fprintf(stdout, "B:\n");
	printMatrix(stdout, B);
	fprintf(stdout, "C:\n");
	printMatrix(stdout, C);
	fprintf(stdout, "A_T:\n");
	printMatrix(stdout, A_T);
	fprintf(stdout, "A * B:\n");
	printMatrix(stdout, AB);	

	fprintf(stdout, "A's copy:\n");
	printMatrix(stdout, A_copy);

	printf("Matrix A equals Matrix A_copy? %s\n", equals(A, A_copy)?"true":"false" );

	printf("Matrix A equals Matric c? %s\n", equals(A, C)?"true": "false");

	makeZero(A);
	printf("New A:\n");
	printMatrix(stdout, A);
	// fprintf(stdout, "A + B:\n");
	// printMatrix(stdout, A_B);
	// fprintf(stdout, "has %d non-zero entries\n", NNZ(A_B));
	// fprintf(stdout, "A - B:\n");
	// printMatrix(stdout, difference);

	// Matrix A_scaled = scalarMult(2, A);
	// fprintf(stdout, "A scaled by 2:\n");
	// printMatrix(stdout, A_scaled);
	return EXIT_SUCCESS;
}