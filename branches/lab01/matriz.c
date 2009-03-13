#include "matriz.h"

/* Aloca memoria para uma matriz de tamanho recebido como parametro.
 * -Parametros: Numero de linhas, Numero de colunas, Endereço da variavel
 * que armazenara a matriz.
 */
int Aloca_Matriz(int num_lin, int num_col, char ***Matriz){

  int i;

  *Matriz = (char**)malloc(sizeof(char*)*num_lin+2);
  for(i=0; i<num_lin+2; i++)
    (*Matriz)[i]= (char*)malloc(sizeof(char)*num_col+2);

  if(Matriz == NULL){
    printf("Erro ao alocar memória\n");
    return 1;
  }
  else{
    return 0;
  }
}


/* Desaloca uma matriz criada na memoria.
 * -Parametros: Numero de linhas, Endereco da variavel que guarda a matriz
 */
int Desaloca_Matriz(int num_linhas, char ***Matriz){

  int i;

  for(i=0; i<num_linhas+2; i++)
    free((*Matriz)[i]);
  /*free(Matriz);  //verificar se a matriz ta sendo liberada..talvez quando ele libera Matriz[0], ele ta liberando tudo?
*/ 
  return 0;
}


int Imprime_Matriz(int num_lin, int num_col, char **Matriz, int estado){
  
  int i,j;

  printf("Tabuleiro %d:\n\n", estado);

  for(i=1; i<=num_lin; i++){
    for(j=1; j<=num_col; j++){
      printf("|%c",Matriz[i][j]);
    }
    printf("|\n");
  }
  return 0;
}

/*essa funcao nao ta sendo usada, ta ligado? :) tem outra no arquivo interface.c q a substitui!*/
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

  Aloca_Matriz(Lin,Col,&Matriz);
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
