#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Aloca memoria para uma matriz de tamanho recebido como parametro.
 * -Parametros: Numero de linhas, Numero de colunas, Endereço da variavel
 * que armazenara a matriz.
 */
int Cria_Matriz(int num_lin, int num_col, int **Matriz){

  *Matriz = malloc(sizeof(int)*num_lin*num_col);
  if(Matriz == NULL){
    printf("Erro ao alocar memória");
    return 1;
  }
  else
    return 0;
}


/* Desaloca uma matriz criada na memoria.
 * -Parametros: Endereco da variavel que guarda a matriz
 */
int Apaga_Matriz(int **Matriz){
  free(*Matriz);
  return 0;
}


/*--Main para teste das funcoes--*/
/*int main (){

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
  printf("\n");

  Desaloca_Matriz(&Matriz);
  return 0;
  }*/


