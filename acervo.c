#include <stdlib.h>
#include <stdio.h>
#include "acervo.h"
#include "operAcervo.h"


/* O acervo é representado por uma estrutura*/

struct _heap { 
    int (*less) (Item, Item);
    int n_elements; /* Numero elementos do acervo */
    int size;  /*tamanho máximo*/
    Item *heapdata; /*tabela de Items*/
};

void FixUp(Heap * h, int k)
{
  Item t;
  while ((k > 0) && (h->less) ((h->heapdata)[(k - 1) / 2], (h->heapdata)[k])) {

    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;

    k = (k - 1) / 2;
  }

  return;
}

void FixDown(Heap * h, int k)
{
  int j;
  Item t;

  while ((2 * k + 1) < h->n_elements) {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) &&
        (h->less) (h->heapdata[j], h->heapdata[j + 1])) {
      /* second offspring is greater */
      j++;
    }
    if (!(h->less) (h->heapdata[k], h->heapdata[j])) {
      /* Elements are in correct order. */
      break;
    }
    

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;
  }

  return;
}

/*cria o cervo e guarda todos os dados nos respetivos valores previamente definidos*/
Heap *NewHeap(int size, int (*less) (Item, Item))
{
  Heap *h;

  h = (Heap *) malloc(sizeof(Heap));
  if (h == ((Heap *) NULL)) {
    fprintf(stderr, "Error in malloc of heap\n");
    exit(0);
  }

  h->n_elements = 0;
  h->less = less;
  h->size = size;
  h->heapdata = (Item *) malloc(size * sizeof(Item));
  if (h->heapdata == ((Item *) NULL)) {
    fprintf(stderr, "Error in malloc of heap data\n");
    exit(0);
  }

  return (h);
}

/* Description: Adiciona elemento no fim do acervo e faz a função fixup*/

int Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    printf("Heap full (size = %d) !\n", h->size);
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;
  FixUp(h, h->n_elements - 1);

  return 1;
}

/*Adiciona o elemento no fim do acervo mas não faz fixup */
int Direct_Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    printf("Heap full (size = %d) !\n", h->size);
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;


  return 1;
}


void Modify(Heap * h, int index, Item newvalue)
{
  if (index > h->n_elements - 1) {
    printf("Index out of range (index = %d) !\n", index);
    return;
  }
  /* Compares new value  with the value of the element to substitute */
  if ((h->less) (newvalue, h->heapdata[index])) {
    /* If smaller, reconstruct heap with function FixDown */
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixDown(h, index);
  }
  else {
    /* If greater, reconstruct heap using the function FixUp */
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixUp(h, index);
  }

  return;
}

Item RemoveMax(Heap * h)
{
  Item t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    free(h->heapdata[h->n_elements - 1]);
    h->n_elements--;
    FixDown(h, 0);
    return t;
  }

  return NULL;
}


Item GetIndex(Heap * h, int index)
{
  Item t;

  if (index > h->n_elements - 1) {
    printf("Index out of range (index = %d) !\n", index);
    return NULL;
  }

  t = (h->heapdata)[index];
  return t;
}




