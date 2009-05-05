#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <semaphore.h>
#include <limits.h>

/*#include <linux/futex.h>
  #include <sys/syscall.h>      Não sei se vou usar futex...*/

/*
/* Retorna -1 se o futex não bloqueou e 
            0 caso contrário *
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Retorna o número de threads que foram acordadas *
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}
*/


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
sem_t fila_desembarque

/*Guardam quantos passageiros (des)embarcaram no carro*/
volatile int embarcaram;
volatile int desembarcaram;

/*Semaforos que indicam se o carro encheu ou esvaziou*/
sem_t carro_encheu;
sem_t carro_esvaziou;

/*Mutexes que controlam o (des)embarque de um único passageiro por vez*/
mutex_t trava_passageiros_embarque; 
mutex_t trava_passageiros_desembarque;

/*----------------------------------------*/



/* ----Funcoes que serao utilizadas pelos carros---- */

/*Funcao principal que controla os carros*/
void* Carro(void *id) {
  /*Por enquanto é isso que planejo para os carros, espero que tenha exclusão mutua e sem deadlock*/
  /*
  while(1){
    sem_wait(plataforma_embarque[id]);
    carrega();
    sem_post(fila_de_embarque); /*Tem que dar post LIMITE_CARRO vezes*
    sem_wait(carro_encheu);
    sem_post(plataforma_embarque[proximo(id)]);
    passeia();
    sem_wait(plataforma_desembarque[id]);
    descarrega();
    sem_post(fila_desembarque); /*Tem que dar post LIMITE_CARRO vezes*
    sem_wait(carro_esvaziou);
    sem_post(plataforma_desembarque[proximo(id)]);
  }
  */
  return NULL;
}

/*Calcula qual eh o proximo carro*/
int proximo(int id) {
  return ( (id+1) % N_CARROS);
}

/*Carrega o carro com passageiros*/
void* carrega(void *v) {
  

  return NULL;
}

/*Descarrega o carro*/
void* descarrega(void *v) {
  

  return NULL;
}

/*O carro passeia pelos trilhos*/
void* passeia(void *v) {
      sleep(rand() % 5);
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
  mutex_lock(trava_passageiros_embarque);
    embarcaram += 1;
    if (embarcaram == LIMITE_CARRO){
      sem_post(carro_encheu);
      embarcaram = 0;
    }
  mutex_unlock(trava_passageiros_embarque);

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

