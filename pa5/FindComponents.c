//Andy He
//ahe206
//Nov 30, 2019
//cse101 fall 19
//FindComponents.c
//Client program that reads in an input file listing the number of vertices and a list
//of pairs of points, each pair with a starting point and destination
//Will determine if such graph contains strongly connected components

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[])
{
	FILE* in;
	FILE* out;
	char line[MAX_LEN];
	int vertices;

	if(argc != 3)
	{
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if( (in=fopen(argv[1], "r")) == NULL )
	{
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if( (out=fopen(argv[2], "w")) == NULL)
	{
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	fscanf(in, "%d", &vertices);

	Graph G = newGraph(vertices);

	while(fgets(line, MAX_LEN, in) != NULL)
	{
		int x;
		int y;
		fscanf(in, "%d %d", &x, &y);
		if(x == 0 && y == 0)
		{
			break;
		}
		addArc(G, x, y);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	List stack = newList();
	for(int i = 1; i <= vertices; i++)
	{
		append(stack, i);
	}
	DFS(G, stack);
	Graph G_T = transpose(G);
	DFS(G_T, stack);

	//printf("finished the two DFS\n");

	//now we want to find the number of strongly connected components
	int num_of_scc = 0;
	if(length(stack) != 0)
	{
		moveFront(stack);
	}
	while(index(stack) > -1)
	{
		//if(G_T->p[get(stack)] < 1)
		if(getParent(G_T, get(stack)) < 1)
		{
			num_of_scc++;
		}
		moveNext(stack);
	}
	if(num_of_scc == 0)
	{
		fprintf(out, "G contains no strongly connected components.\n");
	}
	else
	{
		fprintf(out, "G contains %d strongly connected components:\n", num_of_scc);
		//printList(out, stack);
		//printf("\n");
		moveBack(stack);
		// printList(stdout, stack);
		List* SCC = calloc(num_of_scc + 1, sizeof(List));
		for(int i = 1; i <= num_of_scc; i++)
		{
			SCC[i] = newList();
		}
		//printf("in FindComponents, exited first for loop\n");
		for(int i = num_of_scc; i >= 1; i--)
		{
			while(getParent(G_T, get(stack)) > 0) //while the parent of current stack element is not null
			{
				//we will want to prepend elements onto appropriate SCC list
				prepend(SCC[i], get(stack));
				movePrev(stack);
			}
			prepend(SCC[i], get(stack));
			//append(SCC[i], get(stack));
			movePrev(stack);
		}
		//printf("in FindComponents, exited second for loop\n");
		int index = 1;
		for(int i = num_of_scc; i >= 0; i--)
		{
			if(i == 0)
			{
				freeList(&SCC[i]);
				continue;
			}
			fprintf(out, "Component %d: ", index);
			printList(out, SCC[i]);
			fprintf(out, "\n");
			index++;
			freeList(&SCC[i]);
		}
		//printf("in FindComponents, exited third for loop\n");
		free(SCC);
		SCC = NULL;
	}
	freeGraph(&G);
	freeGraph(&G_T);
	// for(int i = 1; i <= num_of_scc; i++)
	// {
	// 	freeList(&SCC[i]);
	// }
	freeList(&stack);
}