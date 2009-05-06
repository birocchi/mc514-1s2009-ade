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

/*----------------------------------------*/



/* ----Funcoes que serao utilizadas pelos carros---- */

/*Calcula qual eh o proximo carro*/
int proximo(int id) {
  return ( (id+1) % N_CARROS);
}

/*Carrega o carro com passageiros*/
void* carrega() {

  return NULL;
}

/*Descarrega o carro*/
void* descarrega() {

  return NULL;
}

/*O carro passeia pelos trilhos*/
void* passeia() {
      sleep(rand() % 5);
  return NULL;
}

/*Funcao principal que controla os carros*/
void* Carro(void *v) {
  /*Por enquanto é isso que planejo para os carros, espero que tenha exclusão mutua e sem deadlock*/
  
  int k;
  int id = (int) v;
  while(1){
    sem_wait(&plataforma_embarque[id]);
    carrega();
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_embarque);
    sem_wait(&carro_encheu);
    sem_post(&plataforma_embarque[proximo(id)]);
    passeia();
    sem_wait(&plataforma_desembarque[id]);
    descarrega();
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_desembarque);
    sem_wait(&carro_esvaziou);
    sem_post(&plataforma_desembarque[proximo(id)]);
  }
  
  return NULL;
}

/*---------------------------------------------------*/



/* ----Funcoes que serao utilizadas pelos passageiros---- */

/*Função principal que controla os passageiros*/
void* Passageiro(void *v) {
/*Por enquanto é isso que planejo para os passageiros, espero que tenha exclusão mutua e sem deadlock*/
/*
  sem_wait(fila_embarque);
  embarcar();
  pthread_mutex_lock(trava_passageiros_embarque);
    embarcaram += 1;
    if (embarcaram == LIMITE_CARRO){
      sem_post(carro_encheu);
      embarcaram = 0;
    }
  pthread_mutex_unlock(trava_passageiros_embarque);

  sem_wait(fila_desembarque);
  desembarcar();
  mutex_lock(trava_passageiros_desembarque);
    desembarcaram += 1;
    if (desembarcaram == LIMITE_CARRO){
      sem_post(carro_esvaziou);
      desembarcaram = 0;
    }
  mutex_unlock(trava_passageiros_desembarque);
*/
  return NULL;
}

/*Embarca o passageiro*/
void* embarcar(void *v) {
  

  return NULL;
}

/*Desembarca o passageiro*/
void* desembarcar(void *v) {
  

  return NULL;
}
/*------------------------------------------------------- */



/* Função para a realizar a animacao */
void* Animacao(void *v) {
  

  return NULL;
}


int main() {

  /*Apenas cria Threads e espera elas terminarem a execução*/
  /*Cada passageiro e cada carro tem 1 thread e mais 1 thread para animacao*/

  return 0;
}

