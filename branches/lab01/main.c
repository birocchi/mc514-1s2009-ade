#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "matriz.h"
#include "threads.h"
#include "interface.h"

/*pacote com todas as informacoes que uma thread sempre quis saber pra poder modificar uma linha ou coluna da matriz*/
typedef struct pacote {
  int posicao;
  int tamanho;
  char** tabzero;
  char** tabum;
} pacote_thread;


int main(int argc, char *argv[]) {

  int Linhas, Colunas;    /* numero de linhas e colunas desejado */
  int  i, j, k;           /* indexadores/contadores */
  char **tab0, **tab1;    /* matrizes que representam o tabuleiro */
  int n_thr;              /* n de threads que serao executadas simultaneamente*/
  char **tmp;
  int *cel_vivas;         /* vetor com os indices das celulas vivas */
  pthread_t thr[25];      /* fazer essa alocacao ser dinamica futuramente */
  pacote_thread dados[25];  /* contem as informacoes necessarias para */

  system("clear");
  
  /* Chamadas da interface....
     No final, teremos o tabuleiro inicial:  numero de linhas, 
     colunas, as celulas vivas e o numero de iteracoes (i). */
  
  /* Caso tenha dois parametros, sai do programa*/
  if(argc>2) {
    printf("Inicie novamente com apenas um parametro de entrada.\n\n");
    return(0);
  }
  else{
    /* Caso tenha um parametro, abre o arquivo indicado para uso posterior*/
    if(argc==2){
      printf("Este programa ainda nao aceita parametros\n");
      /*Interface_arq(*argv, &Linhas, &Colunas, &i, &cel_vivas);*/
      return(0);
    }
    else 
      /* Chama o menu de interface */
      if(Interface(&Linhas, &Colunas, &i, &cel_vivas))
	/* Caso a funcao retorne 1, sai do programa*/
	return(0); 
  }
  

  /* Alocacao de memoria para as matrizes */
  Aloca_Matriz(Linhas,Colunas,&tab0);
  Aloca_Matriz(Linhas,Colunas,&tab1);
      

  /* Inicializa o tabuleiro com os valores de entrada */
  Inicia_tab0(Linhas, Colunas, tab0, cel_vivas);


  /* Imprime o tabuleiro inicial */
  j=0;
  Imprime_Matriz(Linhas,Colunas,tab0,j);

  

   
  /*n_thr=Calcula_Threads(Linhas,Colunas);*/ /* threads.h */




    
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
      dados[k-1].posicao = k;
      dados[k-1].tamanho = Linhas;
      dados[k-1].tabzero = tab0;
      dados[k-1].tabum = tab1;

      pthread_create(&thr[k-1], NULL, thread, (void *) &dados[k-1]); 
    }
    
    for(k=1; k<=Linhas; k++){
      pthread_join(thr[k-1], NULL); 
    }
    /*
    for(k=1; k<=Linhas; k++){
      linha[0] = tab0[k];
      linha[1] = tab1[k];
      linha[2] = tab0[k-1];
      linha[3] = tab0[k+1];
      calcula_prox(linha[0], linha[1], tab0[k-1], tab0[k+1]);
      //tab1[k] = linha[1];
    }
    */
    /*Chamadas das threads que processarao a matriz:
      tab0 (estado atual) -> tab1 (proximo estado)  */
    
    
    /* imprime tab1*/
     

    Imprime_Matriz(Linhas,Colunas,tab1,j);
    
    
    tmp = tab0;
    tab0=tab1; /* atualiza o estado para a proxima iteracao */
    tab1 = tmp; /*tab1 recebe antiga tab0 (que seria lixo), pra guardar as novas alteracoes*/
  }
  
  
  Desaloca_Matriz(Linhas,&tab0);
  Desaloca_Matriz(Linhas,&tab1);
  
  
  return(0);
  
}
