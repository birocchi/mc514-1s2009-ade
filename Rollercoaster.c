#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

/*#include <linux/futex.h>
  #include <sys/syscall.h>      N�o sei se vou usar futex...*/

/*
/* Retorna -1 se o futex n�o bloqueou e 
            0 caso contr�rio *
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Retorna o n�mero de threads que foram acordadas *
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}
*/
/* N�mero de vezes que uma thread deve entrar na regi�o cr�tica. */

/* ----Definicoes----*/
#define N_CARROS 5
#define N_PASSAGEIROS 50
/*-------------------*/


/* ----Declara��o de variaveis globais---- */

/* Vetor que contem os semaforos de cada carro:
 * - Na area de embarque
 * - Na area de desembarque*/
sem_t plataforma_embarque[N_CARROS];
sem_t plataforma_desembarque[N_CARROS];

/*Guardam quantos passageiros (des)embarcaram no carro*/
volatile int embarcaram;
volatile int desembarcaram;


/*----------------------------------------*/



/* ----Funcoes que serao utilizadas pelos carros---- */

/*Funcao principal que controla os carros*/
void* Carro(void *v) {
  

  return NULL;
}

/*Calcula qual eh o proximo carro*/
void* proximo(void *v) {
  

  return NULL;
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
      sleep(5);
  return NULL;
}
/*---------------------------------------------------*/



/* ----Funcoes que serao utilizadas pelos passageiros---- */

/*Fun��o principal que controla os passageiros*/
void* Passageiro(void *v) {
  

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



/* Fun��o para a realizar a animacao */
void* Animacao(void *v) {
  

  return NULL;
}

int main() {

  /*Apenas cria Threads e espera elas terminarem a execu��o*/

  return 0;
}

