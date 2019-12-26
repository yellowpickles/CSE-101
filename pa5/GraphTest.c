//Andy He
//ahe206
//Nov 30, 2019
//cse101
//GraphTest.c
//my tester for the graph.c adt

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include"Graph.h"

int main()
{
	Graph A = newGraph(100);

	//the following commented out block of code is from the grading script

	// List L = newList();
	// for(uint8_t i = 1; i <= 100; i++)
	// {
	// 	if(getDiscover(A, i) != UNDEF)
	// 	{
	// 		printf("failed test 1\n");
	// 	}
	// }
	// addArc(A, 64, 4);
	// addArc(A, 64, 3);
	// addArc(A, 42, 2);
	// addArc(A, 2, 64);
	// addArc(A, 4, 2);
	// addArc(A, 3, 42);
	// for(uint8_t i = 1; i <= 100; i++)
	// {
	// 	prepend(L, i);
	// }
	// DFS(A, L);
	// if(getDiscover(A, 100) != 1)
	// {
	// 	printf("failed test 2\n");
	// }
	// if (getDiscover(A, 64) != 73) 
	// {
	// 	printf("my test 3 result: %d\n", getDiscover(A, 64));
	// 	printf("failed test 3\n");
	// }
	// if (getDiscover(A, 4) != 80)
	// {
	// 	printf("my test 4 result: %d\n", getDiscover(A, 4));
	// 	printf("failed test 4\n");
	// } 
	// DFS(A, L);
	// if (getDiscover(A, 4) != 126) 
	// {
	// 	printf("my test 5 result: %d\n", getDiscover(A, 4));
	// 	printf("failed test 5\n");
	// }	
	// if (getDiscover(A, 63) != 117) 
	// {
	// 	printf("my test 6 result: %d\n", getDiscover(A, 63));
	// 	printf("failed test 6\n");
	// }
	// DFS(A, L);
	// if (getDiscover(A, 65) != 71) 
	// {
	// 	printf("my test 7 result: %d\n", getDiscover(A, 65));
	// 	printf("failed test 7\n");
	// }
	// if (getDiscover(A, 1) != 199) 
	// {
	// 	printf("my test 8 result: %d\n", getDiscover(A, 1));
	// 	printf("failed test 8\n");
 //    }

	addArc(A, 1 ,2);
	addArc(A, 1, 3);
	addArc(A, 2, 4);
	addArc(A, 2, 5);
	addArc(A, 2, 6);
	addArc(A, 3, 4);
	addArc(A, 4, 5);
	addArc(A, 5, 6);
	//now trying to add duplicate ARCS
	addArc(A, 1, 2);
	addArc(A, 1, 3);
	addArc(A, 2, 4);
	addArc(A, 2, 5);
	addArc(A, 2, 6);
	addArc(A, 3, 4);
	addArc(A, 4, 5);
	addArc(A, 5, 6);

	printGraph(stdout, A);


	
	Graph G = newGraph(7);
	addArc(G, 1, 4);
	addArc(G, 1, 5);
	addArc(G, 4, 5);
	addArc(G, 2, 3);
	addArc(G, 2, 6);
	addArc(G, 3, 5);
	addArc(G, 6, 5);

	printGraph(stdout, G);

	Graph H = newGraph(7);
	addArc(H, 1, 4);
	addArc(H, 1, 5);
	addArc(H, 4, 5);
	addArc(H, 2, 3);
	addArc(H, 2, 6);
	addArc(H, 3, 7);
	addArc(H, 6, 7);

	printGraph(stdout, H);
}