#include "interface.h"

/* Leitura da entrada via Arquivo */
void Interface_arq(char **argv, int *Linhas, int *Colunas, int *i, int **cel_vivas){

  FILE *arq_in;


  /* abre arquivo (string em argv[1]) */
  arq_in=fopen(argv[1], "r");

  /* le linhas, colunas e numero de iteracoes do arquivo */
  


  return;
}



int Interface(int *lin, int *col, int *i, int **cel_vivas) {

  char c;

  do {
    printf("Escolha uma opcao de entrada:\n\n");
    printf("(l)inha de comando\n");
    printf("(d)efault  [entrada padrao atribuida pelo programa]\n");
    printf("(s)air\n");
    scanf("%c", &c);
  } while(c!='l' && c!='d' && c!='s');


  switch(c){

  case 's':
    return(1); /* retorno de 'erro', para finalizacao do processo */

  case 'l':

  case 'd':
    /* ENTRADA PADRAO */
    *lin = 25; /* Tabuleiro 25x25 */
    *col = 25;
    *i = 20; /* 20 iteracoes */

    /* Atribuicao das celulas vivas inicialmente */
    /* !! ATENCAO: cel_vivas[0] contem o numero de celulas vivas inicialmente!! 
       Portanto, se o vetor vai de 0 a N, cel_vivas[0]==N/2
     */
    *cel_vivas=(int *)malloc(sizeof(int)*27);

    (*cel_vivas)[0]=13;
    (*cel_vivas)[1]=10 ;  /* Linha - Celula 1 */
    (*cel_vivas)[2]=10 ;  /* Coluna - Celula 1 */
    (*cel_vivas)[3]=10 ;  /* Cel2 */
    (*cel_vivas)[4]=11 ;
    (*cel_vivas)[5]=10 ;  /* Cel3 */
    (*cel_vivas)[6]=12 ;
    (*cel_vivas)[7]=10 ;  /* ... */
    (*cel_vivas)[8]=14 ;
    (*cel_vivas)[9]=11 ;  
    (*cel_vivas)[10]=10;
    (*cel_vivas)[11]=12;  
    (*cel_vivas)[12]=13;
    (*cel_vivas)[13]=12;  
    (*cel_vivas)[14]=14;
    (*cel_vivas)[15]=13;  
    (*cel_vivas)[16]=11;
    (*cel_vivas)[17]=13;  
    (*cel_vivas)[18]=12;
    (*cel_vivas)[19]=13;  
    (*cel_vivas)[20]=14;
    (*cel_vivas)[21]=14;  
    (*cel_vivas)[22]=10;
    (*cel_vivas)[23]=14;  
    (*cel_vivas)[24]=12;
    (*cel_vivas)[25]=14;  
    (*cel_vivas)[26]=14;

  }/* fim do switch */

  return(0);
}




void Inicia_tab0(int lin, int col, char **tab0, int *cel_vivas) {

  int i,j;

  /* Insere espaco em todas as celulas */
  for(i=0;i<lin+2;i++) {
    for(j=0;j<col+2;j++) 
      tab0[i][j]=' ';
  }

  /* Insere as celulas vivas */
  for(i=1;i<=2*cel_vivas[0];i+=2){
    tab0[ cel_vivas[i] ][ cel_vivas[i+1] ]='#';
  }

  return;
}
