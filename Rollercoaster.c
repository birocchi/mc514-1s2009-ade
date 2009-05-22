#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <semaphore.h>
#include <limits.h>

/* ----Definicoes----*/
#define N_CARROS 5
#define N_PASSAGEIROS 50
#define LIMITE_CARRO 5
/*-------------------*/


/* ----Declaração de variaveis globais---- */

/* Vetor que contem os semaforos de cada carro:
 * - Na area de embarque
 * - Na area de desembarque*/
sem_t plataforma_embarque[N_CARROS];
sem_t plataforma_desembarque[N_CARROS];

/*Semaforos que controlam a fila de (des)embarque dos passageiros*/
sem_t fila_embarque;
sem_t fila_desembarque;

/*Guardam quantos passageiros (des)embarcaram no carro*/
volatile int embarcaram;
volatile int desembarcaram;

/*Semaforos que indicam se o carro encheu ou esvaziou*/
sem_t carro_encheu;
sem_t carro_esvaziou;

/*Mutexes que controlam o (des)embarque de um único passageiro por vez*/
pthread_mutex_t trava_passageiros_embarque;
pthread_mutex_t trava_passageiros_desembarque;

/*Semaforo que indica que alguem esta imprimindo a animacao*/
sem_t imprime_animacao;

/*Vetor que contem os estados de cada passageiro*/
typedef enum {AUSENTE, FILA, EMBARCANDO, DESEMBARCANDO, SAIDA} estado_p;
estado_p estado_passageiros[N_PASSAGEIROS];

/*Vetor que contem os estados de cada carro*/ 
typedef enum { PASSEANDO, CARREGANDO, SAINDO, DESCARREGANDO, ESPERANDO } estado_c;
estado_c estado_carros[N_PASSAGEIROS];

/*----------------------------------------*/



/* ----Funcoes que serao utilizadas pelos carros---- */

/*Calcula qual eh o proximo carro*/
int proximo(int id) {
  return ( (id+1) % N_CARROS);
}

/*Carrega o carro com passageiros*/
void* carregar() {
  sleep(rand() % 3);
  return NULL;
}

/*Descarrega o carro*/
void* descarregar() {
  sleep(rand() % 3);
  return NULL;
}

/*O carro passeia pelos trilhos*/
void* passeia() {
  sleep(rand() % 3);
  return NULL;
}

/*Funcao principal que controla os carros*/
void* Carro(void *v) {

  int k;
  int id = (int) v;
  while(1){
    printf("Carro %d esta pronto para sair.\n",id);
    sem_wait(&plataforma_embarque[id]);
    carregar();
    printf("Carro %d esta carregando.\n",id);
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_embarque);
    sem_wait(&carro_encheu);
    printf("Carro %d terminou de carregar.\n",id);
    sem_post(&plataforma_embarque[proximo(id)]);
    passeia();
    printf("Carro %d esta passeando.\n",id);
    sem_wait(&plataforma_desembarque[id]);
    descarregar();
    printf("Carro %d voltou para a plataforma.\n",id);
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_desembarque);
    sem_wait(&carro_esvaziou);
    printf("Carro %d esvaziou.\n",id);
    sem_post(&plataforma_desembarque[proximo(id)]);
  }
  
  return NULL;
}

/*---------------------------------------------------*/



/* ----Funcoes que serao utilizadas pelos passageiros---- */

/*Embarca o passageiro*/
void* embarcar() {
  sleep(rand() % 3);
  return NULL;
}

/*Desembarca o passageiro*/
void* desembarcar() {
  sleep(rand() % 3);
  return NULL;
}

/*Função principal que controla os passageiros*/
void* Passageiro(void *v) {
  int id = (int) v;
  printf("Passageiro %d chegou.\n",id);
  sem_wait(&fila_embarque);
  embarcar();
  printf("Passageiro %d embarcou.\n",id);
  pthread_mutex_lock(&trava_passageiros_embarque);
    embarcaram += 1;
    if (embarcaram == LIMITE_CARRO){
      sem_post(&carro_encheu);
      embarcaram = 0;
    }
  pthread_mutex_unlock(&trava_passageiros_embarque);

  sem_wait(&fila_desembarque);
  desembarcar();
  printf("Passageiro %d desembarcou.\n",id);
  pthread_mutex_lock(&trava_passageiros_desembarque);
    desembarcaram += 1;
    if (desembarcaram == LIMITE_CARRO){
      sem_post(&carro_esvaziou);
      desembarcaram = 0;
    }
  pthread_mutex_unlock(&trava_passageiros_desembarque);
  printf("Passageiro %d foi embora.\n",id);
  return NULL;
}

/*------------------------------------------------------- */



/* Função para realizar a animacao */
void* Animacao() {
  
  return NULL;
}


int main() {

  /*Vetores de threads de passageiros e carros*/
  pthread_t passageiro[N_PASSAGEIROS];
  pthread_t carro[N_PASSAGEIROS]; 
  pthread_t animacao;

  int i;
  
  /*Inicializa os semaforos comuns*/
  sem_init(&fila_embarque,0,0);
  sem_init(&fila_desembarque,0,0);
  sem_init(&carro_encheu,0,0);
  sem_init(&carro_esvaziou,0,0);
  sem_init(&imprime_animacao,0,1);

  /*Inicializa os vetores de semaforos*/
  sem_init(&plataforma_embarque[0],0,1);
  for(i=1;i < N_CARROS; i++)
    sem_init(&plataforma_embarque[i],0,0);
  sem_init(&plataforma_desembarque[0],0,1);
  for(i=1;i < N_CARROS; i++)
    sem_init(&plataforma_desembarque[i],0,0);

  /*Cria a animacao*/
  if(pthread_create(&animacao, NULL, Animacao, NULL))
    printf("Erro ao criar a animacao!\n");

  /*Cria os carros*/
  for (i = 0; i < N_CARROS; i++) 
    if(pthread_create(&carro[i], NULL, Carro, (void*) i))
      printf("Erro ao criar carro!\n");

  /*Cria os passageiros*/
  for (i = 0; i < N_PASSAGEIROS; i++) 
    if(pthread_create(&passageiro[i], NULL, Passageiro, (void*) i))
      printf("Erro ao criar passageiro!\n");

  /*Espera os passageiros terminarem*/
  for (i = 0; i < N_PASSAGEIROS; i++) 
    if(pthread_join(passageiro[i], NULL))
      printf("Erro ao esperar o passageiro!\n"); 

  /*Mata as threads de carro*/ 
  /*Mata a thread de animacao*/

  return 0;
}

