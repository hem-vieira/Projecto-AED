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
#include "acervo.h"

int main(int argc, char *argv[]) {
    /*  Definição das variáveis utilizadas    */

    char *nameFIn, *nameFOut;
    FILE *fpIn ,*fpOut ;
    fpIn = NULL;
    fpOut = NULL;
    ronda* lp;
    impressao* lol;
    heap* acervo;
    int*** st;
    int **wt;
    int j = 0;
    int i;
    int x0, y0;
    int error_flag; /* variável usada para impedir que o programa continue caso haja um erro num dos testes de erro */
    int erro;       /* variável usada para garantir que se obtem todos os valores no mapa */
    int custo;
    int validade;
    int *x, *y;
    int passos = 0;


    /*  Confirma o número de argumentos */

    nameFIn = argv[1];
    if (argc != 2){
        exit(0);
    }

    /*  Aloca memória para o nome do ficheiro de saída e substitui a terminação .cities por .walks  */

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
    
    /*  Abre o ficheiro de entrada */

    fpIn = fopen(nameFIn, "r");
    if (fpIn == NULL){
        exit(0);
    }
    /*  Abre o ficheiro de saída */

    fpOut = fopen(nameFOut, "w");
    if (fpOut == NULL){
        exit(0);
    }
    /*  Ciclo do programa   */

    while (!feof(fpIn)){

    /*Inicialização da estrutura*/
     criaNovoNo(&lp);


    i = 0;
    x0 = 0;
    y0 = 0;
    x = NULL;
    y = NULL;
    wt = NULL;
    st = NULL;
    custo = 0;
    validade = -1;
    erro = 0;
    error_flag = 0;

/*  Lê a primeira linha do ficheiro de entrada e obtêm a dimensão do mapa (linha * coluna), o modo e o número de atrações   */

    readFileHeader(fpIn, &(lp->linha), &(lp->coluna), &(lp->modo), &(lp->numAtrac));

    /* TESTES DE ERROS*/
 
 /* Confirma se o modo escolhido é válido   */   

    if ((lp->modo != 'A' ) && (lp->modo != 'B') && (lp->modo != 'C')){
        fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
        error_flag = 1;

    }

  /*    Confirma se existem duas ou mais atrações para o modo B    */  

    if(error_flag != 1){
        if(((lp->modo) == 'B') && ((lp->numAtrac)<2)){
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
                    error_flag = 1;


        }
    }

     /*    Confirma se existem apenas duas atrações para o modo A    */ 

    if(error_flag != 1){
        if(((lp->modo) == 'A') && ((lp->numAtrac)!=2)){
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
                    error_flag = 1;
        }  
    }

     /*    Confirma se existem duas ou mais atrações para o modo C    */ 

    if(error_flag != 1){
        if(((lp->modo) == 'C') && ((lp->numAtrac)<2)){
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, validade, custo);
                    error_flag = 1;


        }
    }

/*FIM DE TESTES DE ERROS*/


/*Aloca o espaço para o acervo*/

    acervo = NewHeap(lp->linha , lp->coluna);

/*Aloca vetores necessários ao programa*/

st = (int***)malloc(sizeof(int**) * lp->linha);
for(i = 0; i < lp->linha; i++){

	st[i] = (int**)malloc(sizeof(int*) * lp->coluna);
	
    for(j = 0; j < lp->coluna; j++){

        st[i][j] = (int*)malloc(sizeof(int) * 2);
    }
}



/**/
    wt = (int**)malloc((lp->linha)*sizeof(int*));
    if( wt == NULL){
        exit(0);
    }
    for(i = 0; i < lp->linha; i++){
        wt[i] = (int*)malloc(lp->coluna*sizeof(int));
        if (wt[i] == NULL){
            exit(0);
        }
    }


/*  Aloca os vetores de acordo com o número de atrações */

    x = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
    y = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);

/*  Lê e guarda as respetivas coordenadas de cada posição nos respetivos vetores( x -> linhas, y-> colunas)   */

    readFile(fpIn, &x0, &y0, x, y, (lp->numAtrac));

/* Aloca o mapa com dimensão linha*coluna e guarda os valores de cada posição do mapa*/ 

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

 
/*Dependendo do modo escolhido, chama-se a função responsável por verificar se o problema é válido e imprime-se os resultados para o ficheiro de saída*/        

    if(error_flag != 1 ){

        if ((lp->modo == 'A')){

            Dijkstra(acervo, mapa, x[0], y[0], x[1], y[1], st, wt, &passos);

                if(wt[x[1]][y[1]] != 0)

                     custo = wt[x[1]][y[1]];
                 else 
                    custo = -1;
        }
        else if(lp->modo == 'B'){

            for(i=1; i<=((lp->numAtrac) - 1); i++)
            {
                Dijkstra(acervo, mapa, x[0], y[0], x[1], y[1], st, wt, &passos);


                if(wt[x[1]][y[1]] != 0)

                     custo = wt[x[1]][y[1]];
                 else 
                    custo = -1;
            }   
        }

        else if(lp->modo == 'C'){

        }
        
        fprintf(fpOut, "%d %d %c %d %d %d\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custo, passos);

         lol = alocaImpress(passos, mapa, st);

         impressHelp(st, wt, x[1], y[1], x[0], y[0], mapa, passos, lol);
         printCaminho(fpOut, lol, passos);

    }

/* Libertação de memórias */

        freeMapa(mapa, lp);
        freeThemAll(lp, x, y, st, wt, acervo);

}   /*Fim do ciclo do programa*/

/* Libertação de memória alocada para o ficheiro de saída */

    free(nameFOut);

/* Fecho dos ficheiros abertos e saída do programa */

    fclose(fpIn);
    fclose(fpOut);


    exit(0);
}