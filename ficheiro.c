#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiro.h"
#include "struct.h"
#include "oper.h"

/* Garante que foi feita a leitura de 4 valores na primeira linha do ficheiro de entrada	*/

void readFileHeader(FILE *fp, int *linhas, int *colunas, char *modo, int *nAtrac){

    if(fscanf(fp, "%d %d %c %d", linhas, colunas, modo, nAtrac) != 4){
        exit(0);
    }
}

/* Garante que foi feita a leitura de 2 valores para nAtrac linhas*/

void readFile(FILE *fp, int *x0, int *y0, int *x, int *y, int nAtrac){
    int i = 0;
    while (i != nAtrac){
        if(fscanf(fp, "%d %d", &x[i], &y[i]) != 2){
            exit(0);
        }

        *x0 = x[0];
        *y0 = y[0];

        i++;
    }

}

/*Aloca o mapa*/

int **alocMapa(int linhas, int colunas){
    int **matriz;
    int i = 0;

    /*Alocação da memória para a matriz*/

    matriz = (int**)malloc((linhas)*sizeof(int*));
    if( matriz == NULL ){
        exit(0);
    }
    
    for (i=0; i< (linhas); i++){
        matriz[i] = (int*)malloc((colunas)*sizeof(int));
        if( matriz[i] == NULL ){
            exit(0);
        }
    }

   return matriz;
}

void freeMapa(int ** matriz, ronda* lp){
    int i = 0;
    for (i = 0; i < (lp->linha); i++){
        int* current = matriz[i];
        free(current);
        }
    free(matriz);
}


