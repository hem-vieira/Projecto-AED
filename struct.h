#ifndef _STRUCT_H
#define _STRUCT_H
#include <stdio.h>
#include <stdlib.h>

typedef struct _ronda{
    int coluna;
    int linha;
    char modo;
    int numAtrac;
    /*int **mat;*/
    /*struct _ronda *next;*/
}ronda;
void matAlloc(ronda *lp, int *colunas,int *linhas);
/*d criaNovoNo (ronda** lp,int *linhas,int *colunas,char *modo, int *nAtrac);*/
void criaNovoNo (ronda** lp);
#endif
