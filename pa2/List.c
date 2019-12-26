//------------------------------------------------------------
//Andy He
//ahe206
//101
//Oct 13, 2019
//List.c
//List ADT that implements a linked listed data structure, utilizes concept of a 'cursor'
//------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"List.h"

//NodeObj
typedef struct NodeObj
{
	void* data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

//Node
typedef NodeObj* Node;

//newNode()
//constructor of the Node type
Node newNode(void* data)
{
	Node new_node = malloc(sizeof(NodeObj));
	assert (new_node != NULL);
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return(new_node);
}

//freeNode()
//destructor for the Node type
void freeNode(Node* previousNode)
{
	if(previousNode != NULL && *previousNode != NULL)
	{
		free(*previousNode);
		*previousNode = NULL;
	}
}

//ListObj
typedef struct ListObj
{
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
} ListObj;

//newList()
//constructor for the List type
List newList(void)
{
	List L = malloc(sizeof(ListObj));
	assert( L != NULL );
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	return(L);
}

//freeList()
//destructor for the List type
void freeList(List* pL)
{
	if( pL != NULL && *pL != NULL )
	{
		while(length(*pL) > 0)
		{
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//returns the length of the List
int length(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling length() on NULL List reference\n ");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

//returns the index of the cursor element if defined, -1 otherwise
int index(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if( L->cursor == NULL || length(L) <= 0)
	{
		//printf("Error: cursor is NULL\n");
		return -1;
	}
	return L->index;
}

//returns front element of L, pre: length() > 0
void* front(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling front() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}

//returns back element of L, pre: length() > 0
void* back(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling back() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return(L->back->data);
}

//returns cursor element of L, pre: length() > 0, index() >= 0
void* get(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling get() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		fprintf(stderr, "List Error: calling get() on List with no defined cursor\n");
		exit(EXIT_FAILURE);
	}
	return L->cursor->data;
}

//MANIPULATION PROCEDURES

//resets L to its original empty state
void clear(List L)
{
	if ( L == NULL )
	{
		fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	while(length(L) > 0)
	{
		deleteFront(L);
	}

	L->front = L->back = L->cursor = NULL;
	L->index = -1;
	L->length = 0;
} 

//if L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if( length(L) < 1)
	{
		fprintf(stderr, "List Error: calling moveFront() on empty List\n");
		exit(EXIT_FAILURE);
	}
	L->cursor = L->front; //points L's cursor to front
	L->index = 0; //changes index to where it is pointing, aka index 0
}

//if L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling moveBack() on NULL List referencec\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling moveBack() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	L->cursor = L->back;
	//printf("cursor's previous is %d\n",L->cursor->data);
	L->index = length(L) - 1;
}

//if cursor is defined and not at front move cursor one step 
//toward the front of L; if cursor is defined and at front,
//cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling movePrev() on NULL List referencec\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL) //if cursor is undefined
	{
		fprintf(stderr, "List Error: calling movePrev() on NULL cursor reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == 0) //if cursor is defined and at the front
	{
		L->cursor = NULL;
		L->index = -1;
	}
	else if(index(L) > 0 && index(L) < length(L)) //if cursor isnt at the front
	{
		L->cursor = L->cursor->prev;
		//printf("index in movePrev is %d\n", L->index);
		L->index--;
		//printf("index in movePrev is %d\n", L->index);
	}
}

//if cursor is defined and not at back, move cursor one step
//toward the back of L; if cursor is defined and at back, cursor
//becomes undefined; if cursor is undefined do nothing
void moveNext(List L)
{
	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL)
	{
		fprintf(stderr, "List Error: calling moveNext() on NULL cursor reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == length(L) - 1) //if cursor is defined at the back
	{
		L->cursor = NULL;
		L->index = -1;
	}
	else if(index(L) >= 0 && index(L) < (length(L) - 1))
	{
		L->cursor = L->cursor->next;
		L->index++;
	}
} 

//insert new element onto L, if L is non-empty, insertion takes place
//before front element
void prepend(List L, void* data)
{
	Node new_node = newNode(data);

	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) == 0) //if the list is empty, then L's front and back is new_node
	{
		L->front = L->back = new_node;
	}
	else
	{
		new_node->next = L->front; //point new_node's next node to the current front node
		L->front->prev = new_node;
		L->front = new_node; //now point the list's front to the new node
		L->index++; //increase index if the list wasn't empty originally
	}
	L->length++;
	//freeNode(&new_node);
}

//insert new element onto L, if L is non-empty, insertion
//takes place after back element
void append(List L, void* data)
{
	Node new_node = newNode(data);

	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) == 0)//if list is empty, the L's front & back is new_node
	{
		L->front = L->back = new_node;
	}
	else//if list has more than one element
	{
		L->back->next = new_node;//point L's back's next to new node
		new_node->prev = L->back;
		L->back = new_node; //redirect L's back to new node
	} 
	L->length++;
	//freeNode(&new_node);
}

//insert new element before cursor 
//pre: length() > 0, index() >= 0
void insertBefore(List L, void* data)
{
	Node new_node = newNode(data);

	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		fprintf(stderr, "List Error: calling insertBefore() on NULL cursor reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == 0) //if the cursor element is in the front, call prepend
	{
		prepend(L, data);
	}
	else
	{
		//first we need to point new_node's prev and next to the cursor and cursor.prev
		//this ensures no loss of information by accidentally cutting
		//off the rest of the doubly linked list when inserting before
		new_node->prev = L->cursor->prev;
		new_node->next = L->cursor;
		//then we can change the cursor's prev's next to point to our new node
		//then change where cursor's prev is pointing to maintain structure
		L->cursor->prev->next = new_node;
		L->cursor->prev = new_node;
		L->index++; //we make these calls to index and length bc the other condition
		L->length++;//where we call prepend() already does it
	}
	//freeNode(&new_node);
}

//insert new element after cursor
//pre: length() > 0 & index() >= 0
void insertAfter(List L, void* data)
{
	Node new_node = newNode(data);

	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		fprintf(stderr, "List Error: calling insertAfter() on NULL cursor reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == (length(L) - 1))
	{
		append(L, data);
	}
	else
	{
		new_node->prev = L->cursor;
		new_node->next = L->cursor->next;
		L->cursor->next = new_node;
		L->cursor->next->prev = new_node;
		L->length++;
	}
	//freeNode(&new_node);
}

//Deletes the front element
//pre: length() > 0
void deleteFront(List L)
{
	Node to_delete = NULL;

	if( L == NULL )
	{
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
		exit(EXIT_FAILURE);
	}
	to_delete = L->front;
	if(length(L) > 1)
	{
		if(L->cursor == to_delete)//if cursor points to front
			//we need to delete the cursor and reset index
	 	{
	 		L->cursor = NULL;
	 		L->index = -1;
	 	}
		L->front = L->front->next;
	}
	else
	{
		if(L->cursor == to_delete)
	 	{
	 		L->cursor = NULL;
	 		L->index = -1;
	 	}
		L->front = L->back = NULL;
	}
	if(L->cursor != NULL) //if there is a cursor, we need to update index
	{
		L->index--;
	}
	L->length--;
	freeNode(&to_delete);
}

//Deletes the back element
//pre: length() > 0
void deleteBack(List L)
{
	Node to_delete = NULL;
	if( L == NULL )
	{
	 	fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
	 	exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
	 	fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
	 	exit(EXIT_FAILURE);
	}

	to_delete = L->back;
	if(length(L) > 1)
	{
	 	if(L->cursor == to_delete) //we need to account for if the cursor points at the back
	 	{
	 		L->cursor = NULL;
	 		L->index = -1;
	 	}
	 	L->back = L->back->prev;
	}
	else //if length == 1
	{
	 	if(L->cursor == to_delete)
	 	{
	 		L->cursor = NULL;
	 		L->index = -1;
	 	}
	 	L->back = L->front = NULL;
	}
	L->length--;
	freeNode(&to_delete);
}

//delete element that the cursor is pointing to, making cursor undefined
//pre: length() > 0, index() >= 0
void delete(List L)
{
	if(L==NULL)
	{
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1)
	{
		fprintf(stderr, "List Error: calling delete() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		fprintf(stderr, "List Error: calling delete() on NULL cursor reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->front)
	{
		deleteFront(L);
	}
	else if(L->cursor == L->back)
	{
		deleteBack(L);
	}
	else
	{
		Node to_delete = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&to_delete);
		L->length--;
	}
	L->index = -1;
}