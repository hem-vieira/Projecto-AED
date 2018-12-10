#ifndef _ACERVO_H
#define _ACERVO_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "oper.h"

typedef struct _data{
    int x;
    int y;
    int custo;          /*prioridade */
}Data;



struct _heap{ 
    int n_elements; /* Numero elementos do acervo */
    int size;  /*tamanho máximo*/
    int linhas;
    int colunas;
    Data *heapdata; /*tabela de Items*/
};

typedef struct _heap heap;

heap *NewHeap(int linhas, int colunas);

void FixUp(heap * h, int k);

void FixDown(heap * h, int k);

int Insert(heap * h, int pos_x, int pos_y);

void changePrio(heap *h, int k, int novocusto);

void RemoveMax(heap * h);

int GetTopx(heap * h);

int GetTopy(heap * h);

int GetTopcusto(heap *h);

int findIndex(heap *h, int x, int y);

int contaPassos(int ***st, int **wt, int xf, int yf, int xi, int yi, int **mapa);

void impressHelp(int ***st, int **wt, int xf, int yf, int xi, int yi, int **mapa, int i, impressao* imp);

void printCaminho(FILE *fp, impressao *imp, int passos);

void Dijkstra(heap *h, int** mapa, int xi, int yi, int xf, int yf, int*** st, int** wt, int *passos, int *erro);

int***  aloca3D(ronda* lp);

void freeThemAll(ronda* lp, int *x, int *y, int ***st, int **wt, heap* acervo, impressao* imp);

#endif