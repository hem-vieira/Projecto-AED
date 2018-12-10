#ifndef _OPER_H
#define _OPER_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "ficheiro.h"


void encontraAdj(int** matriz, int x, int y, int xmax, int ymax, int adj[8][2]);
int checklocations(int x, int y, int nlinhas, int ncolunas, int** mapa);

#endif