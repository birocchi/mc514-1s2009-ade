#include <stdio.h>
#include <pthread.h>


#include "matriz.h"


int main () {

  int Lin = 5;
  int Col = 5;
  char **Matriz;

  Cria_Matriz(Lin,Col,&Matriz);
  printf("Matriz %d x %d criada\n", Lin, Col);
  Inicializa_Matriz(Lin,Col,Matriz);
  Imprime_Matriz(Lin,Col,Matriz);

  Matriz[0][0] = '#';
  Matriz[1][1] = '#';
  Matriz[2][2] = '#';
  Matriz[3][3] = '#';
  Matriz[4][4] = '#';

  printf("\n");
  Imprime_Matriz(Lin,Col,Matriz);

  Apaga_Matriz(Lin,&Matriz);

  return(0);

}
