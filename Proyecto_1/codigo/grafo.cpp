/** Universidad Simón Bolívar
*   CI5437 - Diseño de Algoritmos I
*   Trimestre Ene-Mar 2017
*
*   Proyecto I
*   Programa Principal.
* 
*   Hecho por: Enrique Iglesias 11-10477
*              Gabriel Iglesias 11-10476
*
*   Última modificación: 23/02/17
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <time.h>
#include <unistd.h>
#include <deque> 

#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Arista
{
    int nodo1;
    int nodo2;
    int costo;
    int beneficio;
};
 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
    deque<Arista> aristas;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V+1;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc((V+1) * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // 
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // 
    struct AdjListNode* newNode2 = newAdjListNode(src);
    newNode2->next = graph->array[dest].head;
    graph->array[dest].head = newNode2;
}
 
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 1; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

struct Arista extraer_arista (deque<Arista> aristas, int nodo1, int nodo2)
{
    for (int i = 0; i < aristas.size(); ++i)
    {
        if (((aristas[i].nodo1 == nodo1) && (aristas[i].nodo2 == nodo2)) || ((aristas[i].nodo1 == nodo2) && (aristas[i].nodo2 == nodo1)))
        {
            return aristas[i];
        }
    }
    return Arista();
};