#include <stdio.h>

int Calcula_Threads(int lin, int col);
void calcula_prox(char* linhas[4],int tam);
int conta_vizinho(int i, char* linhas[4]);
void * thread(void * dados);
void trata_bordas(int lin, int col, char **Matriz);

/*pacote com todas as informacoes que uma thread sempre 
  quis saber pra poder modificar uma linha ou coluna da matriz*/
typedef struct pacote {
  int posicao;
  int tamanho;
  char** tabzero;
  char** tabum;
} pacote_thread;
