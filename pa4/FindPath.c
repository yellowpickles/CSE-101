//------------------------------------------------------------------------------------------------------------
//Andy He
//ahe206
//Nov 21, 2019
//cse101 fall 19
//FindPath.c
//Client program that reads in an input file listing the number of vertices of the graph, all edges, and then 
//a list of pairs of points, each pair with a starting point and a destination.
//------------------------------------------------------------------------------------------------------------
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

	if( (in=fopen(argv[1], "r")) == NULL)
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

	//fprintf(stdout, "number of vertices of the graph is %d\n", getOrder(G));

	//adding edges to the graph
	while(fgets(line, MAX_LEN, in) != NULL )
	{
		int a;
		int b;
		fscanf(in, "%d %d", &a, &b);
		if(a == 0 && b == 0)
		{
			break;
		}
		addEdge(G, a, b);
	}
	printGraph(out, G);
	//fprintf(stdout, "\n");
	List path = newList();
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		int source;
		int destination;
		fscanf(in, "%d %d", &source, &destination);
		if(source == 0 || destination == 0)
		{
			break;
		}
		BFS(G, source);
		fprintf(out, "\n");
		int distance = getDist(G, destination);
		if(distance != -1)
		{
			fprintf(out, "The distance from %d to %d is %d\n", source, destination, distance);
			fprintf(out, "A shortest %d-%d path is: ", source, destination);
			getPath(path, G, destination);
			printList(out, path);
		}
		else
		{
			fprintf(out, "The distance from %d to %d is %s\n", source, destination, "infinity");
			fprintf(out, "No %d-%d path exists\n", source, destination);
		}
		fprintf(out, "\n");
		//fprintf(stdout, "\n");
		clear(path);
	}

	// printGraph(stdout, G);

	fclose(in);
	fclose(out);

	freeGraph(&G);
	freeList(&path);

	return(EXIT_SUCCESS);
}