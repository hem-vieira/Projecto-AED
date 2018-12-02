#ifndef _FICHEIRO_H
#define _FICHEIRO_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "oper.h"
void readFileHeader(FILE *fp, int *linhas, int *colunas, char *modo, int *nAtrac);
void readFile(FILE *fp, int *x0, int *y0, int *x, int *y, int nAtrac);
int **alocMapa( int linhas, int colunas);


#endif