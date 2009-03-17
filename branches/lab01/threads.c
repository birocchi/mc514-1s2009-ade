#include "threads.h"

int Calcula_Threads(int lin, int col){

  int i;

  /* Calculo de n_thr inicial
     n_thr <- max{LINHAS, COLUNAS}
     n_thr <- min{n_thr, PTHREAD_THREADS_MAX}  */
  
  if (lin>col) i = lin;
  else i = col;
  
  //if (i>PTHREAD_THREADS_MAX) i = PTHREAD_THREADS_MAX;
  
  return(i);
}



void calcula_prox(char * linhas[4], int tam){
  int i, viz;
  char* linha = linhas[0]; 
  char* prox_linha = linhas[1];
  
  /*percorre a linha, verificando suas redondezas e alterando em prox_linha o que tiver que ser alterado*/  
  for(i=1;i<=tam;i++){
    viz = conta_vizinho(i, linhas);
    if(linha[i]=='#'){
      if(viz > 3 || viz < 2)
	prox_linha[i] = ' ';
      else
	prox_linha[i] = '#';
    }
    if(linha[i]==' '){
      if(viz==3)
	prox_linha[i] = '#';
      else
	prox_linha[i] = ' ';
    }
  }
  return; 
}

int conta_vizinho(int i, char* linhas[4]){
  /*pega de linhas o endereço da linha atual e de suas adjacentes*/
  char* linha = linhas[0];
  char* cima = linhas[2]; 
  char* baixo = linhas[3];
  int j, viz=0;

  /*j recebe o valor anterior do indice atual*/
  j=i-1;

  /*verifica valor contido nas 6 casas (3 superiores e 3 inferiores) adjacentes*/
  for(;j<i+2;j++){
  
    if(cima[j]=='#')
      viz++;
    if(baixo[j]=='#')
      viz++;
  }

  /*confere as casas vizinhas (na mesma linha)*/
  if(linha[i-1]=='#')
    viz++;
  if(linha[i+1]=='#')
    viz++;
  
  return viz;
}

 /*Acho que ja vi esse typedef no main... dejavú ou duplicação do codigo ^^?*/
typedef struct pacote {
  int posicao;
  int tamanho;
  char** tabzero;
  char** tabum;
} pacote_thread;

void * thread(void * dados){
  pacote_thread * ap_pacote = (pacote_thread *) dados;
  pacote_thread pacote = *ap_pacote;
  char* linhas[4];
  int tam;
  
  linhas[0] = pacote.tabzero[pacote.posicao];
  linhas[1] = pacote.tabum[pacote.posicao];
  linhas[2] = pacote.tabzero[(pacote.posicao)-1];
  linhas[3] = pacote.tabzero[(pacote.posicao)+1];
  tam = pacote.tamanho;
  
  calcula_prox(linhas, tam);
  return NULL;
}


void trata_bordas(int lin, int col, char **Matriz){
  
  /*essa funcao determina o comportamento da borda do programa. 
    Caso ela nao exista (caso atual), basta apagar as casas criadas nela na ultima iteracao
    Caso o tabuleiro seja "circular", deve-se passar as casas criadas na borda para os lados opostos*/
  
  int i;
  /*limpa as bordas de cima e de baixo*/
  for(i=0; i<col+2; i++){
    Matriz[0][i] = ' ';
    Matriz[lin+1][i] = ' ';
  }
  
  /*limpa as bordas dos lados*/
  for(i=1; i<lin+1; i++){
    Matriz[i][0] = ' ';
    Matriz[col+1][i] = ' ';
  }
  
}
