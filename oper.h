#ifndef _OPER_H
#define _OPER_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "ficheiro.h"

//int fillgraph(int** matriz,int x,int y, int xmax, int ymax);
//int find_next_step(int** matriz,int x,int y, int xmax, int ymax);
void move_next_stepA(int** matriz, int *x, int *y, int *custo, int linha, int coluna);
void move_next_stepB(int** matriz, int *x, int *y, int *custo);   
int salto_1(int x, int y);
int salto_2(int x, int y, int xmax);
int salto_3(int x, int y, int xmax);
int salto_4(int x, int y, int xmax,int ymax);
int salto_5(int x, int y, int xmax,int ymax);
int salto_6(int x, int y, int ymax);
int salto_7(int x, int y, int ymax);
int salto_8(int x, int y);
int checklocations(int x, int y, int nlinhas, int ncolunas, int **mapa);
int check_knight_jump(int x0, int y0, int x, int y);

void encontraAdj(int** matriz, int x, int y, int xmax, int ymax, int*** adj);

#endif