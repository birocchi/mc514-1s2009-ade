#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Aloca memoria para uma matriz de tamanho recebido como parametro.
 * -Parametros: Numero de linhas, Numero de colunas, Endereço da variavel
 * que armazenara a matriz.
 */
int Cria_Matriz(int num_lin, int num_col, int ***Matriz){

  int i;

  *Matriz = (int**)malloc(sizeof(int)*num_lin);
  for(i=0; i<num_lin; i++)
    (*Matriz)[i]= (int*)malloc(sizeof(int)*num_col);

  if(Matriz == NULL){
    printf("Erro ao alocar memória");
    return 1;
  }
  else{
    return 0;
  }
}


/* Desaloca uma matriz criada na memoria.
 * -Parametros: Numero de linhas, Endereco da variavel que guarda a matriz
 */
int Apaga_Matriz(int num_linhas, int ***Matriz){

  int i;

  for(i=0; i<num_linhas; i++)
    free((*Matriz)[i]);
  free(*Matriz);
  return 0;
}


int Imprime_Matriz(int num_lin, int num_col, int **Matriz){
  
  int i,j;

  for(i=0; i<num_lin; i++){
    for(j=0; j<num_col; j++){
      printf("|%d",Matriz[i][j]);
    }
    printf("|\n");
  }
}


/*--Main para teste das funcoes--*/
int main (){

  int i;
  int Lin = 4;
  int Col = 4;
  int **Matriz;

  Cria_Matriz(Lin,Col,&Matriz);
  printf("Matriz %d x %d criada\n", Lin, Col);
  Imprime_Matriz(Lin,Col,Matriz);

  Matriz[0][0] = 4;
  Matriz[1][1] = 5;
  Matriz[2][2] = 6;
  Matriz[3][3] = 7;

  printf("\n");
  Imprime_Matriz(Lin,Col,Matriz);

  Apaga_Matriz(Lin,&Matriz);
  return 0;
}
