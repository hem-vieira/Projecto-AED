#ifndef _FICHEIRO_H
#define _FICHEIRO_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "oper.h"
void iniciaVariaveis(int* i, int* x0, int* y0, int* custo, int* custoFinal, int* erro, int* error_flag, int* n_passos);
void readFileHeader(FILE *fp, int *linhas, int *colunas, char *modo, int *nAtrac);
void readFile(FILE *fp, int *x0, int *y0, int *x, int *y, int nAtrac);
void readMatrix(ronda* lp, int**mapa, FILE* fp);
int **alocMapa( int linhas, int colunas);
void freeMapa(int ** matriz, ronda* lp);
impressao* alocaImpress(int passo, int** mapa, int***st);
void fillImpress(int x, int y, int **mapa, int passo, impressao* imp);
int headerVerifier(ronda* lp, FILE* fp, int *custoFinal, int *n_passos);




#endif