#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiro.h"
#include "struct.h"
#include "oper.h"


    void encontraAdj(int** matriz, int x, int y, int xmax, int ymax, int adj[8][2]){
    int i = 0;
    int Adjs[8][2] = {{1, 2}, {-1, -2}, {-1, 2}, {1, -2}, {2, 1}, {-2, -1}, {2, -1}, {-2, 1}};
    xmax = xmax-1;
    ymax = ymax-1;

    for(i=0; i<=7; i++){
    adj[i][0] = -1;
    adj[i][1] = -1;
    }

    for(i=0; i<=7; i++){
        if(x+Adjs[i][0] >= 0 && x+Adjs[i][0] <= xmax && y+Adjs[i][1] >= 0 && y+Adjs[i][1] <= ymax){
            if(matriz[x+Adjs[i][0]][y+Adjs[i][1]] != 0 ){
            adj[i][0] = x+Adjs[i][0];
            adj[i][1] = y+Adjs[i][1];
           }
        }
    }
}


