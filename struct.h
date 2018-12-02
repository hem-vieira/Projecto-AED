#ifndef _STRUCT_H
#define _STRUCT_H
#include <stdio.h>
#include <stdlib.h>

typedef struct _ronda{
    int coluna;
    int linha;
    char modo;
    int numAtrac;
}ronda;

typedef struct node
{
    VERTICE vertex;
    struct node* next;
}NO;

typedef struct Graph{
    int numVertices;
    NO** adjLists;
}GRAFO;

/*coordenadas e valor de cada vertice*/

typedef struct _vertice{
    int x_vert;
    int y_vert;
    int peso;
    struct _vertice* next;
}VERTICE;


void matAlloc(ronda *lp, int *colunas,int *linhas);

void criaNovoNo (ronda** lp);

GRAFO* createGraph(int vertices);

VERTICE* createVertice(int x, int y, int peso);

void addEdge(GRAFO* graph, int srcx, int srcy, int destx, int desty, int pesosrc, int pesodest);

/*void printGraph(GRAFO* graph);*/


#endif
