/******************************************************************************
 *
 * File Name: main.c
 * 2018        AED
 * Authors:    Henrique Vieira and José Malaquias
 * Last modified: 11/12/2018
 * Revision:  
 *
 * COMMENTS
 *		Main program
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
    int j = 0;
    int i;
    int x0, y0;
    int error_header; /* variável usada para impedir que o programa continue caso haja um erro num dos testes de erro */
    int error_pontos = 0;
    int erro;       /* variável usada para garantir que se obtem todos os valores no mapa */
    int custoFinal;
    int *x, *y;
    int passos = 0;
    int **mapa;
    int*** st;
    int **wt;
    
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

    iniciaVariaveis(&i, &x0, &y0, &custoFinal, &erro, &error_header, &error_pontos, &passos);
    wt = NULL;
    st = NULL;
    mapa = NULL;
    acervo = NULL;
    x = NULL;
    y = NULL;
    lol = NULL;
    lp = NULL;
/*Inicialização da estrutura*/
    criaNovoNo(&lp);
/*  Lê a primeira linha do ficheiro de entrada e obtêm a dimensão do mapa (linha * coluna), o modo e o número de atrações   */
    readFileHeader(fpIn, &(lp->linha), &(lp->coluna), &(lp->modo), &(lp->numAtrac));
/* TESTES DE ERROS - se error_header== 1 significa que o programa não tem parâmetros adequados */
    error_header = headerVerifier(lp, fpOut, &custoFinal, &passos);
/*  Aloca os vetores de acordo com o número de atrações */
    x = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
    y = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
/* Aloca o mapa com dimensão linha*coluna */ 
    mapa = alocMapa(lp->linha, lp->coluna);  
    
/*  Lê e guarda as respetivas coordenadas de cada posição nos respetivos vetores( x -> linhas, y-> colunas)   */
    readFile(fpIn, &x0, &y0, x, y, (lp->numAtrac));
/* Guarda os valores de cada posição do mapa*/
    readMatrix(lp, mapa, fpIn);
    printf("Valor de error_header (%d) deve ser 0\n", error_header );
printf("Valor de error_pontos (%d) deve ser 0\n", error_pontos );

if (error_header == 0){
    /*VERIFICAÇÃO DE ERROS NOS PONTOS DE PASSAGEM*/
    if(lp->modo == 'A'){
        if ((x[0] == x[1]) && (y[0] == y[1])){
            error_pontos = 1;
            printf("Valor de error_pontos (%d) deve ser 1\n", error_pontos );
            custoFinal = 0;
            passos = 0;
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custoFinal, passos);
        }
        else
            error_pontos = 0;
    }
}

/*Só aloca memória do acervo e arrays se não tiver havido nenhum problema anteriormente*/
if((error_header != 1) && (error_pontos != 1)){
    /*Aloca o espaço para o acervo*/
    acervo = NewHeap(lp->linha , lp->coluna);
    /*Aloca arrays necessários ao funcionamento do algoritmo*/
    st = aloca3D(lp);
    wt = alocMapa(lp->linha, lp->coluna);
}


/*Dependendo do modo escolhido, chama-se a função responsável por verificar se o problema é válido e imprime-se os resultados para o ficheiro de saída*/        
/*Após efetuada a leitura completa de um problema só se calcula solução se não houver erros */
if((error_header != 1) && (error_pontos != 1)){

        if ((lp->modo == 'A')){

            Dijkstra(acervo, mapa, x[0], y[0], x[1], y[1], st, wt, &passos);

                if(wt[x[1]][y[1]] != 0)

                     custoFinal = wt[x[1]][y[1]];
                 else 
                    custoFinal = -1;
        }
        else if(lp->modo == 'B'){

            for(i=1; i<=((lp->numAtrac) - 1); i++)
            {
                Dijkstra(acervo, mapa, x[0], y[0], x[1], y[1], st, wt, &passos);


                if(wt[x[1]][y[1]] != 0)

                     custoFinal = wt[x[1]][y[1]];
                 else 
                    custoFinal = -1;
            }   
        }

        else if(lp->modo == 'C'){

        }
        
        fprintf(fpOut, "%d %d %c %d %d %d\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custoFinal, passos);
        lol = alocaImpress(passos, mapa, st);
        impressHelp(st, wt, x[1], y[1], x[0], y[0], mapa, passos, lol);
        printCaminho(fpOut, lol, passos);
        
}

printf("p1:\n%d %d %c %d\n", lp->linha, lp->coluna, lp->modo, lp->numAtrac);

    /* Libertação de memórias */

        if((error_header == 1) || (error_pontos == 1)){
            freeMapa(mapa, lp);
            free(y);
            free(x);
            free(lp);
        }
        else{
            freeMapa(mapa, lp);
            freeThemAll(lp, x, y, st, wt, acervo, lol);
        }

}   /*Fim do ciclo do programa*/
    

/* Libertação de memória alocada para o ficheiro de saída */
    free(nameFOut);
/* Fecho dos ficheiros abertos e saída do programa */
    fclose(fpIn);
    fclose(fpOut);
    exit(0);
}