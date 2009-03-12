#include <stdio.h>
#include <pthread.h>


#include "matriz.h"
#include "threads.h"
#include "interface.h"


int main () {

  int Linhas, Colunas, i, j;
  char **tab0, **tab1; /* matrizes que representam o tabuleiro */
  int n0; /* numero inicial de celulas vivas, obtido na interface */
  int n_thr; /* n de threads que serao executadas simultaneamente */
  char **tmp;

  /* Chamadas pra interface....
     No final, teremos o tabuleiro inicial:  numero de linhas, 
     colunas, as celulas vivas e o numero de iteracoes (i). */


  /* Alocacao da mamoria para as matrizes */
  if( Aloca_Matriz(Linhas,Colunas,&tab0) || Aloca_Matriz(Linhas,Colunas,&tab1) ){
    /* Tratamento de erro na alocacao -> finaliza execucao */
    printf("O programa sera finalizado.\n\n");
    return(0);
  }


  /* Inicializa matriz tab0 com os valores de entrada, ou
   se for o caso, com os valores 'default' */


  /* Imprime o tabuleiro inicial */
  j=0;
  Imprime_Matriz(Linhas,Colunas,tab0,j);
   
  n_thr=Calcula_Threads(Linhas,Colunas);

  for(j=1;j<=i;j++){
    
    /* Chamadas das threads que processarao a matriz:
       tab0 (estado atual) -> tab1 (proximo estado)  */
    
    
    /* imprime tab1*/
    Imprime_Matriz(Linhas,Colunas,tab1,j);
    
    
    tmp=tab1;
    tab0=tab1; /* atualiza o estado para a proxima iteracao */
    tab1=tmp;
    
    
  }
  
  return(0);

}
