/******************************************************************************
 *
 * File Name: main.c
 * 2018        AED
 * Authors:    Henrique Vieira and José Malaquias
 * Last modified: 14/11/2018
 * Revision:  
 *
 * COMMENTS
 *		Main program
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiro.h"
#include "struct.h" 
#include "oper.h"


int main(int argc, char *argv[]) {
    char *nameFIn, *nameFOut;
   // char temp[100];
    FILE *fpIn ,*fpOut ;
    fpIn = NULL;
    fpOut = NULL;
    ronda* lp;
    int j = 0;
    int i = 0;
    int x0, y0;
    int error_flag;
    int custo = 0, validade = -1;
    int *x, *y;
   /* int coord[2]={0};*/
    nameFIn = argv[1];
    if (argc != 2){
        exit(0);
    }
    nameFOut = (char*)malloc(strlen(nameFIn)+strlen(".walks")+1);  
    if(nameFOut == NULL){
        exit (0);
    }

    while (nameFIn[j] != '.'){
    j++;
    }

    strncpy (nameFOut,  nameFIn, j);
    nameFOut[j] = 0;
    strcat(nameFOut,".walks");
    
    /*  Open input file */
    fpIn = fopen(nameFIn, "r");
    if (fpIn == NULL){
        exit(0);
    }
    /*  Open output file */
    fpOut = fopen(nameFOut, "w");
    if (fpOut == NULL){
        exit(0);
    }
/*Ciclo do programa*/
while (!feof(fpIn)){

    /*Inicialização da estrutura*/
     criaNovoNo(&lp);
    i = 0;
    x0 = 0;
    y0 = 0;
    x = NULL;
    y = NULL;
    custo = 0;
    validade = -1;
    int erro = 0;
    error_flag = 0;
    readFileHeader(fpIn, &(lp->linha), &(lp->coluna), &(lp->modo), &(lp->numAtrac));
    x = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
    y = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
    readFile(fpIn, &x0, &y0, x, y, (lp->numAtrac));
    int **mapa;
    mapa = alocMapa(lp->linha, lp->coluna);
    
    for (j = 0; j<(lp->linha);j++){
        for (i = 0; i<(lp->coluna);i++){            
            erro = fscanf(fpIn, "%d ", &mapa[j][i]);
            if(erro!=1){
                exit(0);
            }
        }
                        
    }
   /* 
    for (j = 0; j<(lp->linha);j++){
        for (i = 0; i<(lp->coluna);i++){
            printf("%d  ", mapa[j][i]);
        }
        printf("\n");
            
    }
*/
    if ((lp->modo != 'A' ) && (lp->modo != 'B')){
        fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
        error_flag = 1;

    }

    if(error_flag != 1){
        if(((lp->modo) == 'B') && ((lp->numAtrac)<2)){
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
                    error_flag = 1;


        }
    }
    if(error_flag != 1){
        if(((lp->modo) == 'A') && ((lp->numAtrac)!=2)){
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
                    error_flag = 1;
        }  
    }

    int breakerr = 0;

    if(error_flag != 1){
        int pos_err;
        for (i = 0; i < (lp->numAtrac); i++){
            pos_err = checklocations(x[i], y[i], (lp->linha), (lp->coluna), mapa);
            if (pos_err == 1){
                breakerr = 1;
               // printf("Erro 6\n");
                fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);

            }
            if(breakerr == 1){
                error_flag = 1;
                break;
            }
        }
    }

        if(error_flag != 1){
            int jmp_err;
            for (i = 0; i < ((lp->numAtrac)-1); i++){
                jmp_err = check_knight_jump(x[i], y[i], x[i+1], y[i+1]);
                if (jmp_err == 1){
                    breakerr = 1;
                  //  printf("Erro 7\n");
                    fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
                }
                if(breakerr == 1){
                    error_flag = 1;
                    break;
                }
            }
        }


    if(error_flag != 1 ){
        if ((lp->modo == 'A')){
                move_next_stepA(mapa, &x0, &y0, &custo, (lp->linha), (lp->coluna));
                if(custo!=0)
                     validade = 1;
                 else 
                    validade = -1;
        }
        else if(lp->modo == 'B'){

            for(i=1; i<=((lp->numAtrac) - 1); i++)
            {
                move_next_stepB(mapa, &x[i], &y[i], &custo);
                validade = 1;
        
            }   
        }
        
        fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
    }

/* -- FREE ANY MEMORY YOU HAVE ALLOCATED -- */
   
        for (i = 0; i < (lp->linha); i++){
        int* current = mapa[i];
        free(current);
        }
        free(mapa);
        free(lp);
        free(x);
        free(y);

}/*Fim do ciclo do programa*/

/* -- FREE SOME MORE MEMORY YOU HAVE ALLOCATED -- */
    free(nameFOut);

/* -- CLOSE ALL OPENED FILES -- */
    fclose(fpIn);
    fclose(fpOut);


    exit(0);
}