//Andy He
//ahe206
//cse101
//Nov 30, 2019
//Graph.h
//header file for Graph.c

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL 0
#include"List.h"

typedef struct GraphObj* Graph;

/*Constructors-Destructors*/
Graph newGraph(int n);
void freeGraph(Graph *pG);

/*Access functions*/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); //pre: 1 <= u <= n=getOrder(G)
int getDiscover(Graph G, int u); //pre: 1 <= u <= n=getOrder(G)
int getFinish(Graph G, int u); //pre: 1 <= u <= n=getOrder(G)

/*Manipulation procedures*/
void addArc(Graph G, int u, int v); //pre: 1 <= u & v <= getOrder(G)
void addEdge(Graph G, int u, int v); //pre: 1 <= u & v <= getOrder(G)
void DFS(Graph G, List S); //pre: length(S) == getOrder(G);

/*Other functions*/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif