#ifndef _ACERVO_H
#define _ACERVO_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "oper.h"

typedef struct _heap heap;

heap *NewHeap(int linhas, int colunas);

void FixUp(heap * h, int k);

void FixDown(heap * h, int k);

int Insert(heap * h, int pos_x, int pos_y);

void changePrio(heap *h, int k, int novocusto);

void RemoveMax(heap * h);

int GetTopx(heap * h);

int GetTopy(heap * h);

void Dijkstra(heap *h, int** mapa, int xi, int yi, int xf, int yf, int*** st, int** wt);

#endif