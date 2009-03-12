#define HOR 10
#define VER 10

int Calcula_Threads(int lin, int col){

  int i;

  /* Calculo de n_thr inicial
     n_thr <- max{LINHAS, COLUNAS}
     n_thr <- min{n_thr, PTHREAD_THREADS_MAX}  */
  
  if (lin>col) i = lin;
  else i = col;
  
  if (i>PTHREAD_THREADS_MAX) n_thr = PTHREAD_THREADS_MAX;
  
  return(i);
}



void calcula_prox(int * linha, int * prox_linha){
  
  int i, viz;
  /*percorre a linha, verificando suas redondezas e alterando em prox_linha o que tiver que ser alterado*/  
  for(i=1;i<=HOR;i++){
    viz = conta_vizinho(i, linha);
    if(linha[i]==1){
      if(viz > 3 || viz < 2)
	prox_linha[i] = 0;
    }
    if(linha[i]==0){
      if(viz==3)
	prox_linha[i] = 0;
    }
  }
 return; 
}

int conta_vizinho(int i, int*linha, int*cima, int*baixo){
  /*encontra-se o endereço das linhas superiores e inferiores somando ou subtraindo o numero de bytes de cada linha*/
  int * cima = linha - sizeof(int)*(HOR+2); 
  int * baixo = linha + sizeof(int)*(HOR+2);
  int j, viz=0;

  /*j recebe o valor anterior do indice atual*/
  j=i-1;

  /*verifica valor contido nas 6 casas (3 superiores e 3 inferiores) adjacentes*/
  for(;j<j+3;j++){
    if(cima[j]==1)
      viz++;
    if(baixo[j]==1)
      viz++;
  }

  /*confere as casas vizinhas (na mesma linha)*/
  if(linha[i-1]==1)
    viz++;
  if(linha[i+1]==1)
    viz++;
  
  return viz;
}


void * thread(void * linhas){
  calcula_prox((int *)linhas[0], (int *)linhas[1]);
  return NULL;
}


int main(){
	
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

}
