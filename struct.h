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

typedef struct _impressao{
	int x;
	int y;
	int custo;
}impressao;

void matAlloc(ronda *lp, int *colunas,int *linhas);

void criaNovoNo (ronda** lp);

#endif
