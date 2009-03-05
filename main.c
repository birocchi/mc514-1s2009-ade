#include <stdio.h>
#include <pthread.h>

#define LINHAS   10
#define COLUNAS  10


int main () {

  /* Matrizes que representam o tabuleiro em seu
     estado atual e seu proximo estado. */

  char tab0[LINHAS][COLUNAS], tab1[LINHAS][COLUNAS];


  /* n_thr <- max{LINHAS, COLUNAS}
     n_thr <- min{n_thr, PTHREAD_THREADS_MAX}  */

  int n_thr;

  if (LINHAS>COLUNAS) n_thr = LINHAS;
  else n_thr = COLUNAS;

  if (n_thr>PTHREAD_THREADS_MAX) n_thr = PTHREAD_THREADS_MAX;
  
  /*
    n_thr eh o controle do numero de threads que
    rodarao simultaneamente
   */





  return(0);

}
