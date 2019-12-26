//------------------------------------------------------------
//Andy He
//ahe206
//cse101
//October 3rd, 2019
//Implements the List ADT built to indirectly sort
//a file that contains lines of strings with a similar
//concept to Insertion Sort
//Lex.c
//------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char* argv[])
{
    FILE* in;
    FILE* out;
    char* line = calloc(MAX_LEN, sizeof(char));
    char** list_of_lines;
    int num_of_lines = 0;
    int line_index = 0;

    //printf("About to enter checking of argc = 3\n");
    if( argc != 3 )
    {
        fprintf(stderr, "Usage: %s input-file output-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //printf("Exited checking of argc = 3\n");

    //printf("About to enter: initializing in\n");
    in = fopen(argv[1], "r");
    //printf("Exited: initializing in\n");

    //printf("About to enter: initializing out\n");
    out = fopen(argv[2], "w");
    //printf("Exited: initializing out\n");

    if( in == NULL )
    {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if( out == NULL )
    {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    //printf("Entered: figuring out num of lines\n");
    while( fgets(line, MAX_LEN, in) != NULL )
    {
        num_of_lines++;
    }
    //printf("Exited: found out num of lines: %d\n", num_of_lines);


    //printf("Entered: fseek\n");
    fseek(in, 0, SEEK_SET);
    //printf("Exited: fseek\n");
    //got this line of code from: https://stackoverflow.com/questions/32366665/resetting-pointer-to-the-start-of-file
    //didn't know how to reset the file pointer to the beginning, so had to do a google search


    //printf("Entered: calloc'd size of string[]\n");
    list_of_lines = calloc(num_of_lines, sizeof(char*)); 
    //calloc'd enough space for the string array (aka char[][])
    //printf("Exited: calloc'd done\n");

    for(int i = 0; i < num_of_lines; i++)
    {
        list_of_lines[i] = calloc(MAX_LEN, sizeof(char));
    }

    //printf("Entering: copying out's lines to list_of_lines\n");
    while( fgets(line, MAX_LEN, in) != NULL )
    {
        //printf("Line %d: %s\n", line_index, line);
        strcpy(list_of_lines[line_index], line);
        //printf("Done copying line %d\n", line_index);
        line_index++;
        //printf("Line index: %d\n", line_index);
    }
    //printf("Exited: copied out's lines to list_of_lines\n");

    List sorted_list = newList();
    append(sorted_list, 0);

    for(int i = 1; i < num_of_lines; i++)
    {
        moveFront(sorted_list);
        char* to_compare = list_of_lines[i];

        int unsorted_index = i;
        while(unsorted_index > 0 && strcmp(to_compare, list_of_lines[get(sorted_list)]) >= 0) //we want to compare the list_of_lines[index...n-1] unsorted elements to the cursor element of the list(which is sorted)
        {
            moveNext(sorted_list); //if we cant find something to swap or insert, then move the cursor
            unsorted_index--;
        }
        if(index(sorted_list) > -1 )//cursor exists after while loop, aka there is a place to insert the index
        {
            insertBefore(sorted_list, i);
        }
        else //if the cursor does not exist, aka we are on the biggest element, then just add it to the back of the list
        {
            append(sorted_list, i);
        }
    }

    printList(stdout, sorted_list);
    moveFront(sorted_list);
    while(index(sorted_list) > -1)
    {
        fprintf(out, "%s", list_of_lines[get(sorted_list)]);
        moveNext(sorted_list);
    }

    fclose(in);
    fclose(out);

    for(int i = 0; i < num_of_lines; i++)
    {
        free(list_of_lines[i]);
    }
    free(list_of_lines);
    free(line);
    freeList(&sorted_list);
    return(0);
}