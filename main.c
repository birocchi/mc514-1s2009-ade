#include <stdio.h>
#include <pthread.h>


#include "matriz.h"

int main () {

  int Linhas, Colunas, i;
  char **tab0, **tab1; /* matrizes que representam o tabuleiro */
  int n0; /* numero inicial de celulas vivas, obtido na interface */
  int n_thr; /* n de threads que serao executadas simultaneamente */
  char **tmp;

  /* Chamadas pra interface....
     No final, teremos o tabuleiro inicial:  numero de linhas, 
     colunas, as celulas vivas e o numero de iteracoes (i). */


  /* Alocacao da mamoria para as matrizes */
  if( Aloca_Matriz(Linhas,Colunas,&tab0) || Aloca_Matriz(Linhas,Colunas,&tab1) ) {

    /* TRATAMENTO DO ERRO AO ALOCAR MEMORIA PARA AS MATRIZES... */

  }

  /* Imprime o tabuleiro inicial */

  /* Inicializa matriz tab0 com os valores de entrada, ou
   se for o caso, com os valores 'default' */
  
  
  while(i!=0){
    
    /* INICIO DAS CHAMADAS DE THREADS */

    /* Calculo de n_thr inicial
       n_thr <- max{LINHAS, COLUNAS}
       n_thr <- min{n_thr, PTHREAD_THREADS_MAX}  */
    
    if (Linhas>Colunas) n_thr = Linhas;
    else n_thr = Colunas;
    
    if (n_thr>PTHREAD_THREADS_MAX) n_thr = PTHREAD_THREADS_MAX;
    
    
    /* Chamadas das threads que processarao a matriz
       tab0 (estado atual) -> tab1 (proximo estado)  */
    
    
    /* imprime tab1*/
    
    
    tmp=tab1;
    tab0=tab1; /* atualiza o estado para a proxima iteracao */
    tab1=tmp;
    
    i--; /* i: numero de iteracoes restantes */
    
  }
  
  return(0);

}
