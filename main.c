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
    int error_location = 0;
    int erro;       /* variável usada para garantir que se obtem todos os valores no mapa */
    int erro_adj;
    int custoFinal;
    int passosTotal;
    int *x, *y;
    int passos;
    int **mapa;
    int*** st;
    int **wt;
    ETAPA* etapa;
   /* PONTO* ponto;*/

    
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

    iniciaVariaveis(&i, &x0, &y0, &custoFinal, &erro, &error_header, &error_pontos, &passos, &erro_adj);
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
/*  Aloca os vetores de acordo com o número de atrações */
    x = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
    y = (int*)malloc(((lp->numAtrac)*sizeof(int)) + 1);
/*  Lê e guarda as respetivas coordenadas de cada posição nos respetivos vetores( x -> linhas, y-> colunas)   */
    readFile(fpIn, &x0, &y0, x, y, (lp->numAtrac));
/* Aloca o mapa com dimensão linha*coluna */ 
    mapa = alocMapa(lp->linha, lp->coluna);  
/* Guarda os valores de cada posição do mapa*/
    readMatrix(lp, mapa, fpIn);
    etapa = alocaEtapa(lp->numAtrac);







/* TESTES DE ERROS - se error_header== 1 significa que o programa não tem parâmetros adequados */

    error_header = headerVerifier(lp, fpOut, &custoFinal, &passos);


    if (error_header == 0){

    /*VERIFICAÇÃO DE ERROS NOS PONTOS DE PASSAGEM*/

    if(lp->modo == 'A'){

        if ((x[0] == x[1]) && (y[0] == y[1])){
            error_pontos = 1;
            custoFinal = 0;
            passos = 0;
            fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custoFinal, passos);
        }
        else
            error_pontos = 0;
    }
}

 for (i = 0; i < (lp->numAtrac); i++){
        error_location = checklocations(x[i], y[i], (lp->linha), (lp->coluna), mapa);
        if(error_location == 1)
            break;
    }


/*Só aloca memória do acervo e arrays se não tiver havido nenhum problema anteriormente*/
if((error_header != 1) && (error_pontos != 1) && (error_location != 1)){
    /*Aloca o espaço para o acervo*/
    acervo = NewHeap(lp->linha , lp->coluna);
    /*Aloca arrays necessários ao funcionamento do algoritmo*/
    st = aloca3D(lp);
    wt = alocMapa(lp->linha, lp->coluna);
}


/*Dependendo do modo escolhido, chama-se a função responsável por verificar se o problema é válido e imprime-se os resultados para o ficheiro de saída*/        
/*Após efetuada a leitura completa de um problema só se calcula solução se não houver erros */

if((error_header != 1) && (error_pontos != 1) && (error_location != 1)){

        if ((lp->modo == 'A')){
        
            Dijkstra(acervo, mapa, x[0], y[0], x[1], y[1], st, wt, &passos, &erro_adj);

            if(erro_adj == 1){
                custoFinal = -1;
               
            }

            else
            custoFinal = wt[x[1]][y[1]];
            
            
        }
        else if(lp->modo == 'B'){

            custoFinal = 0;
            passosTotal = 0;
   
            etapa = alocaEtapa(lp->numAtrac);
            for(i=0; i<(lp->numAtrac-1); i++)
            {
                Dijkstra(acervo, mapa, x[i], y[i], x[i+1], y[i+1], st, wt, &passos, &erro_adj);
               
                etapa[i].ponto = alocaPonto(passos);
                int x_anterior, y_anterior;
                x_anterior = x[i+1];
                y_anterior = y[i+1];
                int k,q;

                for(j = 0; j < passos; j++){

                    etapa[i].ponto[j].x = x_anterior;
                    etapa[i].ponto[j].y = y_anterior;
                    etapa[i].ponto[j].custo = mapa[x_anterior][y_anterior];

                    k= x_anterior;
	                q= y_anterior;
                    x_anterior = st[k][q][0];
                    y_anterior = st[k][q][1];

                }

                custoFinal = custoFinal + wt[x[i+1]][y[i+1]];
                passosTotal = passosTotal + passos; 

                free(acervo->heapdata);
                free(acervo);

                acervo = NewHeap(lp->linha , lp->coluna);
/*
                lol = alocaImpress(passos, mapa, st);
                impressHelp(st, wt, x[i+1], y[i+1], x[i], y[i], mapa, passos, lol);
                printCaminho(fpOut, lol, passos);*/
            }   

        }

        else if(lp->modo == 'C'){
            //MODO C AVAILABLE SOON IN A STORE NEAR YOU
        }

        if(lp->modo == 'B')
            fprintf(fpOut, "%d %d %c %d %d %d\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custoFinal, passosTotal);

        else{

            fprintf(fpOut, "%d %d %c %d %d %d\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custoFinal, passos);
        
            if(custoFinal !=-1 && (lp->modo == 'A')){

                lol = alocaImpress(passos, mapa, st);
                impressHelp(st, wt, x[1], y[1], x[0], y[0], mapa, passos, lol);
                printCaminho(fpOut, lol, passos);
            }

        }

    fprintf(fpOut,"\n");
    
        
}

if((error_header == 1) || (error_location ==1))
 fprintf(fpOut, "%d %d %c %d %d %d\n\n",lp->linha, lp->coluna, lp->modo, lp->numAtrac, custoFinal, passos);

    /* Libertação de memórias */

        if((error_header == 1) || (error_pontos == 1) || (error_location ==1)){
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
/*  
for(i = 0; i< lp->numAtrac; i++){
    ETAPA* current;
    *current = etapa[i];
    free(current);
}
    */
/* Libertação de memória alocada para o ficheiro de saída */
    free(nameFOut);
/* Fecho dos ficheiros abertos e saída do programa */
    fclose(fpIn);
    fclose(fpOut);
    exit(0);
}