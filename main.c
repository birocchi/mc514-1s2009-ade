#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "matriz.h"
#include "threads.h"
#include "interface.h"


int main(int argc, char *argv[]) {

  int Linhas, Colunas, i, j, k;
  char **tab0, **tab1; /* matrizes que representam o tabuleiro */
  int n_thr; /* n de threads que serao executadas simultaneamente */
  char **tmp;
  int *cel_vivas; /* vetor com os indices das celulas vivas */
  char **linha;
  pthread_t thr[25]; /*fazer essa alocacao ser dinamica futuramente*/



  /* Chamadas da interface....
     No final, teremos o tabuleiro inicial:  numero de linhas, 
     colunas, as celulas vivas e o numero de iteracoes (i). */
  
  if(argc>2) {
    printf("Inicie novamente com apenas um parametro de entrada.\n\n");
    return(0);
  }
  else{
    /* entrada via arquivo */
    if(argc==2) return(0);/*Interface_arq(*argv, &Linhas, &Colunas, &i, &cel_vivas);*/
    /* entrada por linha de comando ou padrao */
    else 
      if(Interface(&Linhas, &Colunas, &i, &cel_vivas)) return(0); 
  }
  

  /* Alocacao da mamoria para as matrizes */
  if( Aloca_Matriz(Linhas,Colunas,&tab0) || Aloca_Matriz(Linhas,Colunas,&tab1) ){
    /* Tratamento de erro na alocacao -> finaliza execucao */
    printf("O programa sera finalizado.\n\n");
    return(0);
  }


  /* Inicializa o tabuleiro com os valores de entrada */
  Inicia_tab0(Linhas, Colunas, tab0, cel_vivas);


  /* Imprime o tabuleiro inicial */
  j=0;
  Imprime_Matriz(Linhas,Colunas,tab0,j);

  

   
  /*n_thr=Calcula_Threads(Linhas,Colunas);*/ /* threads.h */
  
  linha = (char**) malloc(sizeof(char*)*2);
  linha[0] = (char*) malloc(sizeof(char)*Linhas);
  linha[1] = (char*) malloc(sizeof(char)*Linhas);
  
  for(j=1;j<=i;j++){
    

    /*thread:
      parametros de entrada:
      int * linhas, onde:
      linhas[0] = endereço da linha da matriz a ser lida
      linhas[1] = endereço da linha da matriz a ser escrita
      (lembre de colocar um cast como: (void *) linhas)
      
      retorno: 
      NULL (a linha a ser escrita ja foi alterada durante a execucao da thread)
      
      resumindo: vc vai fazer
      int * linhas[2]
      pthread_create(..., thread, (void*) linhas);
    */
    for(k=1; k<=Linhas; k++){
      linha[0] = tab0[k];     
      linha[1] = tab1[k];
      pthread_create(&thr[k-1], NULL, thread, (void *) linha); 
    }
    
    /*Chamadas das threads que processarao a matriz:
      tab0 (estado atual) -> tab1 (proximo estado)  */
    
    
    /* imprime tab1*/
    

    Imprime_Matriz(Linhas,Colunas,tab1,j);
    

    tmp=tab1;
      
    tab0=tab1; /* atualiza o estado para a proxima iteracao */
    tab1=tmp;
  }
  
  
  Desaloca_Matriz(Linhas,&tab0);
  Desaloca_Matriz(Linhas,&tab1);
  
  
  return(0);

}
