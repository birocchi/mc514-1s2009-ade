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

/*Semaforos que controlam a chegada na plataforma*/
sem_t chegou_plataforma;
sem_t prepararam_desembarque;

/*Guardam quantos passageiros (des)embarcaram no carro*/
volatile int embarcaram;
volatile int prepara;
volatile int desembarcaram;

/*Semaforos que indicam se o carro encheu ou esvaziou*/
sem_t carro_encheu;
sem_t carro_esvaziou;

/*Mutexes que controlam o (des)embarque de um único passageiro por vez*/
pthread_mutex_t trava_passageiros_embarque;
pthread_mutex_t trava_preparacao;
pthread_mutex_t trava_passageiros_desembarque;

/*Semaforo que indica que alguem esta mudando o estado e imprimindo a animacao*/
sem_t mudando_estado;

/*Vetor que contem os estados de cada passageiro*/
typedef enum {AUSENTE, FILA, EMBARCANDO, NOCARRO, DESEMBARCANDO, SAIDA} estado_p;
estado_p estado_passageiros[N_PASSAGEIROS];

/*Vetor que contem os estados de cada carro*/ 
typedef enum { PASSEANDO, CARREGANDO, SAINDO, DESCARREGANDO, ESPERANDO } estado_c;
estado_c estado_carros[N_CARROS];

/*----------------------------------------*/



/* ----Funcoes que serao utilizadas pelos carros---- */

/*Calcula qual eh o proximo carro*/
int proximo(int id) {
  return ( (id+1) % N_CARROS);
}

/*Carrega o carro com passageiros*/
void* carregar(int id) {
  sem_wait(&mudando_estado);
  estado_carros[id] = CARREGANDO;
//imprime
  printf("Carro %d esta carregando.\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*Descarrega o carro*/
void* descarregar(int id) {
  sem_wait(&mudando_estado);
  estado_carros[id] = DESCARREGANDO;
//imprime
  printf("Carro %d esta descarregando.\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*O carro passeia pelos trilhos*/
void* passeia() {
  /*O tempo do passeio varia entre 3 e 5 segundos*/
  sleep((rand() % 3) + 3);
  return NULL;
}

/*Funcao principal que controla os carros*/
void* Carro(void *v) {

  int k;
  int id = (int) v;

  while(1){

    sem_wait(&plataforma_embarque[id]);
    carregar(id);
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_embarque);
    sem_wait(&carro_encheu);

    sem_wait(&mudando_estado);
    estado_carros[id] = SAINDO;
//imprime
    printf("Carro %d esta saindo.\n",id);
    estado_carros[id] = PASSEANDO;
//imprime
    printf("Carro %d esta passeando.\n",id);
    sem_post(&mudando_estado);

    sem_post(&plataforma_embarque[proximo(id)]);
    passeia();

    sem_wait(&plataforma_desembarque[id]);

    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&chegou_plataforma);
    sem_wait(&prepararam_desembarque);

    descarregar(id);

    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_desembarque);
    sem_wait(&carro_esvaziou);

    sem_wait(&mudando_estado);
    estado_carros[id] = ESPERANDO;
//imprime
    printf("Carro %d esta esperando.\n",id);
    sem_post(&mudando_estado);

    sem_post(&plataforma_desembarque[proximo(id)]);
  }
  
  return NULL;
}

/*---------------------------------------------------*/



/* ----Funcoes que serao utilizadas pelos passageiros---- */

/*Embarca o passageiro*/
void* embarcar(int id) {
  sem_wait(&mudando_estado);
  estado_passageiros[id] = EMBARCANDO;
//imprime
  printf("Passageiro %d embarcou.\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*Desembarca o passageiro*/
void* desembarcar(int id) {
  sem_wait(&mudando_estado);
  estado_passageiros[id] = SAIDA;
//imprime
  printf("Passageiro %d desembarcou.\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*Função principal que controla os passageiros*/
void* Passageiro(void *v) {
  int id = (int) v;
  sleep(rand() % N_PASSAGEIROS);

  sem_wait(&mudando_estado);
  estado_passageiros[id] = FILA;
//imprime
  printf("Passageiro %d esta na fila.\n",id);
  sem_post(&mudando_estado);

  sem_wait(&fila_embarque);
  embarcar(id);
  pthread_mutex_lock(&trava_passageiros_embarque);
    embarcaram += 1;
    if (embarcaram == LIMITE_CARRO){
      sem_post(&carro_encheu);
      embarcaram = 0;
    }
  pthread_mutex_unlock(&trava_passageiros_embarque);

  sem_wait(&mudando_estado);
  estado_passageiros[id] = NOCARRO;
  sem_post(&mudando_estado);

  sem_wait(&chegou_plataforma);
  pthread_mutex_lock(&trava_preparacao);
    sem_wait(&mudando_estado);
    estado_passageiros[id] = DESEMBARCANDO;
    sem_post(&mudando_estado);
    prepara += 1;
    if (prepara == LIMITE_CARRO){
      sem_post(&prepararam_desembarque);
      prepara = 0;
    }
  pthread_mutex_unlock(&trava_preparacao);

  sem_wait(&fila_desembarque);
  desembarcar(id);
  pthread_mutex_lock(&trava_passageiros_desembarque);
    desembarcaram += 1;
    if (desembarcaram == LIMITE_CARRO){
      sem_post(&carro_esvaziou);
      desembarcaram = 0;
    }
  pthread_mutex_unlock(&trava_passageiros_desembarque);

  sem_wait(&mudando_estado);
  estado_passageiros[id] = AUSENTE;
  sem_post(&mudando_estado);
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

  int i;
  
  /*Inicializa os semaforos comuns*/
  sem_init(&fila_embarque,0,0);
  sem_init(&fila_desembarque,0,0);
  sem_init(&prepararam_desembarque,0,0);
  sem_init(&chegou_plataforma,0,0);
  sem_init(&carro_encheu,0,0);
  sem_init(&carro_esvaziou,0,0);
  sem_init(&mudando_estado,0,1);

  /*Inicializa os vetores de semaforos*/
  sem_init(&plataforma_embarque[0],0,1);
  for(i=1;i < N_CARROS; i++)
    sem_init(&plataforma_embarque[i],0,0);
  sem_init(&plataforma_desembarque[0],0,1);
  for(i=1;i < N_CARROS; i++)
    sem_init(&plataforma_desembarque[i],0,0);
  
  /*Todos os passageiros comecam no estado ausente*/
  for(i=0;i < N_PASSAGEIROS;i++)
    estado_passageiros[i] = AUSENTE;

  /*Todos os carros comecam no estado esperando*/
  for(i=0;i < N_CARROS;i++)
    estado_carros[i] = ESPERANDO;

  /*Imprime a situacao inicial da animacao*/
  Animacao();
  printf("Imprimiu situacao inicial\n");

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

  return 0;
}

