#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operAcervo.h"

typedef struct _data{
    int id;
    int custo; /*prioridade */
}Data;

int currID = 0;


int LessNum(Item a, Item b)
{
  Data *pra = (Data*) a;
  Data *prb = (Data*) b;
  int aa, bb;

  aa = pra->custo;
  bb = prb->custo;

  return (aa < bb);
}

void InsertNum(Heap * h, int num_insert)
{
   Data *prc;

   prc = (Data *) malloc(sizeof(Data));
   prc->id = currID;
   prc->custo = num_insert;
   currID++;
   if (Insert(h, (Item) prc) == 0) free(prc);

  return;
}


void DirectInsertNum(Heap * h, int num_Dinsert)
{
   Data *prc;

   prc = (Data *) malloc(sizeof(Data));
   prc->id = currID;
   prc->custo = num_Dinsert;
   currID++;
   if (Direct_Insert(h, (Item) prc) == 0) free(prc);

  return;
}

/* index do elemento a mudar. Nova prioridade */
void ModifyNum(Heap * h, int index, int novovalor)
{
  
  Data *newprc = (Data*) malloc(sizeof(Data)), *oldprc;

  
  oldprc = (Data*) GetIndex(h, index);
  if (oldprc != (Data*)NULL) {
    newprc->id = oldprc->id;
    newprc->custo = novovalor;
    Modify(h, index, (Item) newprc);
  }

  return;
}
/*
void RemoveMaxNum(Heap * h)
{
  RemoveMax(h);

  return;
}
*/