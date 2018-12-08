#include <stdlib.h>
#include <stdio.h>
#include "acervo.h"
#include "oper.h"
#include "struct.h"
#include "ficheiro.h"
#include "limits.h"
#define MAX_VALUE (INT_MAX)/2

/*PASSAR ISTO PARA STRUCT.C*/

typedef struct _data{
    int x;
    int y;
    int custo;          /*prioridade */
}Data;

/* O acervo é representado por uma estrutura*/
struct _heap{ 
    int n_elements; /* Numero elementos do acervo */
    int size;  /*tamanho máximo*/
    int linhas;
    int colunas;
    Data *heapdata; /*tabela de Items*/
};


/*cria o acervo e guarda todos os dados nos respetivos valores previamente definidos*/

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

  while ((k > 0) &&  h->heapdata[(k-1)/2].custo > h->heapdata[k].custo){

    t = h->heapdata[k].custo;
    (h->heapdata)[k].custo = (h->heapdata)[(k - 1) / 2].custo;
    (h->heapdata)[(k - 1) / 2].custo = t;

    t = (h->heapdata)[k].x;
    (h->heapdata)[k].x = (h->heapdata)[(k-1) / 2].x;
    (h->heapdata)[(k-1) / 2].x = t;

    t = (h->heapdata)[k].y;
    (h->heapdata)[k].y = (h->heapdata)[(k-1) / 2].y;
    (h->heapdata)[(k-1) / 2].y = t;

    k = (k - 1) / 2;
  }

  return;
}



void FixDown(heap * h, int k)
{

  int j;
  int t;

  while ((2 * k) < h->n_elements-1) {

    j = 2 * k + 1;

    if ((j < h->n_elements-1) && (h->heapdata[j].custo > h->heapdata[j + 1].custo)){
      j++;
    }

    if ((h->heapdata[k].custo) < (h->heapdata[j].custo)){
      break;
    }

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */

    t = (h->heapdata)[k].custo;
    (h->heapdata)[k].custo = (h->heapdata)[j].custo;
    (h->heapdata)[j].custo = t;

    t = (h->heapdata)[k].x;
    (h->heapdata)[k].x = (h->heapdata)[j].x;
    (h->heapdata)[j].x = t;

    t = (h->heapdata)[k].y;
    (h->heapdata)[k].y = (h->heapdata)[j].y;
    (h->heapdata)[j].y = t;

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
    h->heapdata[k].custo = novocusto;
    FixUp(h, k);

  }
  else{
    h->heapdata[k].custo = novocusto;
    FixDown(h, k);
  }
  return;
}

void RemoveMax(heap * h)
{
  int t;

  if (h->n_elements > 0) {

    t = (h->heapdata)[0].custo;
    (h->heapdata)[0].custo = (h->heapdata)[h->n_elements - 1].custo;
    (h->heapdata)[h->n_elements - 1].custo = t;

    t = (h->heapdata)[0].x;
    (h->heapdata)[0].x = (h->heapdata)[h->n_elements - 1].x;
    (h->heapdata)[h->n_elements - 1].x = t;

    t = (h->heapdata)[0].y;
    (h->heapdata)[0].y = (h->heapdata)[h->n_elements - 1].y;
    (h->heapdata)[h->n_elements - 1].y = t;

    h->n_elements--;

    FixDown(h, 0);

  }

  return;
}

int GetTopx(heap * h)
{
  int t;

  t = (h->heapdata)[0].x;

  return t;
}

int GetTopy(heap * h)
{
  int t;

  t = (h->heapdata)[0].y;

  return t;
}

int GetTopcusto(heap *h)
{
	int t;

	t= (h->heapdata)[0].custo;

	return t;
}

void printqueue(heap *h){
for(int i=0; i< h->n_elements; i++){
	printf("custo = %d\n", h->heapdata[i].custo);
}

}

int findIndex(heap *h, int x, int y)
{
	for(int i=0; i<h->n_elements; i++)
	{
		if(x==h->heapdata[i].x && y==h->heapdata[i].y)
			return i;
	}
	return -1;
}

int contaPassos(int ***st, int **wt, int xf, int yf, int xi, int yi, int **mapa){

	int aux1 = st[xf][yf][0];
	int aux2 = st[xf][yf][1];
	int passo = 0;
	passo++;

	while(aux1 != xi || aux2 != yi) 
	{
		int k=aux1;
		int q=aux2;
		aux1 = st[aux1][aux2][0];
		aux2 = st[k][q][1];
		passo++;
	}
	return passo;
}

void impressHelp(int ***st, int **wt, int xf, int yf, int xi, int yi, int **mapa, int passo, impressao* imp){

	int aux1 = xf;
	int aux2 = yf;
	int i= 0;

	while(aux1 != xi || aux2 != yi) 
	{
		fillImpress(aux1, aux2, mapa, i, imp);
		int k=aux1;
		int q=aux2;
		aux1 = st[aux1][aux2][0];
		aux2 = st[k][q][1];
		i++;

	}
}


void printCaminho(FILE *fp, impressao *imp, int passos){

	int loop;

	for(loop = passos-1; loop >= 0; loop--)
		fprintf(fp,"%d %d %d\n", imp[loop].x, imp[loop].y, imp[loop].custo);
}


void Dijkstra(heap *h, int** mapa, int xi, int yi, int xf, int yf, int*** st, int** wt, int *passos){

  int vx, vy, wx, wy, weight;
  int i;
  int adj[8][2];
  
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

  changePrio(h, 0, wt[xi][yi]);
 

/******/
  while (h->n_elements != 0){

	//printqueue(h);

    vx = GetTopx(h);
    vy = GetTopy(h);
	weight = GetTopcusto(h);

    if(vx == xf && vy == yf){
    	*passos = contaPassos(st, wt, xf, yf, xi, yi, mapa);
    	break;
}

    RemoveMax(h);

    if(weight != MAX_VALUE){

    encontraAdj(mapa, vx, vy, h->linhas, h->colunas, adj);

      for(i= 0; i<8; i++){

        if(adj[i][0] !=-1 && wt[adj[i][0]][adj[i][1]] == MAX_VALUE){

          wx = adj[i][0];
          wy = adj[i][1];

          if(wt[wx][wy] > weight + mapa[wx][wy]){

             wt[wx][wy] = weight + mapa[wx][wy];

			int index = findIndex(h, wx, wy);

			if(index == -1)
				break;

              changePrio(h, index, wt[wx][wy]);

              st[wx][wy][0] = vx;
              st[wx][wy][1] = vy;



          }

        }

      }




    }

  }

}


void freeThemAll(ronda* lp, int *x, int *y, int ***st, int **wt, heap* acervo, impressao* imp){
  /*libertação de memória do array tridimensional*/
  int i = 0, j = 0;
  for(i=0;i<lp->linha;i++)
        {
            for(j=0;j<lp->coluna ;j++)
        {
            free(st[i][j]);
        }
        free(st[i]);
        }
        free(st);
/*libertação memória array bidimensional */
        for(i=0;i< lp->linha ;i++)
        {
            free(wt[i]);
        }
        free(wt);
  /*Libertação de memória do resto dos parâmetros*/
        free(imp);
        free(acervo->heapdata);
        free(acervo);
        free(lp);
        free(x);
        free(y);

}