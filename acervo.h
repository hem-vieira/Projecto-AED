/*#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "operAcervo.h"*/
#include "Item.h"

typedef struct _heap Heap;

Heap *NewHeap(int tamanho, int (*less) (Item, Item));

void FreeHeap(Heap * h);

int Insert(Heap * h, Item element);

int Direct_Insert(Heap * h, Item element);

void Modify(Heap * h, int indice, Item newvalue);

Item RemoveMax(Heap * h);

Item GetIndex(Heap * h, int index);

void CleanHeap(Heap * h);

int VerifyHeap(Heap * h);

void HeapSort(Heap * h);

void Heapify(Heap * h);
