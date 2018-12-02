#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiro.h"
#include "struct.h"
#include "oper.h"

/*Algoritmo que decide o salto de custo mínimo entre os 8 saltos possíveis para certa posição*/

int find_next_step(int** matriz,int x,int y, int xmax, int ymax){
    int Vmin = 100;
    int n=0;
    xmax = xmax-1;
    ymax = ymax-1;

    if(salto_1(x, y) == 1){
        if((matriz[x-1][y-2] < Vmin) && (matriz[x-1][y-2] > 0)){
            Vmin = matriz[x-1][y-2];
            n = 1; 

        }
    }

    if (salto_2( x,  y,  xmax ) == 1){
        if((matriz[x+1][y-2] < Vmin) && (matriz[x+1][y-2] > 0)){

            Vmin = matriz[x+1][y-2];
            n = 2;
        }
    }

    if (salto_3( x,  y,  xmax ) == 1){
        if((matriz[x+2][y-1] < Vmin) && (matriz[x+2][y-1] > 0)){
            Vmin = matriz[x+2][y-1];
            n = 3;
        }
    }

    if (salto_4( x, y, xmax, ymax) == 1){
        if((matriz[x+2][y+1] < Vmin) && (matriz[x+2][y+1] > 0))
        {
            Vmin = matriz[x+2][y+1];
            n = 4;
        }

    }

    if (salto_5( x, y, xmax, ymax) == 1){
        if((matriz[x+1][y+2] < Vmin) && (matriz[x+1][y+2] > 0)){

            Vmin = matriz[x+1][y+2];
            n = 5;
        }
    }

    if (salto_6( x,  y,  ymax ) == 1){
        if((matriz[x-1][y+2] < Vmin) && (matriz[x-1][y+2] > 0)){
            Vmin = matriz[x-1][y+2];
            n = 6;
        }
    }

    if (salto_7( x,  y,  ymax ) == 1){
            if((matriz[x-2][y+1] < Vmin) && (matriz[x-2][y+1] > 0)){
            Vmin = matriz[x-2][y+1];
            n = 7;
        }
        
    }

    if (salto_8(x, y) == 1){
        if((matriz[x-2][y-1] < Vmin) && (matriz[x-2][y-1] > 0)){
            Vmin = matriz[x-2][y-1];
            n = 8;
        }
    }

    return n;
}

/*  Muda as coordenadas de x e y para representar um salto na direção escolhida por find_next_step e adiciona o valor da posição ao custo*/

void move_next_stepA(int** matriz, int *x, int *y, int *custo, int linha, int coluna ){
    int n;
    n = find_next_step(matriz,*x, *y, linha, coluna);
    if (n == 1){
        *x = *x -1;
        *y = *y-2;
        *custo += matriz[*x][*y];
    }
    else if (n == 2){
        *x = *x +1;
        *y = *y-2;
        *custo += matriz[*x][*y];
    }
    else if (n == 3){
        *x = *x +2;
        *y = *y-1;
        *custo += matriz[*x][*y];
    }
    else if (n == 4){
        *x = *x +2;
        *y = *y+1;
        *custo += matriz[*x][*y];
    }
    else if (n == 5){
        *x = *x +1;
        *y = *y+2;
        *custo += matriz[*x][*y];
    }
    else if (n == 6){
       *x = *x -1;
        *y = *y+2;
        *custo += matriz[*x][*y];
    }
    else if (n == 7){
        *x = *x -2;
        *y = *y+1;
        *custo += matriz[*x][*y];
    }
    else if (n == 8){
        *x = *x -2;
        *y = *y-1;
        *custo += matriz[*x][*y];
    }
    else
        *custo = 0;


}

/*Adiciona o valor da posição ao custo*/

void move_next_stepB(int** matriz, int *x, int *y, int *custo){ 

    *custo += matriz[*x][*y];

}

/*  Testes para garantir que o salto efetuado não vai para fora do mapa ou para um ponto inacessível  */

int salto_1(int x, int y){
    int validade;
    if((x > 0) && (y - 2) >= 0)
        validade = 1;
    else 
        validade = 0;

    return validade;
}

int salto_2(int x, int y, int xmax){
    int validade;
    if(((xmax-x) >= 1)  && ((y-2)>=0))
        validade = 1;
    else
        validade = 0;

    return validade;
}

int salto_3(int x, int y, int xmax){
    int validade;
    if(((xmax-x) >= 2)  && ((y-1)>=0))
        validade = 1;
    else
        validade = 0;
        
    return validade;
}

int salto_4(int x, int y, int xmax,int ymax){
    int validade;
    if(((xmax-x) >= 2) &&  ((y+1)<=ymax) )
        validade = 1;
    else
        validade = 0;
        
    return validade;
}

int salto_5(int x, int y, int xmax,int ymax){
    int validade;
    if(((xmax-x) >= 1) &&  ((y+2)<=ymax))
        validade = 1;
    else
        validade = 0;
        
    return validade;
}

int salto_6(int x, int y, int ymax){
    int validade;
    if((x > 0) && ((y+2)<=ymax) )
        validade = 1;
    else
        validade = 0;
        
    return validade;
}

int salto_7(int x, int y, int ymax){
    int validade;
    if((x > 1) && ((y+1)<=ymax) )
        validade = 1;
    else
        validade = 0;
        
    return validade;
}

int salto_8(int x, int y){
    int validade;
    if((x > 1) && ((y-1)>=0))
        validade = 1;
    else 
        validade = 0;

    return validade;
}

/*Verifica que a posição está dentro do mapa e é acessível*/

int checklocations(int x, int y, int nlinhas, int ncolunas, int** mapa){

    if((x>=(nlinhas)) || (y>=(ncolunas)) || (x < 0)|| (y < 0)){
        return 1;
    }

    else if((mapa[x][y]) <= 0){
        return 1;

    }    
    else 
        return 0;

}

/*  Verifica que o salto entre x0 e x, y0 e y é possível    */

int check_knight_jump(int x0, int y0, int x, int y){
    if((abs(x0-x)==2) && ((abs(y0-y)==1))){
        return 0;
    }

    else if((abs(x0-x)==1) && ((abs(y0-y)==2))){
        return 0;
    }
    else 
        return 1;
}
