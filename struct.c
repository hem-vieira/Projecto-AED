#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "oper.h"
#include "ficheiro.h"

/*Estrutura que guarda os dados referentes a cada mapa*/

void criaNovoNo (ronda** lp)
 {
  ronda *novoNo;

  novoNo = (ronda*) malloc(sizeof(ronda));
  
  if (novoNo == NULL){
      exit (0);
  }

  else if(novoNo!=NULL) {
    novoNo->coluna =0;
    novoNo->linha =0;
    novoNo->modo =0;
    novoNo->numAtrac =0;

    *lp = novoNo;    
  } 

  else{
      exit(0);
  }

}


GRAFO* createGraph(int vertices)
{
    GRAFO* graph = malloc(sizeof(GRAFO));

    if(graph == NULL){
      exit(0);
    }

    graph->numVertices = vertices;
 
    graph->adjLists = malloc(vertices * sizeof(VERTICE*));

    if(graph->adjLists == NULL){
      exit(0);
    }
 
    int i;

    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
 
    return graph;
}

VERTICE* createVertice(int x, int y, int peso)
{
    VERTICE* vertice = malloc(sizeof(VERTICE));

    if(vertice == NULL){
      exit(0);
    }

    vertice->x_vert = x;
    vertice->y_vert = y;
    vertice->peso = peso;
    vertice->next = NULL;
    return vertice;

}

void addEdge(GRAFO* graph, int srcx, int srcy, int destx, int desty, int pesosrc, int pesodest)
{
    /* Add edge from src to dest*/
    //vertice = createVertice(destx, desty, pesodest);
    vertice->next = graph->adjLists[src];
    graph->adjLists[src] = vertice;
 
    /* Add edge from dest to src*/
   // vertice = createVertice(srcx, srcy, pesosrc);
    vertice->next = graph->adjLists[dest];
    graph->adjLists[dest] = vertice;
}
 
/*void printGraph(GRAFO* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        NO* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}*/


