#include <stdlib.h>
#include <stdio.h>
#include "acervo.h"
#define MAX_VALUE 1000
typedef struct _data{
    int x;
    int y;
    int custo; /*prioridade */
}Data;

/* O acervo é representado por uma estrutura*/
struct _heap { 
    int n_elements; /* Numero elementos do acervo */
    int size;  /*tamanho máximo*/
    int linhas;
    int colunas;
    Data *heapdata; /*tabela de Items*/
};


/*cria o cervo e guarda todos os dados nos respetivos valores previamente definidos*/
heap *NewHeap(int linhas, int colunas)
{
  heap *h;

  h = (heap *) malloc(sizeof(heap));
  if (h ==  NULL) {
    exit(0);
  }

  h->n_elements = 0;
  h->size = linhas * colunas;
  h->linhas = linhas;
  h->colunas = colunas;
  h->heapdata = (Data *) malloc((linhas*colunas) * sizeof(Data));
  if (h->heapdata == NULL ) {
    exit(0);
  }

  return (h);
}




void FixUp(heap * h, int k)
{
    int t;
  while ((k > 0) &&  h->heapdata[(k-1)/2].custo < h->heapdata[k].custo){
    t = h->heapdata[k].custo;
    (h->heapdata)[k].custo = (h->heapdata)[(k - 1) / 2].custo;
    (h->heapdata)[(k - 1) / 2].custo = t;

    k = (k - 1) / 2;
  }

  return;
}



void FixDown(heap * h, int k)
{
  int j;
  int t;

  while ((2 * k + 1) < h->n_elements) {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) && (h->heapdata[j].custo < h->heapdata[j + 1].custo)){
      j++;
    }
    if (!((h->heapdata[k].custo) < (h->heapdata[j].custo))){
      /* Elements are in correct order. */
      break;
    }
    

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k].custo;
    (h->heapdata)[k].custo = (h->heapdata)[j].custo;
    (h->heapdata)[j].custo = t;
    k = j;
  }

  return;
}

/* Description: Adiciona elemento no fim do acervo e faz a função fixup*/

int Insert(heap * h, int pos_x, int pos_y)
{
  if (h->n_elements == h->size) {
    return 0;
  }
  /* Adiciona elemento na primeira posição disponível no acervo */
  h->heapdata[h->n_elements].x = pos_x;
  h->heapdata[h->n_elements].y = pos_y;
  h->heapdata[h->n_elements].custo = MAX_VALUE;
  h->n_elements++;
  FixUp(h, h->n_elements - 1);

  return 1;
} 

void changePrio(heap *h, int k, int novocusto)
{
  if( novocusto < h->heapdata[k].custo){
    free(h->heapdata[k].custo);
    h->heapdata[k].custo = novocusto;
    FixDown(h, k);

  }
  else{
    free(h->heapdata[k].custo);
    h->heapdata[k].custo = novocusto;
    FixUp(h, k);
  }

  return;
}

void Dijkstra(heap *h, int** mapa, int xi, int yi, int xf, int yf, int*** st, int** wt, int** adj ){
  
  int vx, vy, wx, wy;
  int i;
  
  

  for( vx = 0;  vx < h->linhas ; vx++){
    for( vy = 0;  vy < h->colunas ; vy++){
    st[vx][vy][0] = -1;                         //0 equivale ao x, 1 equivale ao y
    st[vx][vy][1] = -1;

    wt[vx][vy] = MAX_VALUE;

    if(Insert(h, vx, vy) == 0)
    exit(0);

    }
  }

  wt[xi][yi] = 0;
  changePrio(h, (yi * (h->colunas) + xi +1), wt[xi][yi]);
  vx =xi;
  vy =yi;
  
  h->n_elements--;

  while (h->n_elements != 0){

    if(wt[vx][vy] != MAX_VALUE){

      adj = encontraAdj(mapa, vx, vy, h->linhas, h->colunas);

      for(i= 0; adj[i][0] !=-1; i++){

        wx = adj[i][0];
        wy = adj[i][1];

        if(wt[wx][wy] > wt[vx][vy] + mapa[wx][wy]){

          wt[wx][wy] = wt[vx][vy] + mapa[wx][wy];

          changePrio(h, (wy * (h->colunas) + wx +1), wt[wx][wy]);

          h->n_elements--;
          st[wx][wy][0] = vx;
          st[wx][wy][1] = vy;

          }
        }
      }
    }
while(xf!= xi && yf!= yi){
  printf("Destino: x:%d y:%d e custo = %d, Vértice predecessor: x:%d y:%d", xf, yf, wt[xf][yf], st[xf][yf][0], st[xf][yf][1]);
  xf = st[xf][yf][0];
  yf = st[xf][yf][1];
  }
}








/*Adiciona o elemento no fim do acervo mas não faz fixup */
/*
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
*/

/*
void Modify(Heap * h, int index, Item newvalue)
{
  if (index > h->n_elements - 1) {
    printf("Index out of range (index = %d) !\n", index);
    return;
  }*/
  /* Compares new value  with the value of the element to substitute */
  //if ((h->less) (newvalue, h->heapdata[index])) {
    /* If smaller, reconstruct heap with function FixDown */
    /*
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixDown(h, index);
  }
  else {*/
    /* If greater, reconstruct heap using the function FixUp */
    /*
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixUp(h, index);
  }

  return;
}
*/
/*
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
*/
/*
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
*/