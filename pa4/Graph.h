//-------------------------------------------------------------------------------
//Andy He
//ahe206
//cse101
//Nov 17th, 2019
//Graph.h
//header file for Graph ADT
//-------------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL 0
#include"List.h"

//Graph reference type
typedef struct GraphObj* Graph;


//Constructors & Destructors------------------------------------------------

//newGraph()
Graph newGraph(int n);

//destructor
void freeGraph(Graph *pG);

//Access functions----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

//Manipulation Procedures---------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

//Other operations----------------------------------------------------------
void printGraph(FILE* out, Graph G);

#endif