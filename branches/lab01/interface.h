#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

void Interface_arq(char **argv, int *Linhas, int *Colunas, int *i, int **cel_vivas);
int Interface(int *lin, int *col, int *i, int **cel_vivas);
void Inicia_tab0(int lin, int col, char **tab0, int cel_vivas[]);
