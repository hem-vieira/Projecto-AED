#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "oper.h"
#include "ficheiro.h"

/*Estrutura que guarda os dados referentes a cada mapa*/

void criaNovoNo (ronda** lp)
 {
  ronda *novoNo;

  novoNo = (ronda*) malloc(sizeof(ronda));
  
  if (novoNo == NULL){
      exit (0);
  }

  else if(novoNo!=NULL) {
    novoNo->coluna =0;
    novoNo->linha =0;
    novoNo->modo =0;
    novoNo->numAtrac =0;

    *lp = novoNo;    
  } 

  else{
      exit(0);
  }

}

