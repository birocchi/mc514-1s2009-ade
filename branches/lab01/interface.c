#include "interface.h"


void Print_intro(){

    printf("          #####################################\n");
    printf("          ##  MC514 - Sistemas Operacionais  ##\n");
    printf("          ##                                 ##\n");
    printf("          ##  Laboratorio 1 - Jogo da Vida   ##\n");
    printf("          #####################################\n\n");
    return;
}

int Interface(int *lin, int *col, int *i, int **cel_vivas) {

  char c;
  int j;

  do {
    Print_intro();
    printf("  o----------------------------------------------------o\n");
    printf("  |           Escolha uma opcao de entrada:            |\n");
    printf("  |                                                    |\n");
    printf("  | (l)inha de comando                                 |\n");
    printf("  | (d)efault [entrada padrao atribuida pelo programa] |\n");
    printf("  | (s)air                                             |\n");
    printf("  o----------------------------------------------------o\n");
    printf("  ->");
    scanf("%c", &c);
    printf("\n");
    system("clear");
  } while(c!='l' && c!='d' && c!='s');


  switch(c){

  case 's':
    return(1); /* retorno de 'erro', para finalizacao do processo */
    break;

  case 'l':
    Print_intro();
    printf("  Digite o numero de linhas: ");
    scanf("%d",lin);
    printf("  Digite o numero de colunas: ");
    scanf("%d",col);
    printf("  Digite o numero de geracoes: ");
    scanf("%d",i);

    /*como o tabuleiro pode estar cheio, o numero de 
     *celulas vivas=lin*col*2(casas/celula)+1(cel_vivas[0])
     */
    *cel_vivas = (int*)malloc(sizeof(int)*(*lin)*(*col)*2+1);

    printf("  Digite o numero de celulas vivas: ");
    scanf("%d",&(*cel_vivas)[0]);
    printf("  Digite as coordenadas das celulas vivas (linha,coluna):\n");
    for(j=1; j <= ((*cel_vivas)[0]*2); j+=2){
      printf("  ->");
      scanf("%d,%d",&(*cel_vivas)[j],&(*cel_vivas)[j+1]);
    }
    return 0;

  case 'd':
    /* ENTRADA PADRAO */
    *lin = 25; /* Tabuleiro 25x25 */
    *col = 25;
    *i = 10; /* n iteracoes */

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



void Inicia_tab0 (char **tab0, int *cel_vivas) {

  /* Todas as celulas ja ganharam espaco quando foram alocadas, 
     portanto aqui apenas iremos alterar as celulas com valor */

  int j;
  /* Insere as celulas vivas */

  for(j=1;j<=2*cel_vivas[0];j+=2){
    tab0[ cel_vivas[j] ][ cel_vivas[j+1] ]='#';
  }
  return;
}
