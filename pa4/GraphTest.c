//Andy He
//ahe206
//Nov 21, 2019
//cse101 fall 2019
//GraphTest.c
//my own tester for the Graph.c ADT

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main()
{
	Graph G = newGraph(6);
	addEdge(G, 1 ,2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	// addEdge(G, 1, 5);
	// addEdge(G, 3, 6);
	// addEdge(G, 2, 3);
	// addEdge(G, 4, 4);
	//now trying to add duplicate edges
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);

	//printGraph(stdout, G);

	BFS(G, 1);
	List from1to5 = newList();
	// fprintf(stdout, "The distance from 1 to 5 is: %d\n", getDist(G, 5));
	// fprintf(stdout, "path from 1 to 5 is: ");
	// getPath(from1to5, G, 5);
	// printList(stdout, from1to5);
	// fprintf(stdout, "\n");

	makeNull(G);
	//printGraph(stdout, G);

	addEdge(G, 1, 4);
	addEdge(G, 1, 5);
	addEdge(G, 4, 5);
	addEdge(G, 2, 3);
	addEdge(G, 2, 6);
	addEdge(G, 3, 5);
	addEdge(G, 6, 5);

	//printGraph(stdout, G);

	Graph H = newGraph(7);
	addEdge(H, 1, 4);
	addEdge(H, 1, 5);
	addEdge(H, 4, 5);
	addEdge(H, 2, 3);
	addEdge(H, 2, 6);
	addEdge(H, 3, 7);
	addEdge(H, 6, 7);

	//printGraph(stdout, H);
	BFS(H, 2);
	List from2to7 = newList();
	//fprintf(stdout, "The distance from 2 to 7 is %d\n", getDist(H, 7));
	//fprintf(stdout, "A shortest 2-7 path is ");
	//getPath(from2to7, H, 7);
	//printList(stdout, from2to7);
	//fprintf(stdout, "\n");

	//the following test is from DG_getPath from summer 2019's grading script
	List path = newList();
	List path_copy = newList();
	Graph A = newGraph(100);
	addArc(A, 64, 4);
	addArc(A, 64, 3);
	addArc(A, 42, 2);
	addArc(A, 2, 64);
	addArc(A, 4, 2);
	addArc(A, 3, 42);
	BFS(A, 3);
	getPath(path, A, 64);
	append(path_copy, 3);
	append(path_copy, 42);
	append(path_copy, 2);
	append(path_copy, 64);
	printf("path is ");
	printList(stdout, path);
	printf("\n");
	printf("copied path is ");
	printList(stdout, path_copy);
	printf("\n");

	BFS(A, 2);
	getPath(path, A, 2);
	append(path_copy, 2);
	printf("path is ");
	printList(stdout, path);
	printf("\n");
	printf("copied path is ");
	printList(stdout, path_copy);
	printf("\n");

	getPath(path, A, 99);
	printf("path is ");
	printList(stdout, path);
	printf("\n");
	printf("copied path is ");
	printList(stdout, path_copy);
	printf("\n");

	freeList(&from1to5);
	freeList(&from2to7);
	freeGraph(&G);
	freeGraph(&H);
	return EXIT_SUCCESS;
}