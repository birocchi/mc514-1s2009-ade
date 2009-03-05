#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main (){

  int i;
  int Lin = 4;
  int Col = 4;
  int *Matriz;

  Cria_Matriz(Lin,Col,&Matriz);
  printf("Matriz %d x %d criada\n", Lin, Col);

  for(i=0; i<(Lin*Col); i++){
    printf("i= %d\n", i);
    Matriz[i] = i+100; 
    printf("Matriz[i]= %d\n", Matriz[i]); 
  }
  for(i=0; i<(Lin*Col); i++)
    printf("%d|", Matriz[i]);
  return 0;
}

int Cria_Matriz(int num_lin, int num_col, int *Matriz){

  Matriz = malloc(sizeof(int)*16);
  if(Matriz == NULL){
    printf("Erro ao alocar memória");
    return 1;
  }
  else
    return 0;
}
