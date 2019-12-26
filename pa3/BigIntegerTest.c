//--------------------------------------------------------------------------
//Andy He
//Nov 1, 2019
//Arithmetic.c
//Uses BigInteger.c and reads in input files to perform BigInteger
//--------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include"BigInteger.h"

int main(int argc, char* argv[])
{
	// BigInteger A = newBigInteger();
	// // char* s = "13075623459";
	// char* a = "123";
	// A = stringToBigInteger(a);
	// printBigInteger(stdout, A);
	// fprintf(stdout, "\n");
	// fprintf(stdout, "sign is %d\n", sign(A));
	// // fprintf(stdout, "-----------------------------------------------------");

	// BigInteger B = newBigInteger();
	// char* b = "-0041085449";
	// B = stringToBigInteger(b);
	// printBigInteger(stdout, B);
	// fprintf(stdout, "\n");
	// fprintf(stdout, "sign is %d\n", sign(B));

	// BigInteger C = newBigInteger();
	// char* c = "123465789";
	// C = stringToBigInteger(c);
	// printBigInteger(stdout, C);
	// fprintf(stdout, "\n");
	// fprintf(stdout, "sign is %d\n", sign(C));

	// BigInteger D = newBigInteger();
	// char* d = "1489145378415783418743157815378";
	// D = stringToBigInteger(d);
	// printBigInteger(stdout, D);
	// fprintf(stdout, "\n");
	// fprintf(stdout, "sign is %d\n", sign(D));

	// BigInteger E = newBigInteger();
	// char* e = "0";
	// E = stringToBigInteger(e);
	// printBigInteger(stdout, E);
	// fprintf(stdout, "\n");
	// fprintf(stdout, "sign is %d\n", sign(E));

	BigInteger A = newBigInteger();
	char* a = "213659";
	A = stringToBigInteger(a);
	fprintf(stdout, "A is: ");
	//fprintf(stdout, "%d ", sign(A_1));
	printBigInteger(stdout, A);
	fprintf(stdout, "\n");

	BigInteger B = newBigInteger();
	char* b = "125674";
	B = stringToBigInteger(b);
	fprintf(stdout, "B is: ");
	//fprintf(stdout, "%d ", sign(B_1));
	printBigInteger(stdout, B);
	fprintf(stdout, "\n");

	BigInteger sumAB = sum(A, B);
	fprintf(stdout, "A + B is: ");
	//fprintf(stdout, "%d ", sign(sumAB));
	printBigInteger(stdout, sumAB);
	fprintf(stdout, "\n");
	// add(sumAB, A_1, B_1);
	// printBigInteger(stdout, sumAB);
	// fprintf(stdout, "\n");

	// BigInteger sumAB2 = newBigInteger();
	// add(sumAB2, sumAB2, B);
	// fprintf(stdout, "A + B second is: ");
	// printBigInteger(stdout, sumAB2);
	// fprintf(stdout, "\n");

	BigInteger diffAB = diff(A, B);
	fprintf(stdout, "A - B is: ");
	//fprintf(stdout, "%d ", sign(diffAB));
	printBigInteger(stdout, diffAB);
	fprintf(stdout, "\n");
	// subtract(diffAB, A_1, B_1);
	// printBigInteger(stdout, diffAB);
	// fprintf(stdout, "\n");

	// BigInteger diffAB2 = newBigInteger();
	// subtract(diffAB2, A, B);
	// fprintf(stdout, "A - B second is: ");
	// printBigInteger(stdout, diffAB2);
	// fprintf(stdout, "\n");

	// BigInteger result = newBigInteger();
	// add(result, result, A);
	// fprintf(stdout, "A + result is: ");
	// printBigInteger(stdout, result);
	// fprintf(stdout, "\n");

	BigInteger prodAB = prod(A, B);
	fprintf(stdout, "A * B is: ");
	printBigInteger(stdout, prodAB);
	fprintf(stdout, "\n");
}