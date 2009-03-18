#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "matriz.h"
#include "threads.h"
#include "interface.h"

#define PTHREAD_THREADS_MAX 25  /* valor maximo de threads simultaneas */

int main(int argc, char *argv[]) {

  int Linhas, Colunas;    /* numero de linhas e colunas desejado */
  int  i, j, k, l, m;     /* indexadores/contadores */
  char **tab0, **tab1;    /* matrizes que representam o tabuleiro */
  int n_thr;              /* n de threads que serao executadas simultaneamente*/
  char **tmp;
  int *cel_vivas;         /* vetor com os indices das celulas vivas */
  pthread_t* thr;      
  pacote_thread* dados;   /* contem as informacoes necessarias para a thread operar com a tabela*/

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
  Inicia_tab0(tab0, cel_vivas);


  /* Imprime o tabuleiro inicial */
  j=0;
  Imprime_Matriz(Linhas,Colunas,tab0,j);
  
   
  /*  n_thr = min{Linhas,PTHREAD_THREADS_MAX */
  if(Linhas < PTHREAD_THREADS_MAX)
    n_thr=Linhas;
  else
    n_thr=PTHREAD_THREADS_MAX;

  thr = (pthread_t*) malloc(sizeof(pthread_t)*n_thr);
  dados = (pacote_thread*) malloc(sizeof(pacote_thread)*n_thr);

  
  for(j=1;j<=i;j++){
    
    /*Chamadas das threads que processarao a matriz:
      tab0 (estado atual) -> tab1 (proximo estado)  */
    
    l=0;   
    for(k=1; k<=Linhas; k++){
      l++; /*contador de threads*/
      /*se o numero de threads lancadas for o maximo, 
	espera elas terminarem para lancar novas*/
      if(l == n_thr+1){
	for(m=0; m<n_thr; m++)      
	  pthread_join(thr[m], NULL);
	l=1; /*reseta o contador*/
      }
      
      dados[l-1].posicao = k;
      dados[l-1].tamanho = Linhas;
      dados[l-1].tabzero = tab0;
      dados[l-1].tabum = tab1;
      
      /*cria threads para percorrer as linhas e atualiza-las (uma thread por linha)*/
      pthread_create(&thr[l-1], NULL, thread, (void *) &dados[l-1]); 
      
    }
    
    /*aguarda o termino das threads para impressao*/    
    for(k=1; k<=l; k++){
      pthread_join(thr[k-1], NULL); 
    }
    
    
    /* imprime tab1*/
    Imprime_Matriz(Linhas,Colunas,tab1,j);
    
    trata_bordas(Linhas, Colunas, tab0); /*a cada iteracao, eh necessario verificar as bordas do tabuleiro*/
    trata_bordas(Linhas, Colunas, tab1);

    tmp = tab0;
    tab0=tab1; /* atualiza o estado para a proxima iteracao */
    tab1 = tmp; /*tab1 recebe antiga tab0 (que seria lixo), pra guardar as novas alteracoes*/
  }
  
  printf("\n\nPrograma terminado.\n\n");  
  Desaloca_Matriz(Linhas,&tab0);
  Desaloca_Matriz(Linhas,&tab1);
  free(cel_vivas);
  free(thr);
  free(dados);
  
  return(0);
  
}
