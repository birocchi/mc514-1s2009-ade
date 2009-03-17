#include "matriz.h"

/* Aloca memoria para uma matriz de tamanho recebido como parametro.
 * -Parametros: Numero de linhas, Numero de colunas, Endereço da variavel
 * que armazenara a matriz.
 */
int Aloca_Matriz(int num_lin, int num_col, char ***Matriz){

  int i, j;

  *Matriz = (char**)malloc(sizeof(char*)*num_lin+2);
  for(i=0; i<num_lin+2; i++)
    (*Matriz)[i]= (char*)malloc(sizeof(char)*num_col+2);

  if(Matriz == NULL){
    printf("Erro ao alocar memoria!\n");
    printf("O programa sera finalizado...\n");
    exit(1);
  }
  else{

    /*preenche a matriz com espacos vazios*/
    for(i=0; i<num_lin+2; i++){
      for(j=0; j<num_col+2; j++){
      (*Matriz)[i][j]=' ';
      }
    }
    
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

  free(*Matriz);

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
