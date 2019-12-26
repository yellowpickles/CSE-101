//-------------------------------------------------------------------
//Andy He
//ahe206
//cse101
//Nov 1, 2019
//BigInteger.c
//implements a BigInteger ADT that performs big integer operations
//-------------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"BigInteger.h"
#include"List.h"

#define POWER 9;
#define BASE 1000000000;

//BigIntegerObj
typedef struct BigIntegerObj
{
	int sign;
	List magnitude;
}BigIntegerObj;

//newBigInteger()
//constructor
BigInteger newBigInteger()
{
	BigInteger BI = malloc(sizeof(BigIntegerObj));
	assert( BI != NULL );
	BI->sign = 0;
	BI->magnitude = newList();
	return BI;
}

//freeBigInteger()
//destructor
void freeBigInteger(BigInteger* pN)
{
	if( pN != NULL && *pN != NULL )
	{
		freeList( &((*pN)->magnitude));
		free(*pN);
		*pN = NULL;
	}
}

//Access functions--------------------------------------------------

//sign()
int sign(BigInteger N)
{
	if(N == NULL)
	{
		fprintf(stderr, "BigInteger error: calling sign() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);		
	}
	return N->sign;
}

//compare()
//returns -1 if A<B, 1 if A>B, 0 of A=B
int compare(BigInteger A, BigInteger B)
{
	if(A==NULL || B==NULL)
	{
		fprintf(stderr, "BigInteger error: calling compare() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if(sign(A) < sign(B))
	{
		return -1;
	}
	else if(sign(A) > sign(B))
	{
		return 1;
	}
	else if(length(A->magnitude) > length(B->magnitude))
	{
		return 1;
	}
	else if(length(A->magnitude) < length(B->magnitude))
	{
		return -1;
	}
	else if(length(A->magnitude) == length(B->magnitude))
	{
		moveFront(A->magnitude);
		moveFront(B->magnitude);
		//need to change following if to a while, to check the entire magnitude
		// if(front(A->magnitude) > front(B->magnitude))
		// {
		// 	return 1 * sign(A);
		// }
		// else
		// {
		// 	return 0;
		// }
		while(index(A->magnitude) > -1)
		{
			if(get(A->magnitude) > get(B->magnitude))
			{
				return 1 * sign(A);
			}
			else if(get(A->magnitude) < get(B->magnitude))
			{
				return -1 * sign(A);
			}
			moveNext(A->magnitude);
			moveNext(B->magnitude);
		}
	}
	return 0;
}

//equals
//return true(1) if A&B are equal, false(0) otherwise
int equals(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling equals() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	int result = 0;
	if(sign(A) == sign(B) && list_equals(A->magnitude, B->magnitude) == 1)
	{
		result = 1;
	}
	return result;
}

//MANIPULATION PROCEDURES----------------------------------------------------------------------------------------------------

//makeZero()
//resets N to the zero state
void makeZero(BigInteger N)
{
	if(N == NULL)
	{
		fprintf(stderr, "BigInteger error: calling makeZero() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	N->sign = 0;
	clear(N->magnitude);
}

//negate()
//reverses the sign of Nl positive <-> negative
//does nothing if N is in zero state
void negate(BigInteger N)
{
	if(N == NULL)
	{
		fprintf(stderr, "BigInteger error: calling negate() on NULL reference\n");
		exit(EXIT_FAILURE);
	}
	N->sign = (-1) * N->sign;
}

//BigInteger Arithmetic operations------------------------------------------------------------------------------------------

//stringToBigInteger()
//returns a reference to a new BigInteger object representing the
//decimal integer represented in base 10 by the string s.
//Pre: s is a non-empty string containing only base 10 digits
//(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) and an optional sign(+, -) prefix
BigInteger stringToBigInteger(char* s)
{
	if(s == NULL)
	{
		fprintf(stderr, "BigInteger error: calling stringToBigInteger() on NULL string reference\n");
		exit(EXIT_FAILURE);
	}
	if(strlen(s) == 0)
	{
		fprintf(stderr, "BigInteger error: calling stringToBigInteger() on empty string\n");
		exit(EXIT_FAILURE);
	}
	BigInteger result = newBigInteger();
	int p = POWER;
	//printf("p is %d\n", p);
	int start_index = 0;
	int s_size = strlen(s);
	if(s[0] ==  '-' || s[0] == '+')
	{
		start_index = 1;
	}
	//note: when we create a c string, say of size n, we need to make sure element n+1 is '\0'
	char input_finalized[s_size - start_index + 1];
	// int input_index = 0;
	// while(s[start_index] != '\0')
	// {
	// 	input_finalized[input_index] = s[start_index];
	// 	start_index++;
	// 	input_index++;
	// }
	for(int i = 0; i < s_size - start_index; i++)
	{
		input_finalized[i] = s[i + start_index];
	}

	//printf("the string passed in is %s", input_finalized);

	input_finalized[s_size - start_index] = '\0';
	int s_loop = strlen(input_finalized) - 1;
	char* temp = (char*)malloc(sizeof(char)*(p+1));
	for(int i = 0; i < p+1; i++)
	{
		temp[i] = '0';
	}
	// printf("0. temp should be zeros: %s\n", temp);
	// char temp[p+1];
	temp[p] = '\0';
	int temp_index_counter = p - 1;
	while(input_finalized[s_loop] != '\0')
	{
		// printf("1. s_loop is currently %d\n", s_loop);

		temp[temp_index_counter] = input_finalized[s_loop];
		// char* x = input_finalized[s_loop];
		// strcat(temp, x);
		// printf("input_finalized is %c\n", input_finalized[s_loop]);
		// printf("2. temp at temp_index_counter is currently %c\n", temp[temp_index_counter]);
		// printf("3. temp_index_counter is currently %d\n", temp_index_counter);

		temp_index_counter--;

		// printf("4. temp_index_counter after being subtracted is currently %d\n", temp_index_counter);
		// printf("5. temp is currently %s\n", temp);
		// printf("5a. temp char is currently %c\n", temp[temp_index_counter+1]);

		if(temp_index_counter < 0)
		{
			long to_insert = atol(temp);

			//printf("6. inside first if statement, inserting long %ld\n", to_insert);

			prepend(result->magnitude, to_insert);
			//strcpy(temp, "");
			//temp = calloc(p, sizeof(char));
			//temp[0] = '\0';
			temp_index_counter = p - 1;
			//strcpy(temp, "");
			//memset(temp, 0, strlen(temp));
			for(int i = 0; i < p; i++)
			{
				temp[i] = '0';
			}
		}
		//printf("6. s_loop is currently %d\n", s_loop);
		s_loop--;

		//printf("7. s_loop after being subtracted is currently %d\n", s_loop);

		if(s_loop < 0)
		{
			long to_insert = atol(temp);

			//printf("8. inside second if statement, inserting long %ld\n", to_insert);

			prepend(result->magnitude, to_insert);
		}
	}
	//now we need to establish what result's sign should be
	if(s[0] == '-')
	{
		result->sign = -1;
	}
	else if(s[0] == '+')
	{
		result->sign = 1;
	}
	else
	{
		//printf("about to move cursor to front to establish sign\n");
		// printf("number of digits in the BigInteger is %d\n", length(result->magnitude));
		if(length(result->magnitude) > 0) //might have to get rid of this if statement
		{
			//printf("in sTBI(), about to moveFront()\n");
			moveFront(result->magnitude);
			//printf("in sTBI(), moveFront() done\n");
			//printf("moved cursor\n");
			while(index(result->magnitude) != -1)
			{
				//printf("entered while loop\n");
				if(get(result->magnitude) > 0) //once we find a positive number in the magnitude
				{
					//printf("entered if statement\n");
					result->sign = 1;//assign it the proper sign
					break;//then break out of the loop
				}
				moveNext(result->magnitude);
			}
		}
	}
	//if front of result's magnitude is 0, then deleteFront()
	if(length(result->magnitude) > 1)
	{
		//printf("before entering to check for front()\n");
		while(front(result->magnitude) == 0)
		{
			//printf("entered while that calls front()\n");
			deleteFront(result->magnitude);
		}
	}
	//printf("number of digits in the BigInteger is %d\n", length(result->magnitude));
	//printf("successfully converted input to BigInteger\n");
	return result;
}

//copy()
//returns a reference to a new BigInteger object in the same state as N
BigInteger copy(BigInteger N)
{
	if(N == NULL)
	{
		fprintf(stderr, "BigInteger error: calling copy() on NULL BigInteger reference(\n");
		exit(EXIT_FAILURE);
	}
	BigInteger to_return = newBigInteger();
	to_return->sign = N->sign;
	to_return->magnitude = copyList(N->magnitude);
	return to_return;
}

//normalize()
//returns a new BigInteger that is the normalized version of N
BigInteger normalize(BigInteger N, int operation)
{
	//printf("7.					entered normalize\n");
	//if operation is 0, we are adding
	//1 is subtracting
	//2 is multiplying
	int operand = 1;
	if(operation == 1)
	{
		operand = -1;
	}
	BigInteger result = newBigInteger();
	result = N;
	//case for if they are all negative elements
	//first assume that they are all negative
	//break out of loop once found positive element, and set all_neg = 0
	int all_neg = 1;
	//printf("in normalize(), about to do 1st mF()\n");
	moveFront(N->magnitude);
	//printf("in normalize, 1st mF() done\n");
	while(index(N->magnitude) > -1)
	{
		if(get(N->magnitude) >= 0)
		{
			all_neg = 0;
			break;
		}
		moveNext(N->magnitude);
	}
	//printf("7a.						checked if elements are all neg\n");

	if(all_neg)
	{
		//result = N;
		//printf("in normalize(), about to do 2nd mF()\n");
		moveFront(result->magnitude);
		//printf("in normalize, 2nd mF() done\n");
		while(index(result->magnitude) > -1)
		{
			set(result->magnitude, -1 * get(result->magnitude));
			moveNext(result->magnitude);
		}
		result->sign = -1;
		return result;
	}
	//printf("7b.						if all neg, negated all elements\n");

	//case for if the first element is negative
	//if it is, we need to negate all elements 
	if(front(result->magnitude) < 0)
	{
		moveFront(result->magnitude);
		while(index(result->magnitude) > -1)
		{
			set(result->magnitude, -1 * get(result->magnitude));
			moveNext(result->magnitude);
		}
	}
	//printf("7c.						checked if first element is neg\n");

	int b = BASE;
	int carry = 0;
	moveBack(result->magnitude);
	while(index(result->magnitude) > -1)
	{
		long new_val = get(result->magnitude);
		new_val = new_val + carry;
		carry = 0;
		if(get(result->magnitude) < 0 || get(result->magnitude) > b)
		{
			// while(get(result->magnitude) < 0 || get(result->magnitude) > b)
			// {
			// 	carry = carry + (1 * operand);
			// 	//printf("carry is %d: \n", carry);
			// 	new_val = new_val - (b * operand);
			// 	set(result->magnitude, get(result->magnitude) - (b * operand));
			// }
			carry = operand * (get(result->magnitude) / b);
			new_val = new_val % b;
		}
		else
		{
			carry = 0;
		}
		set(result->magnitude, new_val);
		movePrev(result->magnitude);
	}
	//printf("7d.						finally done with the REAL normalizing\n");

	if(carry > 0)
	{
		prepend(result->magnitude, carry);
	}
	//printf("7.					done with normalize\n");
	return result;
}

//add()
//Places the sum of A and B in existing BigInteger S, overwriting its
//current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
	if(S == NULL || A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling add() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	//printf("4.			add() was called\n");
	BigInteger result = newBigInteger();
	result = sum(A, B);
	//printf("5.			sum() is done!!!!!!\n");
	S->sign = sign(result);
	S->magnitude = result->magnitude;
	freeBigInteger(&result);
}

//sum()
//returns a reference to a new BigInteger object representing A+B
BigInteger sum(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling sum() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	BigInteger result = newBigInteger();
	//case 1: if either A or B is 0
	if(sign(A) == 0 && sign(B) != 0)
	{
		//printf("4a.				entered case 1 of sum()\n");
		result = copy(B);
		// printf("				result is: ");
		// printBigInteger(stdout, result);
		// printf("\n");
		//printf("				length of the result is %d\n", length(result->magnitude));
		//return result;
	}
	else if(sign(A) != 0 && sign(B) == 0)
	{
		//printf("4b.				entered case 2 of sum()\n");
		result = copy(A);
		//printf("4c.				copied A ");
		//return result;
	}
	else if(sign(A) == 0 && sign(B) == 0)
	{
		//printf("4d.				entered case 3 of sum()\n");
		return result;
	}
	//if the signs are not the same, we need to call diff with the appropriate parameters
	else if(sign(A) != sign(B))
	{
		//printf("4e.				entered case 4 of sum()\n");
		if(compare(A, B) == -1) //if A < B
		{
			//printf("4e1.					case 4.1\n");
			//call diff(B, A);
			//negate(A);
			BigInteger A_copy = copy(A);
			//printf("4e2.					copied A\n");
			negate(A_copy);
			result = diff(B, A_copy);
			//printf("4e3.					diff'd B and A's copy\n");
			freeBigInteger(&A_copy);
		}
		else if(compare(A, B) == 1) // if A > B
		{
			//printf("4e11.					case 4.2\n");
			//printf("Entered condition where signs aren't same, A>B\n");
			//call diff(A, B);
			//negate(B);
			BigInteger B_copy = copy(B);
			//printf("4e12.					copied B\n");
			negate(B_copy);
			//printf("B_copy's sign is now %d\n", sign(B_copy));
			result = diff(A, B_copy);
			printf("4e13.					diff'd A and B's copy\n");
			freeBigInteger(&B_copy);
		}
		//printf("				finished case 4\n");
	}
	else if(equals(A, B) == 1)
	{
		//printf("4f.				entered case 5 of sum()\n");
		//if they are the same number
		BigInteger C = copy(B);
		//printf("4g.				copied B onto C\n");
		result->sign = A->sign;
		moveBack(A->magnitude);
		moveBack(C->magnitude);
		while(index(A->magnitude) > -1 && index(C->magnitude) > -1)
		{
			prepend(result->magnitude, get(A->magnitude) + get(B->magnitude));
			movePrev(A->magnitude);
			movePrev(C->magnitude);
		}
		while(index(A->magnitude) > -1)
		{
			prepend(result->magnitude, get(A->magnitude));
			movePrev(A->magnitude);
		}
		while(index(C->magnitude) > -1)
		{
			prepend(result->magnitude, get(C->magnitude));
			movePrev(C->magnitude);
		}
		//printf("				finished case 5\n");
		freeBigInteger(&C);
	}
	//signs are the same
	else
	{
		//printf("				4g.entered case 6\n");
		result->sign = A->sign;
		//printf("				4g2. length of A is%d\n", length(A->magnitude));
		//printf("result's sign is %d\n", sign(result));
		moveBack(A->magnitude);
		//printf("last element of A is: %ld\n", get(A->magnitude));
		//printf("				4g3.length of B is %d\n", length(B->magnitude));
		moveBack(B->magnitude);
		// printf("last element of B is: %ld\n", get(B->magnitude));
		// printf("number of elements in A is: %d\n", length(A->magnitude));
		// printf("number of elements in B is: %d\n", length(B->magnitude));
		// printf("elements of A is: ");
		// printList(stdout, A->magnitude);
		// printf("\n");
		// printf("elements of B is: ");
		// printList(stdout, B->magnitude);
		// printf("\n");
		while(index(A->magnitude) > -1 && index(B->magnitude) > -1)
		{
			prepend(result->magnitude, get(A->magnitude) + get(B->magnitude));
			movePrev(A->magnitude);
			// if(index(A->magnitude) > 0)
			// {
			// 	movePrev(A->magnitude);
			// }
			// if(index(B->magnitude) >= 0)
			// {
			// 	movePrev(B->magnitude);
			// }
			//printf("1st while, movePrev'd on A\n");
			movePrev(B->magnitude);
			//printf("1st while, movePrev'd on B\n");
		}
		while(index(A->magnitude) > -1)
		{
			prepend(result->magnitude, get(A->magnitude));
			movePrev(A->magnitude);
			// printf("2nd while, movePrev'd on A\n");
		}
		while(index(B->magnitude) > -1)
		{
			prepend(result->magnitude, get(B->magnitude));
			movePrev(B->magnitude);
			// printf("3rd while, movePrev'd on B\n");
		}
		//printf("				finished case 6\n");
	}
	// BigInteger normalized = newBigInteger();
	if(length(result->magnitude) > 0)
	{
		//printf("				about to normalize the result\n");
		BigInteger normalized = newBigInteger();
		normalized = normalize(result, 0);
		//printf("						length of normalized is %d\n", length(normalized->magnitude));
		result = copy(normalized);
		//printf("				normalized result!!!!!\n");
		//printf("						length of result is %d\n", length(result->magnitude));
	}
	// normalized = normalize(result, 0);
	// result = normalized;
	//printf("# of elements in the result is %d\n", length(result->magnitude));
	return result;
}

//subtract()
//places the difference of A and B in the existing BigInteger D,
//overwriting its current state: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
	if(D == NULL || A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling subtract() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	BigInteger result = diff(A, B);
	D->sign = sign(result);
	D->magnitude = result->magnitude;
	freeBigInteger(&result);
}

//diff()
//returns a reference to a new BigInteger object representing A-B
BigInteger diff(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling diff() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	BigInteger result = newBigInteger();
	//case 1: if either one or both BigIntegers are 0 or if they are the same
	if(equals(A, B) == 1)
	{
		//printf("Entered condition in diff(), where A=B\n");

		return result;
	}
	// else if(equals(A, B) && sign(A) < 0)
	// {
	// 	BigInteger dbl = newBigInteger();
	// 	dbl = stringToBigInteger("2");
	// 	result = copy(prod(dbl, A));
	// }
	else if(sign(B) == 0 && sign(A) != 0)
	{
		result = copy(A);
		//return result;
	}
	else if(sign(A) == 0 && sign(B) != 0)
	{
		result = copy(B);
		negate(result);
		//return result;
	}
	//if they have different signs
	else if(sign(A) != sign(B))
	{
		//printf("in diff(), entered case where signs are different\n");
		//keep track of original sign
		int original_sign = sign(A);
		BigInteger A_copy = newBigInteger();
		A_copy = copy(A);
		BigInteger B_copy = newBigInteger();
		B_copy = copy(B);
		//printf("the original sign is %d\n", original_sign);
		//negate if their signs are negative so add() can work properly
		if(sign(A) == -1)
		{
			negate(A_copy);
		}
		else if(sign(B) == -1)
		{
			negate(B_copy);
		}
		result = sum(A_copy, B_copy);
		result->sign = original_sign;
		//we change sign after calling add() bc add() changes the sign
		//return result;
		freeBigInteger(&A_copy);
		freeBigInteger(&B_copy);
	}
	//case for if the signs are the same
	else
	{
		//printf("in diff(), entered case where signs are the same\n");
		if(compare(A, B) == 1) //if A>B
		{
			//printf("in diff, A > B\n");
			result->sign = 1;
		}
		else
		{
			//printf("in diff, A < B\n");
			result->sign = -1;
		}
		//printf("in diff(), the resulting sign is %d\n", result->sign);
		moveBack(A->magnitude);
		moveBack(B->magnitude);
		while(index(A->magnitude) > -1 && index(B->magnitude) > -1)
		{
			prepend(result->magnitude, get(A->magnitude) - get(B->magnitude));
			movePrev(A->magnitude);
			movePrev(B->magnitude);
		}
		while(index(A->magnitude) > -1)
		{
			prepend(result->magnitude, get(A->magnitude));
			movePrev(A->magnitude);
		}
		while(index(B->magnitude) > -1)
		{
			prepend(result->magnitude, (-1) * get(B->magnitude));
			movePrev(B->magnitude);
		}
	}
	//printf("about to normalize the result in diff()\n");
	// BigInteger normalized = newBigInteger();
	// normalized = normalize(result, 1);
	// result = normalized;
	if(length(result->magnitude) > 0)
	{
		BigInteger normalized = newBigInteger();
		normalized = normalize(result, 1);
		result = copy(normalized);
	}
	return result;
}

//multiply()
//places the product of A & B in the existing BigInteger P, 
//overwrites its current state: P = A * B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling multiply() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	//printf("1. multiply() is called\n");
	// BigInteger result = prod(A, B);
	//printf("3. prod is done!!!!\n");
	// P->sign = sign(result);
	// P->magnitude = result->magnitude;
	// freeBigInteger(&result);
}

//prod()
//returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "BigInteger error: calling prod() on NULL BigInteger reference(s)\n");
		exit(EXIT_FAILURE);
	}
	BigInteger result = newBigInteger();
	//printf("2. prod() is called\n");
	// BigInteger temp = newBigInteger();
	// temp->sign = 1;
	// BigInteger result = newBigInteger();

	// BigInteger A_copy = copy(A);
	// BigInteger B_copy = copy(B);
	//printf("2a. copied B onto B_copy\n");
	// moveBack(A->magnitude);
	//printf("moved back on A\n");
	// moveBack(B_copy->magnitude);
	// //printf("moved back on B's copy\n");
	// //printf("2b. moved back on both A and B_copy\n");
	// int num_zeros = 0;
	// while(index(B_copy->magnitude) > -1)
	// {
	// 	//printf("	2c. entered first layer1 while loop, iterating on B\n");
	// 	//printf("	about to move back on A\n");
	// 	moveBack(A->magnitude);
	// 	//printf("	moved back on A\n");
	// 	while(index(A->magnitude) > -1)
	// 	{
	// 		//printf("		2d. entered first layer2 while loop, iterating on A: %ld x %ld\n", get(A->magnitude), get(B_copy->magnitude));
	// 		prepend(temp->magnitude, get(A->magnitude) * get(B_copy->magnitude));
	// 		//printf("		2e. multiplied A and B_copy's elements\n");
	// 		movePrev(A->magnitude);
	// 		//printf("		2f. moved A's cursor\n");
	// 	}
	// 	//printf("			temp is currently: ");
	// 	printBigInteger(stdout, temp);
	// 	//printf("\n");
	// 	//printf("	2g. exited first layer2 while loop\n");
	// 	int n_z = num_zeros;
	// 	//printf("	2h. the number of zeros to append is %d\n", n_z);
	// 	while(n_z > 0)
	// 	{
	// 		//printf("		2i. entered second layer2 while loop, adding 0s\n");
	// 		append(temp->magnitude, 0);
	// 		//printf("		2j. appended the 0\n");
	// 		n_z--;
	// 	}
	// 	num_zeros++;

	// 	// printf("temp is: ");
	// 	// printList(stdout, temp->magnitude);
	// 	// printf("\n");
	// 	//need to figure out how to prepend the right amount of zeros

	// 	add(result, result, temp);
	// 	//printf("	2k. added temp to result\n");
	// 	//printf("	result is currently: ");
	// 	//printBigInteger(stdout, result);
	// 	//printf("\n");
		
	// 	//printf("after calling add on result and temp\n");
	// 	// printf("result is currently length: %d\n", length(result->magnitude));

	// 	// printf("result is currently: ");
	// 	// printList(stdout, result->magnitude);
	// 	// printf("\n");
		
	// 	clear(temp->magnitude);
	// 	//printf("	2l. cleared temp's magnitude\n");
	// 	//printf("after calling clear on temp's magnitude\n");
		
	// 	movePrev(B_copy->magnitude);
	// 	//printf("after calling movePrev() on B's magnitude\n");
	// }
	// if(sign(A) == sign(B_copy))
	// {
	// 	result->sign = 1;
	// }
	// else if(sign(A) == 0 || sign(B_copy) == 0)
	// {
	// 	result->sign = 0;
	// }
	// else
	// {
	// 	result->sign = -1;
	// }
	// //printf("successfully produced a product of A and B\n");
	// BigInteger normalized = newBigInteger();
	// normalized = normalize(result, 2);
	// result = normalized;
	// freeBigInteger(&B_copy);
	return result;
}

//printBigInteger()
//prints a base 10 representation of N to filestream out
void printBigInteger(FILE* out, BigInteger N)
{
	//if the sign isnt 0, call printlist
	//otherwise print 0
	if(sign(N) != 0)
	{
		if(sign(N) == -1)
		{
			fprintf(out, "-");
		}
		//printf("					in pBI, about to mF()\n");
		moveFront(N->magnitude);
		//printf("					in pBI, mF'd\n");
		fprintf(out, "%ld", get(N->magnitude));
		moveNext(N->magnitude);
		//printList(out, N->magnitude);
		while(index(N->magnitude) > -1)
		{
			fprintf(out, "%0*ld", 9, get(N->magnitude));
			moveNext(N->magnitude);
		}
	}
	else
	{
		fprintf(out, "0");
	}
}