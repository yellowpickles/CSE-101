//------------------------------------------------------------
//Andy He
//ahe206
//101
//Nov 30, 2019
//List.h
//header file for List.c
//------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;


//Constructors & Destructors
List newList(void);

void freeList(List* pL);

//Access functions
int length(List L); //returns the number of elements in L
int index(List L); //returns index of the cursor element if defined, -1 otherwise
int front(List L); //returns front element of L, pre: length() > 0
int back(List L); //returns back element of L, pre: length() > 0
int get(List L); //returns cursor element of L, pre: length() > 0, index() >= 0
int equals(List A, List B); //returns true(1) iff Lists A and B are in same state, 
							//returns false(0) otherwise

//Manipulation procedures
void clear(List L); //resets L to its original empty state
void moveFront(List L); //if L is non-empty, sets cursor under the front element,
						//otherwise does nothing
void moveBack(List L); //if L is non-empty, sets cursor under the back element,
					   //otherwise does nothing
void movePrev(List L); //If cursor is defined and not at front, move cursor one
					   //step toward the front of L; if cursor is defined and at
					   //front, cursor becomes undefined; if cursor is undefined
					   //do nothing
void moveNext(List L); //if cursor is defined and not at back, move cursor one
					   //step toward the back of L; if cursor is defined and at
					   //back, cursor becomes undefined; if cursor is undefined
					   //do nothing
void prepend(List L, int data); //insert new element into L. if L is non-empty,
								//insertion takes place before front element
void append(List L, int data);  //insert new element into L. If L is non-empty.
								//insertion takes place after back element
void insertBefore(List L, int data);	//insert new element before cursor.
										//pre: length() > 0, index() >= 0
void insertAfter(List L, int data); 	//insert new element after cursor.
										//pre: length() > 0, index() >= 0
void deleteFront(List L); 	//Delete the front element, pre: length() > 0
void deleteBack(List L); 	//Delete the back element, pre: length() > 0
void delete(List L); 	//Delete cursor element, making cursor undefined
						//pre: length() > 0, index() >= 0

//Other Operations--------------------
void printList(FILE* out, List L);	//prints to the file pointed to by out, a 
									//string representation of L consisting
									//of a space separated sequence of integers,
									//with front on left
List copyList(List L); 	//Returns a new List representing the same integer
						//sequence as L. The cursor in the new list is undefined,
						//regardless of the state of the cursor in L. The state
						//of L is unchanged
//List concatList(List A, List B); 	//Returns a new List which is the concatentation of 
									//A and B. The cursor in the List is undefined,
									//regardless of the states of the cursors in A and B.
									//The states of A and B are unchanged

#endif