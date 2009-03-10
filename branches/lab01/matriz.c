#include "matriz.h"

/* Aloca memoria para uma matriz de tamanho recebido como parametro.
 * -Parametros: Numero de linhas, Numero de colunas, Endereço da variavel
 * que armazenara a matriz.
 */
int Cria_Matriz(int num_lin, int num_col, char ***Matriz){

  int i;

  *Matriz = (char**)malloc(sizeof(char*)*num_lin);
  for(i=0; i<num_lin; i++)
    (*Matriz)[i]= (char*)malloc(sizeof(char)*num_col);

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
int Apaga_Matriz(int num_linhas, char ***Matriz){

  int i;

  for(i=0; i<num_linhas; i++)
    free((*Matriz)[i]);
  free(*Matriz);
  return 0;
}


int Imprime_Matriz(int num_lin, int num_col, char **Matriz){
  
  int i,j;

  for(i=0; i<num_lin; i++){
    for(j=0; j<num_col; j++){
      printf("|%c",Matriz[i][j]);
    }
    printf("|\n");
  }
  return 0;
}

int Inicializa_Matriz(int num_lin, int num_col, char **Matriz){
  
  int i,j;

  for(i=0; i<num_lin; i++){
    for(j=0; j<num_col; j++){
      Matriz[i][j]=' ';
    }
  }
  return 0;
}



/*--Main para teste das funcoes--*/
/*
int main (){

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
  return 0;
}
*/
