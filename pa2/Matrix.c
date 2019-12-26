//-------------------------------------------------------------------------
//Andy He
//ahe206
//101
//Oct 13, 2019
//Matrix.c
//uses Matrix.h and implements a Matrix ADT that performs Matrix Operations
//-------------------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"Matrix.h"
#include"List.h"

//EntryObj
typedef struct EntryObj
{
	int column;
	double value;
}EntryObj;

//Entry
typedef EntryObj* Entry;

//newEntry()
//constructor of the Entry type
Entry newEntry(int c, double v)
{
	Entry new_entry = malloc(sizeof(EntryObj));
	assert (new_entry != NULL);
	new_entry->column = c;
	new_entry->value = v;
	return(new_entry);
}

//freeEntry()
//destructor for the Entry type
void freeEntry(Entry* previousEntry)
{
	if(previousEntry != NULL && *previousEntry != NULL)
	{
		free(*previousEntry);
		*previousEntry = NULL;
	}
}

//MatrixObj
typedef struct MatrixObj
{
	int size;
	List* rows;
	int NNZ;
}MatrixObj;

//newMatrix()
//constructor for the List type
Matrix newMatrix(int n)
{
	Matrix M = malloc(sizeof(MatrixObj));
	assert( M != NULL );
	M->size = n;
	M->NNZ = 0;
	M->rows = calloc(n+1, sizeof(List));
	for(int i = 1; i <= n; i++)
	{
		M->rows[i] = newList();
	}
	return M;
}

void freeMatrix(Matrix* pM)
{
	if( pM != NULL && *pM != NULL)
	{
		makeZero(*pM);
		for(int i = 1; i <= size(*pM); i++)
		{
			freeList( &((*pM)->rows[i]) );
		}
		free((*pM)->rows);
		(*pM)->rows = NULL;
		free(*pM);
		*pM = NULL;
	}
}


//returns size of the square Matrix M
int size(Matrix M)
{
	if( M == NULL )
	{
		fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

//NNZ()
//returns the number of non-zero elements in M
int NNZ(Matrix M)
{
	if( M == NULL )
	{
		fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->NNZ;
}


//equals()
//returns true (1) if matrices A & B are the same, false(0) otherwise
int equals(Matrix A, Matrix B)
{
	if( A == NULL || B == NULL )
	{
		fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix/Matrices reference(s)\n");
		exit(EXIT_FAILURE);
	}
	int equal_to = 0;

	equal_to = ( ( size(A) == size(B) ) && ( A->NNZ == B->NNZ ) );

	if(equal_to == 0)
	{
		return equal_to;
	}

	List A_list = NULL;
	List B_list = NULL;

	//printf("sizes of A and B are the same and their NNZ are the same so equal_to is %d\n", equal_to);
	for(int i = 1; i <= A->size; i++)//enter row comparison
	{
		A_list = A->rows[i];
		B_list = B->rows[i];
		equal_to = ( ( length(A_list) == length(B_list) ) );
		if(equal_to == 0)
		{
			return equal_to;
		}
		//if the lengths are not zero in either list and if they arent zero, make sure they have the same length
		//printf("size of rows at row %d are the same and are non zero in both Matrices and equal_to is %d\n", i, equal_to);
		if(length(A_list) > 0)
		{
			moveFront(A_list);
			//printf("moved to front of A_list\n");
		}
		if(length(B_list) > 0)
		{
			moveFront(B_list);
			//printf("moved to front of B_list\n");
		} 
		while( length(A_list) != 0 && ( index(A_list)>-1 && index(B_list)>-1 ))
		{
			Entry A_entry = (Entry)get(A_list);
			Entry B_entry = (Entry)get(B_list);

			equal_to = (A_entry->column == B_entry->column);
			if(equal_to == 0)
			{
				return equal_to;
			}

			equal_to = (A_entry->value == B_entry->value);
			if(equal_to == 0)
			{
				return equal_to;
			}
			//printf("equal_to is currently %d\n", equal_to);
			if(index(A_list) > -1)
			{
				moveNext(A_list);
				//printf("moved to next cursor in A_list\n");
			}
			if(index(B_list) > -1)
			{
				moveNext(B_list);
				//printf("moved to next cursor in B_list\n");
			}
			//printf("nearing the end of while loop, equal_to is currently %d\n", equal_to);
		}
		//printf("outside of while loop, equal_to is currently %d\n", equal_to);
	}
	//printf("outside of for loop,, equal_to is currently %d\n", equal_to);
	
	return equal_to;
}



void makeZero(Matrix M)
{
	if( M == NULL )
	{
		fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	//go through list
	//call changeEntry(M, i, j, 0.0) on every entry
	//free list
	//then instantiate newList()
	for(int i = 1; i <= size(M); i++)
	{
		if(length(M->rows[i]) > 0)
		{
			while(index(M->rows[i]) > -1)
			{
				Entry to_remove = (Entry)get(M->rows[i]);
				changeEntry(M, i, to_remove->column, 0);
			}
		}
		clear(M->rows[i]);
	}
	M->NNZ = 0;
}


//might need to rewrite condition if entry exists
void changeEntry(Matrix M, int i, int j, double x)
{
	if( M == NULL )
	{
		fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if( i < 1 || i > size(M) || j < 1 || j > size(M))
	{
		fprintf(stderr, "Matrix Error: calling changeEntry() on invalid i/j indices\n");
		exit(EXIT_FAILURE);
	}
	//the following will cover the cases:
	//M[i][j] is an entry & x = 0
	//M[i][j] is an entry & x =/= 0
	int found = 0;
	if(length(M->rows[i]) > 0)
	{
		moveFront(M->rows[i]);
	}
	while(index(M->rows[i]) > -1) //while the cursor exists
	{
		//printf("Entered first while loop of changeEntry()\n");
		Entry entry = (Entry) get(M->rows[i]);
		//printf("Found an entry at row: %d column: %d\n", i, entry->column);
		found = (entry->column == j);
		if(found == 1) //if the entry already exists in the jth column
		{
			if(x == 0.0)
			{
				//fprintf(stdout, "Entering condition to delete\n");
				//delete and free entry
				delete(M->rows[i]);
				freeEntry(&entry);
				M->NNZ--;
				// return;
			}
			else
			{
				//overwrite the current entry's value
				entry->value = x;
				// return;
			}
			return;
		}
		//fprintf(stdout, "about to move cursor to index %d look for entry: (%d, %d, %f) \n", index(M->rows[i]), i, j, x);
		moveNext(M->rows[i]);
		//freeEntry(&entry); ////////////MAYBE REMOVE THIS
	}

	//the following will cover the case that:
	//M[i][j] is not an existing entry & x=/= 0
	if(found == 0 && x != 0.0)
	{

		Entry to_insert = newEntry(j, x);
		if(index(M->rows[i]) == -1 && length(M->rows[i]) == 0) //if no cursor exists & list is empty
		{
			append(M->rows[i], to_insert);
		}
		else //if cursor exists % list !empty
		{
			//find appropriate column
			moveFront(M->rows[i]);
			//Entry to_compare = (Entry)get(M->rows[i]);
			while(index(M->rows[i]) > -1 && to_insert->column >= ((Entry)get(M->rows[i]))->column)
			{
				//fprintf(stdout, "about to move cursor to index %d to find appropriate list index\n", index(M->rows[i]));
				moveNext(M->rows[i]);
			}
			if(index(M->rows[i]) > -1)
			{
				insertBefore(M->rows[i], to_insert);	
			}
			else
			{
				append(M->rows[i], to_insert);
			}
			//freeEntry(&to_compare);
		}
		M->NNZ++;
		//freeEntry(&to_insert);
	}
}


//copy()
//returns a reference to a new Matrix object having the same entries
Matrix copy(Matrix A)
{
	if( A == NULL )
	{
		fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix to_return = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++)
	{
		if(length(A->rows[i]) > 0)
		{
			moveFront(A->rows[i]);
		}
		while(index(A->rows[i]) > -1)
		{
			Entry to_copy = (Entry)get(A->rows[i]);
			changeEntry(to_return, i, to_copy->column, to_copy->value);
			moveNext(A->rows[i]);
		}

	}
	return to_return;
}


//transpose()
//returns a reference to a new Matrix object representing the
//transpose of A
Matrix transpose(Matrix A)
{
	if( A == NULL )
	{
		fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix A_transpose = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++)
	{
		if(length(A->rows[i]) > 0)
		{
			moveFront(A->rows[i]);
		}
		while(index(A->rows[i]) > -1)
		{
			Entry to_copy = (Entry)get(A->rows[i]);
			changeEntry(A_transpose, to_copy->column, i, to_copy->value);
			moveNext(A->rows[i]);
		}

	}
	return A_transpose;
}

//scalarMult()
//returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A)
{
	if( A == NULL )
	{
		fprintf(stderr, "Matrix Error: calling scalarMult on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix A_scaled = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++)
	{
		if(length(A->rows[i]) > 0)
		{
			moveFront(A->rows[i]);
		}
		while(index(A->rows[i]) > -1)
		{
			Entry to_copy = (Entry)get(A->rows[i]);
			changeEntry(A_scaled, i, to_copy->column, x * to_copy->value);
			moveNext(A->rows[i]);
		}

	}
	return A_scaled;
}

//helper function for the methods add() and diff()
void addSub(List A, List B, Matrix m, int row, int toAdd)
{
	//List result = m->rows[row];
	//result was used to debug code
	//Tuan, the TA, helped me debug my addSub code
	//Tuan suggested that I make the helper function void, and add parameters Lists A and B and Matrix where I can change them directly
	int operand = -1;
	if(toAdd == 1)
	{
		operand = 1;
		// fprintf(stdout, "operand is %d\n", operand);
	}
	// fprintf(stdout, "About to enter moveFront() in addSub()\n");
	// moveFront(A);
	// moveFront(B);
	if(length(A) > 0)
	{
		moveFront(A);
	}
	if(length(B) > 0)
	{
		moveFront(B);
	}
	while( index(A) > -1 || index(B) > -1 )
	{
		if( index(A) > -1 && index(B) > -1 )
		{
			Entry A_entry = (Entry)get(A);
			Entry B_entry = (Entry)get(B);
			if( A_entry->column == B_entry->column )
			{
				double new_value = A_entry->value + (operand * B_entry->value);
				if(new_value != 0)
				{
					Entry to_insert = newEntry(A_entry->column, new_value);
					append(m->rows[row], to_insert);
					m->NNZ++;
					//freeEntry(&to_insert);
				}
				// append(m->rows[row], newEntry( A_entry->column, A_entry->value + (operand * B_entry->value) ) );
				// moveBack(result);
				// Entry newEntry = (Entry)get(result);
				// fprintf(stdout, "summed list at column %d is %f\n", newEntry->column, newEntry->value);
				//fprintf(stdout, "summed list at column %d is %f\n", A_entry->column, A_entry->value + (operand * B_entry->value));
				if(index(A) > -1)
				{
					moveNext(A);
				}
				if(index(B) > -1)
				{
					moveNext(B);
				}
			}
			else if( A_entry->column < B_entry->column )
			{
				// append(m->rows[row], newEntry( A_entry->column, A_entry->value ));
				double new_value = A_entry->value;
				if(new_value != 0)
				{
					Entry to_insert = newEntry(A_entry->column, new_value);
					append(m->rows[row], to_insert);
					//freeEntry(&to_insert);
				}
				m->NNZ++;
				// moveBack(result);
				// Entry newEntry = (Entry)get(result);
				// fprintf(stdout, "summed list at column %d is %f\n", newEntry->column, newEntry->value);
				//fprintf(stdout, "summed list at column %d is %f\n", A_entry->column, A_entry->value);
				if(index(A) > -1)
				{
					moveNext(A);
				}
			}
			else if( A_entry->column > B_entry->column)
			{
				double new_value = operand * B_entry->value;
				if(new_value != 0)
				{
					Entry to_insert = newEntry(B_entry->column, operand * B_entry->value);
					append(m->rows[row], to_insert);
					//freeEntry(&to_insert);
				}
				// append(m->rows[row], newEntry( B_entry->column, operand * B_entry->value ));
				m->NNZ++;
				// moveBack(result);
				// Entry newEntry = (Entry)get(result);
				// fprintf(stdout, "summed list at column %d is %f\n", newEntry->column, newEntry->value);
				//fprintf(stdout, "summed list at column %d is %f\n", B_entry->column, B_entry->value * operand);
				if(index(B) > -1)
				{
					moveNext(B);
				}
			}
		}
		else if( index(A) > -1 )
		{
			Entry A_entry = (Entry)get(A);
			double new_value = A_entry->value;
			if(new_value != 0)
			{
				Entry to_insert = newEntry(A_entry->column, A_entry->value );
				append(m->rows[row], to_insert);
				//]freeEntry(&to_insert);
			}
			// append(m->rows[row], newEntry( A_entry->column, A_entry->value ));
			m->NNZ++;
			// moveBack(result);
			// Entry newEntry = (Entry)get(result);
			// fprintf(stdout, "summed list at column %d is %f\n", newEntry->column, newEntry->value);
			//fprintf(stdout, "summed list at column %d is %f\n", A_entry->column, A_entry->value);
			if(index(A) > -1)
			{
				moveNext(A);
			}
		}
		else if( index(B) > -1 )
		{
			Entry B_entry = (Entry)get(B);
			double new_value = B_entry->value;
			if(new_value != 0)
			{
				Entry to_insert = newEntry( B_entry-> column, operand * B_entry->value);
				append(m->rows[row], to_insert);
				//freeEntry(&to_insert);
			}
			// append(m->rows[row], newEntry( B_entry-> column, operand * B_entry->value));
			m->NNZ++;
			//moveBack(result);
			//Entry newEntry = (Entry)get(result);
			//fprintf(stdout, "summed list at column %d is %f\n", newEntry->column, newEntry->value);
			if(index(B) > -1)
			{
				moveNext(B);
			}
		}
	}
}

//sum()
//returns a reference to a new Matrix object representing A+B
//pre: size(A) == size(B)
Matrix sum(Matrix A, Matrix B)
{
	if( A == NULL || B == NULL )
	{
		fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix/Matrices reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if( size(A) != size(B) )
	{
		fprintf(stderr, "Matrix Error: calling sum() on Matrices with different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix summed = newMatrix(size(A));
	if(equals(A, B) == 1)
	{
		summed = scalarMult(2, A);
		return summed;
	}
	for(int i = 1; i <= size(A); i++)
	{
		addSub(A->rows[i], B->rows[i], summed, i, 1);
		// printf("After summing row\n");
		// printMatrix(stdout, summed);
		// if(length(summed->rows[i]) > 0 )
		// {
		// 	moveFront(summed->rows[i]);
		// }
		// for(int i = 1; i <= length(summed->rows[i]); i++)
		// {
		// 	Entry toPrint = (Entry)get(summed->rows[i]);
		// 	fprintf(stdout, "(%d, %0.1f) ", toPrint->column, toPrint->value );	
		// }
		// fprintf(stdout, "summed row at row %d has length %d\n", i, length(summed->rows[i]));
	}
	return summed;
}

Matrix diff(Matrix A, Matrix B)
{
	if( A == NULL || B == NULL )
	{
		fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix/Matrices reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if( size(A) != size(B) )
	{
		fprintf(stderr, "Matrix Error: calling diff() on Matrices with different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix difference = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++)
	{
		addSub(A->rows[i], B->rows[i], difference, i, 0);
	}
	return difference;
}

//helper function that returns dot product of two lists
//idea of using static to create private functions from:
//https://stackoverflow.com/questions/1401781/how-to-implement-a-private-restricted-function-in-c/1401792
static double vectorDot(List P, List Q)
{
	// if( length(P) == 0 || length(Q) == 0 )
	// {
	// 	return;
	// }
	double dot_product = 0.0;
	moveFront(P);
	moveFront(Q);
	// int moveP = 0;
	// int moveQ = 0;
	while( index(P) > -1 && index(Q) > -1 )
	{
		Entry P_entry;
		Entry Q_entry;
		//printf("Entered while loop of vectorDot()\n");
		if(index(P) > -1)
		{
			P_entry = (Entry)get(P);
			//printf("Retrieved list P's entry: column: %d value: %0.1f\n", P_entry->column, P_entry->value);
		}
		if(index(Q) > -1)
		{
			Q_entry = (Entry)get(Q);
			//printf("Retrieved list Q's entry: column: %d value: %0.1f\n", Q_entry->column, Q_entry->value);
		}
		// Entry P_entry = (Entry)get(P);
		// printf("Retrieved list P's entry: column: %d value: %0.1f\n", P_entry->column, P_entry->value);
		// Entry Q_entry = (Entry)get(Q);
		// printf("Retrieved list Q's entry: column: %d value: %0.1f\n", Q_entry->column, Q_entry->value);
		if( P_entry->column < Q_entry->column && index(P) > -1)
		{
			moveNext(P);
		}
		else if( P_entry->column > Q_entry->column && index(Q) > -1)
		{
			moveNext(Q);
		}
		else //if( P_entry->column == Q_entry->column && ( index(Q) > -1 && index(P) > -1 ) )
		{
			dot_product = dot_product + (P_entry->value * Q_entry->value);
			if(index(P) > -1)
			{
				moveNext(P);
			}
			//moveNext(P);
			//moveNext(Q);
			if(index(Q) > -1)
			{
				moveNext(Q);
			}
		}
	}
	return dot_product;
}


//product()
//returns a reference to a new Matrix object representing AB
//pre: size(A) == size(B)
Matrix product(Matrix A, Matrix B)
{
	if( A == NULL || B == NULL )
	{
		fprintf(stderr, "Matrix Error: calling product() on NULL Matrix/Matrices reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if( size(A) != size(B) )
	{
		fprintf(stderr, "Matrix Error: calling product() on different sized Matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix AB = newMatrix(size(A));
	Matrix B_T = transpose(B);
	for(int i = 1; i <= size(A); i++)
	{
		if( length(A->rows[i]) < 1 )
		{
			continue;  //if we have nothing in current list of A, move to next list
		}
		for(int j = 1; j <= size(A); j++)
		{
			if( length(B_T->rows[j]) < 1 )
			{
				continue; //if we have nothing in current list of B, move to next list
			}
			double AB_value = vectorDot(A->rows[i], B_T->rows[j]);
			changeEntry(AB, i, j, AB_value);
		}
	}
	return AB;
}

//printMatrix()
//prints a string representation of Matrix M to filestream out
//zero rows are not printed. Each non-zero is represented as one
//line consisting of the row number, followed by a colon, a space,
//then a space separated list of pairs "(col, val)" giving the
//column numbers and non-zero values in that row. The double val
//will be rounded to 1 decimal point
void printMatrix(FILE* out, Matrix M)
{
	//if M->NNZ > 0, then continue with method
	if(M->NNZ > 0)
	{
		for(int i = 1; i <= size(M); i++)
		{
			if(length(M->rows[i]) > 0)
			{
				fprintf(out, "%d:", i);
				moveFront(M->rows[i]);
				while(index(M->rows[i]) > -1)
				{
					Entry to_print = (Entry)get(M->rows[i]);
					fprintf(out, " (%d, %0.1f)", to_print->column, to_print->value);
					moveNext(M->rows[i]);
				}
				fprintf(out, "\n");
			}
			// else if(length(M->rows[i]) == 0)
			// {
			// 	fprintf(out, "the row at row %d is empty\n", i);
			// }
		}
	}
	fprintf(out, "\n");
}
