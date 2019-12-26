//Andy He
//ahe206
//cse101
//Nov 17, 2019
//Graph.c
//uses adjacency list as a representation of Graphs, performs necessary functions

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

#define NIL 0
#define INF -1	

typedef struct GraphObj
{
	int order;
	int size;
	int source;
	List* adj; 
	int* p;
	int* d;
	char* color;
}GraphObj;

Graph newGraph(int n)
{
	Graph G = calloc(1, sizeof(GraphObj));
	assert( G != NULL );
	G->order = n;
	G->size = 0;
	G->source = NIL;
	G->adj = calloc(n+1, sizeof(List));
	G->p = calloc(n+1, sizeof(int));
	G->d = calloc(n+1, sizeof(int));
	G->color = calloc(n+2, sizeof(char));
	for(int i = 1; i <= n; i++)
	{
		G->adj[i] = newList();
		G->p[i] = NIL;
		G->d[i] = INF;
		G->color[i] = 'w';
	}
	G->color[n+1] = '\0';
	return G;
}

void freeGraph(Graph* pG)
{
	if ( pG != NULL && *pG != NULL )
	{
		makeNull(*pG);
		for(int i = 1; i <= getOrder(*pG); i++)
		{
			freeList( &((*pG)->adj[i]) );
			//free the other stuff as well
		}
		free((*pG)->adj);
		(*pG)->adj = NULL;

		free((*pG)->p);
		(*pG)->p = NULL;

		free((*pG)->d);
		(*pG)->d = NULL;

		free((*pG)->color);
		(*pG)->color = NULL;

		free(*pG);
		*pG = NULL;
	}
}

//Access functions--------------------------------------------------

//returns order, aka number of vertices
int getOrder(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

//returns size, aka number of edges
int getSize(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

//returns source vertex most recently used in BFS, NIL if BFS hasn't been called
int getSource(Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->source;
}

//returns parent
//pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->p[u];
}

//returns distance
//pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->d[u];
}

//returns path
//pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u)
{
	if( G == NULL )
	{
		fprintf(stderr, "Graph error: calling getPath() on NULL Graph refererence\n");
		exit(EXIT_FAILURE);
	}
	if( u < 1 || u > getOrder(G) )
	{
		fprintf(stderr, "Graph error: calling getPath() when u is out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if(u == getSource(G))
	{
		//prepend(L, getSource(G));
		append(L, getSource(G));
		//printf("%d ", getSource(G));
	}
	else if(G->p[u] == NIL)
	{
		// fprintf(stderr, "%d is not reachable from %d\n", u, getSource(G));
		// exit(EXIT_FAILURE);
		append(L, NIL);
	}
	else
	{
		getPath(L, G, G->p[u]);
		//printf("%d ", u);
		append(L, u); //we call append because when the recursion bottoms out, 
		//we want to return back down the tree, and insert those elements to the back, to get the path in order
	}
}

//Manipulation procedures----------------------------------------

//makeNull()
//deletes all edges of G, restoring it to the no edge state, or null state
void makeNull(Graph G)
{
	if( G == NULL )
	{
		fprintf(stderr, "Graph error: calling makeNull() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	//want to reset, or clear all the adjacency lists
	//reset p, d, and color
	for(int i = 1; i <= getOrder(G); i++)
	{
		clear(G->adj[i]);
		G->p[i] = NIL;
		G->d[i] = INF;
		G->color[i] = 'w';
	}
}

//addEdge()
//pre: 1 <= u & v <= getOrder(G)
//inserts new edge joining u to v
//i.e u is added to adjacency list of v & v is added to adjacency list of u
void addEdge(Graph G, int u, int v)
{
	//we essentially just call addArc on (u, v) and (v, u)
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if( u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G))
	{
		fprintf(stderr, "Graph error: calling addEdge() on invalid u/v vertices\n");
		exit(EXIT_FAILURE);
	}
	if(u != v)
	{
		addArc(G, u, v);
		addArc(G, v, u);
		G->size--;
		//need to decrease size because the two calls to addArc() increases size by two
	}
}

//addArc()
//pre: 1 <= u & v <= getOrder(G)
//adds directed edge from u to v
//i.e v is added to adjacency list of u
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if( u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G))
	{
		fprintf(stderr, "Graph error: calling addArc() on invalid u/v vertices\n");
		exit(EXIT_FAILURE);
	}
	//not sure if we need to worry about adding duplicate arcs/edges?
	//we do... so if either u exists in adj[v] or if v exists in adj[u]
	//then we just exit out of the loop
	int duplicate = 0;
	if(length(G->adj[u]) > 0)
	{
		moveFront(G->adj[u]);
	}
	while(index(G->adj[u]) > -1)
	{
		duplicate = (v == get(G->adj[u]));
		if(duplicate == 1)
		{
			return;
		}
		moveNext(G->adj[u]);
	}

	if(duplicate != 1)
	{
		if(index(G->adj[u]) == -1 && length(G->adj[u]) == 0)
		{
			//in the case that u has no adjacency at the moment
			//and/or that the cursor is pointing to nothing
			append(G->adj[u], v);
		}
		else 
		{
			//the case that the cursor exists in u's adjacency list
			moveFront(G->adj[u]);
			//by default, there is no duplicate
			while(index(G->adj[u]) > -1 && v > get(G->adj[u]))
			{
				moveNext(G->adj[u]);
			}
			if(index(G->adj[u]) > -1)
			{
				//the case that v should be inserted somewhere in the middle of 
				//u's adjacency list
				insertBefore(G->adj[u], v);
			}
			else
			{
				//the case that v should be inserted at the end
				append(G->adj[u], v);
			}
		}
		G->size++;
	}
}

//
void BFS(Graph G, int s)
{
	for(int i = 1; i <= getOrder(G); i++)
	{
		if(i != s)
		{
			G->color[i] = 'w';
			G->d[i] = INF;
			G->p[i] = NIL;
		}
	}
	G->source = s;
	G->color[s] = 'g';
	G->d[s] = 0;
	G->p[s] = NIL;
	List queue = newList();
	//note: the queue methods of list are: 
	//enqueue: append()
	//dequeue: deleteFront()
	append(queue, s);
	while(length(queue) != 0)
	{
		//to dequeue something, get the front, then delete the front
		int x = front(queue);
		deleteFront(queue);
		if(length(G->adj[x]) > 0)
		{
			moveFront(G->adj[x]);
		}
		while(index(G->adj[x]) > -1)
		{
			int y = get(G->adj[x]);
			if(G->color[y] == 'w')
			{
				G->color[y] = 'g';
				G->d[y] = G->d[x] + 1;
				G->p[y] = x;
				append(queue, y);
			}
			moveNext(G->adj[x]);
		}
		G->color[x] = 'b';
	}
	freeList(&queue);
}

//Other operations-----------------------------------------------
void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		fprintf(stderr, "Graph error: calling printGraph on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); i++)
	{
		fprintf(out, "%d: ", i);
		if(length(G->adj[i]) > 0)
		{
			printList(out, G->adj[i]);
		}
		fprintf(out, "\n");
	}
}