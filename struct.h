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


typedef struct _pontos{
    int x;
    int y;
    int custo;
}PONTO;

typedef struct _etapa{
    int n_passos;
    PONTO* ponto;
}ETAPA;

void matAlloc(ronda *lp, int *colunas,int *linhas);

void criaNovoNo (ronda** lp);
ETAPA* alocaEtapa(int n_atrac);
PONTO* alocaPonto(int n_passos);




#endif
