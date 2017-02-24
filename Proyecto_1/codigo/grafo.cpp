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

//Estructura de aristas
struct Arista
{
    int nodo1; //primer nodo
    int nodo2; //segundo nodo
    int costo; //Valor del costo de la arista
    int beneficio; //Valor del beneficio de la arista
};
 
// Estructura que representa nodo
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// Estructura que representa la lista de adyacencia
struct AdjList
{
    struct AdjListNode *head;  
 
// Estructura que representa el grafo
struct Graph
{
    int V; //Numero de nodos
    struct AdjList* array; //Lista de adyacencia
};
 
// Funcion para crear nuevo nodo
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// Funcion que crea grafo con V nodos
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V+1;
 
    graph->array = (struct AdjList*) malloc((V+1) * sizeof(struct AdjList));
 
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    

    return graph;
}
 
//Funcion que anade nodos al grafo 
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

//Funcion que crea una arista
struct Arista crear_arista(int nodo1, int nodo2, int costo, int beneficio)
{
    struct Arista nueva_arista;
    nueva_arista.nodo1 = nodo1;
    nueva_arista.nodo2 = nodo2;
    nueva_arista.costo = costo;
    nueva_arista.beneficio = beneficio;
    return nueva_arista;
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

//Funcion que extrae del deque de aristas la arista que cumple con solicitado
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