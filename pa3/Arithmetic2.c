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
    FILE* in;
    FILE* out;

    int a_size;
    int b_size;
    
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s input-file output-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if( (in=fopen(argv[1], "r")) == NULL )
    {
        fprintf(stderr, "Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if( (out=fopen(argv[2], "w")) == NULL )
    {
        fprintf(stderr, "Unable to read from file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    // printf("passed all the if cases\n");

    fscanf(in, "%d", &a_size);
    char* a = calloc(a_size+2, sizeof(char));
    fscanf(in, "%s", a);

    // printf("instantiated the character a\n");

    fscanf(in, "%d", &b_size);
    char* b = calloc(b_size+2, sizeof(char));
    fscanf(in, "%s", b);

    // printf("instantiated the character b\n");

    // printf("%s\n", a);
    // printf("%s\n", b);
    
    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    BigInteger sumAB = newBigInteger();
    BigInteger diffAB = newBigInteger();
    BigInteger diffAA = newBigInteger();
    BigInteger diff3A2B = newBigInteger();
    BigInteger prodAB = newBigInteger();
    BigInteger A_2 = newBigInteger();
    BigInteger B_2 = newBigInteger();
    BigInteger A_4 = newBigInteger();
    BigInteger B_5 = newBigInteger();
    BigInteger bigSum = newBigInteger();

    A = stringToBigInteger(a);
    B = stringToBigInteger(b);

    //fprintf(stdout, "A: ");
    printBigInteger(out, A);
    fprintf(out, "\n");
    fprintf(out, "\n");

    //fprintf(stdout, "B: ");
    printBigInteger(out, B);
    fprintf(out, "\n");
    fprintf(out, "\n");

    sumAB = sum(A, B);
    //fprintf(stdout, "A + B: ");
    printBigInteger(out, sumAB);
    fprintf(out, "\n");
    fprintf(out, "\n");

    diffAB = diff(A, B);
    //fprintf(stdout, "A - B: ");
    printBigInteger(out, diffAB);
    fprintf(out, "\n");
    fprintf(out, "\n");

    diffAA = diff(A, A);
    //fprintf(stdout, "A - A: ");
    printBigInteger(out, diffAA);
    fprintf(out, "\n");
    fprintf(out, "\n");

    BigInteger A_tripled = newBigInteger();
    BigInteger B_doubled = newBigInteger();
    add(A_tripled, A, A);
    add(A_tripled, A_tripled, A);
    add(B_doubled, B, B);
    diff3A2B = diff(A_tripled, B_doubled);
    //fprintf(stdout, "3A - 2B: ");
    printBigInteger(out, diff3A2B);
    fprintf(out, "\n");
    fprintf(out, "\n");

    prodAB = prod(A, B);
    //fprintf(stdout, "A*B: ");
    printBigInteger(out, prodAB);
    fprintf(out, "\n");
    fprintf(out, "\n");

    A_2 = prod(A, A);
    //fprintf(stdout, "A*A: ");
    printBigInteger(out, A_2);
    fprintf(out, "\n");
    fprintf(out, "\n");

    B_2 = prod(B, B);
    //fprintf(stdout, "B*B: ");
    printBigInteger(out, B_2);
    fprintf(out, "\n");
    fprintf(out, "\n");

    A_4 = prod(A_2, A_2);
    B_5 = prod(B_2, B_2);
    multiply(B_5, B_5, B);

    BigInteger coeff_9 = newBigInteger();
    char* c_9 = "9";
    coeff_9 = stringToBigInteger(c_9);

    BigInteger coeff_16 = newBigInteger();
    char* c_16 = "16";
    coeff_16 = stringToBigInteger(c_16);

    multiply(A_4, coeff_9, A_4);
    multiply(B_5, coeff_16, B_5);

    bigSum = sum(A_4, B_5);
    //fprintf(stdout, "9A_4 + 16B_5: ");
    printBigInteger(out, bigSum);
    fprintf(out, "\n");
    fprintf(out, "\n");

    fclose(in);
    fclose(out);

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&sumAB);
    freeBigInteger(&diffAB);
    freeBigInteger(&diffAA);
    freeBigInteger(&diff3A2B);
    freeBigInteger(&prodAB);
    freeBigInteger(&A_2);
    freeBigInteger(&B_2);
    freeBigInteger(&A_4);
    freeBigInteger(&B_5);
    freeBigInteger(&A_tripled);
    freeBigInteger(&B_doubled);
    freeBigInteger(&coeff_9);
    freeBigInteger(&coeff_16);

    return(EXIT_SUCCESS);
}