#include <stdio.h>

int Calcula_Threads(int lin, int col);
void calcula_prox(char* linhas[4],int tam);
int conta_vizinho(int i, char* linhas[4]);
void * thread(void * dados);
void trata_bordas(int lin, int col, char **Matriz);
