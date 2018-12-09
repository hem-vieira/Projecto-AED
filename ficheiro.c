#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiro.h"
#include "struct.h"
#include "oper.h"
void iniciaVariaveis(int* i, int* x0, int* y0, int* custo, int* custoFinal, int* erro, int* error_flag, int* n_passos){
    *i = 0;
    *x0 = 0;
    *y0 = 0;
    *custo = 0;
    *custoFinal = 0;
    *erro = 0;
    *error_flag = 0;
    *n_passos = 0;
}

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

void readMatrix(ronda* lp, int**mapa, FILE* fp){
    int i =0, j = 0;
    int erro;
    for(i = 0; i < lp->linha ; i++){
        for(j = 0; j < lp->coluna; j++){
            erro = fscanf(fp, "%d", &mapa[i][j]);
            if(erro != 1){
                exit(0);
            }
        }
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


impressao* alocaImpress(int passo, int** mapa, int***st){
    impressao* imp;
    imp = (impressao*)malloc(sizeof(impressao) * passo);

    if(imp == NULL){
        exit(0);
    }

    return imp;
}


void fillImpress(int x, int y, int **mapa, int i, impressao* imp){   
        imp[i].x = x;
        imp[i].y = y;
        imp[i].custo = mapa[x][y];
}


void freeMapa(int ** matriz, ronda* lp){
    int i = 0;
    for (i = 0; i < (lp->linha); i++){
        int* current = matriz[i];
        free(current);
        }
    free(matriz);
}

int headerVerifier(ronda* lp, FILE* fp, int *custoFinal, int *n_passos){
    int verifier = 0;

     /* Confirma se o modo escolhido é válido   */   
    if ((lp->modo != 'A' ) && (lp->modo != 'B') && (lp->modo != 'C')){
        *custoFinal = -1;
        *n_passos = 0;
        verifier = 1;
        fprintf(fp, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, *custoFinal, *n_passos);
        //error_flag = 1;
    }
    /*    Confirma se existem duas ou mais atrações para o modo B    */  
    if(verifier == 0){
        if(((lp->modo) == 'B') && ((lp->numAtrac)<2)){
            *custoFinal = -1;
            *n_passos = 0;
            verifier = 1;
            fprintf(fp, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, *custoFinal, *n_passos);
        }
    }
    /*    Confirma se existem apenas duas atrações para o modo A    */ 
    if(verifier == 0){
        if(((lp->modo) == 'A') && ((lp->numAtrac)!=2)){
            *custoFinal = -1;
            *n_passos = 0;
            verifier = 1;
            fprintf(fp, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, *custoFinal, *n_passos); 
        }
    }
    /*    Confirma se existem duas ou mais atrações para o modo C    */ 
    if(verifier == 0){
        if(((lp->modo) == 'C') && ((lp->numAtrac)<2)){
            *custoFinal = -1;
            *n_passos = 0;
            verifier = 1;
            fprintf(fp, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, *custoFinal, *n_passos);        
        }
    }

    return verifier;
}








