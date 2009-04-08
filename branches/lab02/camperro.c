/* 
 * Campeonato entre N threads para acesso �regi�o cr�tica.
 *
 *
 * Comandos sleep foram colocados nos seguintes pontos:
 *   - entre as partidas;
 *   - entre a atribui��o � vari�vel s e a impress�o do
 *     valor desta vari�vel;
 *   - fora da regi�o cr�tica.  
 *
 * Esperas ocupadas substituidas por chamadas a futex_wait. 
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <limits.h>

/* Retorna -1 se o futex n�o bloqueou e 
            0 caso contr�rio */
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Retorna o n�mero de threads que foram acordadas */
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}

/* N�mero de vezes que uma thread deve entrar na regi�o cr�tica. */
#define N_VEZES 5
/* Vari�vel compartilhada */
volatile int s = 0;
/* Numero de threads */
int N_THR;

/* Vari�veis de controle para as partidas */
int ** interesse;
int ** ultimos;
int n_fases;


/*Fun��o que cria vetores para disputas*/
void inicializa_tabelas(int n_thr){
  
  /*como funciona:
   * para X threads, dado um est�gio N temos:
   * 1� fase: X interesses, X/2 �ltimos
   * 2� fase: X/2 interesses, X/4 �ltimos
   * .... n fases at�:
   * 2 interesses, 1 �ltimo
   *
   * */
  int i, j, n, tam;
  
  n_fases=0;
  
  n=1;
  while(n < n_thr){
    n = n*2;
    n_fases++;
  }
  /*n recebe a menor potencia de 2 maior a n_thr
   *n_fases recebe o expoente de n ( i = log2(n) )
   * */
  
  interesse = (int**) malloc(sizeof(int*)*n_fases);
  ultimos  = (int**) malloc(sizeof(int*)*n_fases);
  
  tam = n;
  for(i=0; i<n_fases; i++){
    interesse[i] = (int*) malloc(sizeof(int)*tam);
    ultimos[i] = (int*) malloc(sizeof(int)*tam/2);
    tam=tam/2;
  }
  
  /*inicializa matrizes*/
  tam = n;
  for(i=0; i<n_fases; i++){
    for(j=0; j<tam; j++){
      interesse[i][j] = 0;
      ultimos[i][j/2] = 0;
    }
    tam=tam/2;
  }
}


/*Fun��o que acha o rival de uma thread em uma disputa (de acordo com o id)*/
int rival(int thr_id){
  if(thr_id%2 == 0) /*se for par, disputa com a pr�xima (ex: 0 disputa com thr_id 1)*/
    return thr_id+1;
  else	/*caso contr�rio, disputa com a anterior*/
    return thr_id-1;
}


void disputa(partida, lugar){

  interesse[partida][lugar] = 1;
  ultimos[partida][lugar/2] = lugar;
  
  /* se as duas threads estao interessadas ao mesmo tempo, a thread que setou a variavel ultimos[partida][lugar/2] 
   * primeiro vai dormir e esperar at� que a thread que passou para a regi�o cr�tica a acorde.*/
  if(interesse[partida][rival(lugar)]){
    futex_wake(&ultimos[partida][lugar/2], N_THR-1);  /*se uma thread dormiu antes, por ter chegado em primeiro, a ultima acorda ela, pra poder dormir*/
    futex_wait(&ultimos[partida][lugar/2], lugar);

  }
  
}


void desinteressa(thr_id){
  
  int i;
  int categorias[n_fases];
  
  
  for(i=0; i<n_fases; i++){
    categorias[i] = thr_id; /*categorias guarda cada id q a thread teve em cada estagio do campeonato*/
    thr_id = thr_id/2;
  }
  
  for(i=0; i<n_fases; i++){
    interesse[i][categorias[i]] = 0;  
    ultimos[i][categorias[i]/2] = 0;  
    futex_wake(&ultimos[i][categorias[i]/2], N_THR-1); 
	sleep(2);
	/*retira interesses e acorda futex's na ordem direta em que foram colocados.
	 * Isso gera um erro no algoritmo, evidenciado pelo sleep, pois threads de fases 
	 * iniciais s�o liberadas antes do tempo, gerando conflitos na regi�o cr�tica*/
  }
  

}

/* Fun��o gen�rica para as threads*/
void* f_thread(void *v) {
  int i, partida, thr_id;
  int lugar;
  thr_id = *(int *) v;
  
  
  for (i = 0; i < N_VEZES; i++) {
    
    lugar = thr_id;
    for(partida = 0; partida<n_fases; partida++){
      disputa(partida, lugar); /*para poder modificar a variavel compartilhada, deve passar por n_fases partidas*/
      sleep(1); /* Sleep entre as partidas */
      lugar = lugar/2; /*quando passa de fase, sobe de categoria*/
    }	
    
    /**************************/
    /* !!! REGI�O CR�TICA !!! */
    /*quem ganha a disputa, ganha o premio! mudar a variavel compartilhada com o seu id!!!*/
    s = thr_id;
    sleep(1); /* Sleep entre a atribui��o e a impress�o */    
    printf("Thread %d, s = %d.\n", thr_id, s); 
    /* !!! REGI�O CR�TICA !!! */
    /**************************/

    desinteressa(thr_id);  /*retira o interesse das threads para poder liberar as proximas*/
    
    sleep(1); /* Sleep fora da regi�o cr�tica */
  }
  
  return NULL;
}


int main(int argc, char *argv[]) {

  pthread_t *thr;
  int i, *id;

  if(argc!=2){
    printf("Argumento unico obrigatorio: numero de threads.\n");
    return(0);
  }
  else N_THR = atoi(argv[1]);

  thr = (pthread_t *)malloc(sizeof(pthread_t) * N_THR);
  id = (int *)malloc(sizeof(int) * N_THR);

  inicializa_tabelas(N_THR);
  
  for (i = 0; i < N_THR; i++) {
    id[i] = i;
    pthread_create(&thr[i], NULL, f_thread, (void*) &id[i]);
  }
  
  for (i = 0; i < N_THR; i++) 
    pthread_join(thr[i], NULL); 
  

  free(thr);
  free(id);

  for(i=0 ; i<n_fases ; i++) {
    free(interesse[i]);
    free(ultimos[i]);
  }

  free(interesse);
  free(ultimos);

  return 0;
}

