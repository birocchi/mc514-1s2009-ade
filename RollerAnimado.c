#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

/*Semaforos que controlam a saida para o passeio*/
sem_t foi_passear;
sem_t prepararam_passeio;

/*Matriz com a imagem que eh impressa*/
char imagem[9][75];

/*Guardam quantos passageiros (des)embarcaram no carro*/
volatile int embarcaram;
volatile int prepara1,prepara2;
volatile int desembarcaram;

/*Semaforos que indicam se o carro encheu ou esvaziou*/
sem_t carro_encheu;
sem_t carro_esvaziou;

/*Mutexes que controlam o (des)embarque de um único passageiro por vez*/
pthread_mutex_t trava_passageiros_embarque;
pthread_mutex_t trava_preparacao1;
pthread_mutex_t trava_preparacao2;
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

/*Configura a matriz imagem com o estado inicial*/
void InicializaImagem(void){
  char imagem0[75] = "/                            Montanha Russa                           \\\n";
  char imagem1[75] = "|            |entrada|                                                |\n";
  char imagem2[75] = "|            |   #__________________________________________________  |\n";
  char imagem3[75] = "|            |   |\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/  |\n";
  char imagem4[75] = "|           |_____| |_____| |_____| |_____| |_____| |_____| |_____|   |\n";
  char imagem5[75] = "|           =o===o===o===o===o===o===o===o===o===o===o===o===o===o=---|\n";
  char imagem6[75] = "|                                                      |saida|   |    |\n";
  char imagem7[75] = "|                                                      |_________|    |\n";
  char imagem8[75] = "\\                                                                     /\n";

  strcpy(imagem[0], imagem0);
  strcpy(imagem[1], imagem1);
  strcpy(imagem[2], imagem2);
  strcpy(imagem[3], imagem3);
  strcpy(imagem[4], imagem4);
  strcpy(imagem[5], imagem5);
  strcpy(imagem[6], imagem6);
  strcpy(imagem[7], imagem7);
  strcpy(imagem[8], imagem8);
}

void ImprimeImagem(void){
  int i;
  for(i=0; i<9; i++)
    printf("%s",imagem[i]);
}

/* ----Função para realizar a animacao----*/
void* Animacao() {
  /*Variaveis que contam quantos passageiros estao num certo estado*/
  int quant_fila=0, quant_embarcando=0, quant_desembarcando=0, quant_saida=0;

  /*Variavel que conta quantos carros estão esperando na plataforma*/
  int quant_esperando=0, existe_carregando=0, existe_saindo=0, existe_descarregando=0;
  
  /* Contador/indexador */
  int i, j;

  /*Conta quantos estao na fila*/
  for(i=0;i < N_PASSAGEIROS;i++){
    if(estado_passageiros[i] == FILA)
      quant_fila++;
  }

  /*Conta quantos estao embarcando*/
  for(i=0;i < N_PASSAGEIROS;i++){
    if(estado_passageiros[i] == EMBARCANDO)
      quant_embarcando++;
  }

  /*Conta quantos estao na desembarcando*/
  for(i=0;i < N_PASSAGEIROS;i++){
    if(estado_passageiros[i] == DESEMBARCANDO)
      quant_desembarcando++;
  }

  /*Conta quantos estao na saida*/
  for(i=0;i < N_PASSAGEIROS;i++){
    if(estado_passageiros[i] == SAIDA)
      quant_saida++;
  }

  /*Conta quantos carros estao esperando*/
  for(i=0;i < N_CARROS;i++){
    if(estado_carros[i] == ESPERANDO)
      quant_esperando++;
  }

  /*Checa se existe um carro carregando*/
  for(i=0;i < N_CARROS;i++){
    if(estado_carros[i] == CARREGANDO)
      existe_carregando = 1;
  }

  /*Checa se existe um carro saindo*/
  for(i=0;i < N_CARROS;i++){
    if(estado_carros[i] == SAINDO)
      existe_saindo = 1;
  }

  /*Checa se existe um carro descarregando*/
  for(i=0;i < N_CARROS;i++){
    if(estado_carros[i] == DESCARREGANDO)
      existe_descarregando = 1;
  }

  /***** Primeira Linha *****/
  /**************************/

  /***** Segunda  Linha *****/
  /**************************/

  /***** Terceira Linha *****/
  for(i=0;i < N_PASSAGEIROS;i++)
    if(i < quant_fila)
       imagem[2][17+i] = 'o';
    else
       imagem[2][17+i] = '_';
  /**************************/

  /****** Quarta Linha ******/
  /**************************/

  /****** Quinta e Sexta Linhaa ******/
  /*carro saindo*/
  if(existe_saindo){
    imagem[4][3] = '|';
    imagem[5][4] = 'o';
    for(i=0;i<5;i++)
      imagem[4][4+i] = 'o';
    imagem[4][9] = '|';
    imagem[5][8] = 'o';
  }
  else{
    for(i=0;i<7;i++)
      imagem[4][3+i] = ' ';
    imagem[5][4] = '-';
    imagem[5][8] = '-';
  }

  /*carro sendo carregado*/
  if(existe_carregando){
    imagem[4][12] = '|';
    imagem[5][13] = 'o';
    for(i=0;i < LIMITE_CARRO;i++){
      if(i < quant_embarcando)
        imagem[4][13+i] = 'o';
      else
        imagem[4][13+i] = '_';
    }
    imagem[4][18] = '|';
    imagem[5][17] = 'o';
  }
  else{
    for(i=0;i<7;i++)
      imagem[4][12+i] = ' ';
    imagem[5][13] = '=';
    imagem[5][17] = '=';
  }
      
  /*outros carros*/
  for(i=0;i < N_CARROS;i++)
    if(i < quant_esperando){
       imagem[4][20+(i*8)] = '|';
       imagem[5][21+(i*8)] = 'o';
       for(j=0;j<LIMITE_CARRO;j++)
         imagem[4][(21+i*8)+j] = '_';
       imagem[4][26+(i*8)] = '|';
       imagem[5][25+(i*8)] = '0';
       imagem[4][27+(i*8)] = ' ';
    }
    else{
       for(j=0;j<LIMITE_CARRO+3;j++)
         imagem[4][(20+i*8)+j] = ' ';
       imagem[5][21+(i*8)] = '=';
       imagem[5][25+(i*8)] = '=';
    }

  /*carro descarregando*/
  if(existe_descarregando){
    imagem[4][53] = '|';
    for(i=0;i < LIMITE_CARRO;i++){
      imagem[5][54+i] = ' ';  
      if(i < quant_desembarcando)
       imagem[4][54+i] ='o';
      else
       imagem[4][54+i] ='_';
    }
    imagem[4][59] = '|';
    imagem[5][54] = 'o';
    imagem[5][58] = 'o';
  }
  else{
    for(i=0;i<LIMITE_CARRO+2;i++)
      imagem[4][53+i] = ' ';
      imagem[5][53+i] = '=';
  }

  /**************************/

  /****** Setima Linha ******/
  /**************************/

  /****** Oitava Linha ******/
  for(i=0;i < N_CARROS;i++){
    if(i < quant_saida)
        imagem[7][60+i] = 'o';
    else
        imagem[7][60+i] = '_';
  }

  /******* Nona Linha *******/
  /**************************/

  ImprimeImagem();

  return NULL;
}

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
  Animacao();
  printf("Carro %d esta carregando.\n\n\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*Descarrega o carro*/
void* descarregar(int id) {
  sem_wait(&mudando_estado);
  estado_carros[id] = DESCARREGANDO;
  Animacao();
  printf("Carro %d esta descarregando.\n\n\n",id);
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
    /*Primeiramente o carro espera a permissao para carregar*/
    sem_wait(&plataforma_embarque[id]);

    /*Se conseguir, o imprime na area de carregamento*/
    carregar(id);

    /*Permite a passagem de LIMITE_CARROS passageiros e espera encher*/
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_embarque);
    sem_wait(&carro_encheu);

    /*Imprime o carro saindo e desaparecendo*/
    sem_wait(&mudando_estado);
    estado_carros[id] = SAINDO;
    Animacao();
    printf("Carro %d esta saindo.\n\n\n",id);
    estado_carros[id] = PASSEANDO;
    Animacao();
    printf("Carro %d esta passeando.\n\n\n",id);
    /*Prepara LIMITE_CARROS passageiros para passear*/
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&foi_passear);
    sem_wait(&prepararam_passeio);
    sem_post(&mudando_estado);

    /*Permite que outro carro carregue e passeia*/
    sem_post(&plataforma_embarque[proximo(id)]);
    passeia();

    /*Espera a area de desembarque ficar livre*/
    sem_wait(&plataforma_desembarque[id]);

    /*Se ficou, prepara LIMITE_CARROS passageiros para desembarcar*/
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&chegou_plataforma);
    sem_wait(&prepararam_desembarque);

    /*Imprime o carro na area de desembarque*/
    descarregar(id);

    /*Libera a saida de LIMITE_CARROS passageiros e espera esvaziar*/
    for(k=0;k < LIMITE_CARRO; k++)
      sem_post(&fila_desembarque);
    sem_wait(&carro_esvaziou);

    /*Depois de esvaziar, volta a fila de espera*/
    sem_wait(&mudando_estado);
    estado_carros[id] = ESPERANDO;
    Animacao();
    printf("Carro %d esta esperando.\n\n\n",id);
    sem_post(&mudando_estado);

    /*Libera a plataforma de desembarque para outro carro*/
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
  Animacao();
  printf("Passageiro %d embarcou.\n\n\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*Desembarca o passageiro*/
void* desembarcar(int id) {
  sem_wait(&mudando_estado);
  estado_passageiros[id] = SAIDA;
  Animacao();
  printf("Passageiro %d desembarcou.\n\n\n",id);
  sem_post(&mudando_estado);
  sleep(rand() % 3);
  return NULL;
}

/*Função principal que controla os passageiros*/
void* Passageiro(void *v) {
  int id = (int) v;

  /*Para tornar mais real, os passageiros demoram um tempo aleatorio para surgir*/
  sleep(rand() % N_PASSAGEIROS);

  /*Mostra que o passageiro esta na fila*/
  sem_wait(&mudando_estado);
  estado_passageiros[id] = FILA;
  Animacao();
  printf("Passageiro %d esta na fila.\n\n\n",id);
  sem_post(&mudando_estado);

  /*O passageiro espera a entrada no carro*/
  sem_wait(&fila_embarque);
  
  /*Se esta for permitida, imprime o passageiro embarcando*/
  embarcar(id);

  /*Os passageiros vao entrando e avisam quando encher o carro*/
  pthread_mutex_lock(&trava_passageiros_embarque);
    embarcaram += 1;
    if (embarcaram == LIMITE_CARRO){
      sem_post(&carro_encheu);
      embarcaram = 0;
    }
  pthread_mutex_unlock(&trava_passageiros_embarque);

  /*Preparam os passageiros para o passeio*/
  sem_wait(&foi_passear);
  pthread_mutex_lock(&trava_preparacao1);
    estado_passageiros[id] = NOCARRO;
    prepara1 += 1;
    if (prepara1 == LIMITE_CARRO){
      sem_post(&prepararam_passeio);
      prepara1 = 0;
    }
  pthread_mutex_unlock(&trava_preparacao1);

  /*Prepara os passageiros para desembarcar*/
  sem_wait(&chegou_plataforma);
  pthread_mutex_lock(&trava_preparacao2);
    sem_wait(&mudando_estado);
    estado_passageiros[id] = DESEMBARCANDO;
    sem_post(&mudando_estado);
    prepara2 += 1;
    if (prepara2 == LIMITE_CARRO){
      sem_post(&prepararam_desembarque);
      prepara2 = 0;
    }
  pthread_mutex_unlock(&trava_preparacao2);

  /*Espera para poder desembarcar*/
  sem_wait(&fila_desembarque);

  /*Quando puder, imprime o passageiro na saida*/
  desembarcar(id);

  /*Os passageiros saem do carro e avisam quando ele esvaziar*/
  pthread_mutex_lock(&trava_passageiros_desembarque);
    desembarcaram += 1;
    if (desembarcaram == LIMITE_CARRO){
      sem_post(&carro_esvaziou);
      desembarcaram = 0;
    }
  pthread_mutex_unlock(&trava_passageiros_desembarque);

  /*O passageiro vai embora*/
  sem_wait(&mudando_estado);
  estado_passageiros[id] = AUSENTE;
  sem_post(&mudando_estado);
  return NULL;
}

/*------------------------------------------------------- */


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
  InicializaImagem();
  ImprimeImagem(); //PARA COMPARACAO APENAS!
  Animacao();
  printf("Imprimiu situacao inicial\n\n\n");

  /*Cria os carros*/
  for (i = 0; i < N_CARROS; i++) 
    if(pthread_create(&carro[i], NULL, Carro, (void*) i))
      printf("Erro ao criar carro!\n\n");

  /*Cria os passageiros*/
  for (i = 0; i < N_PASSAGEIROS; i++) 
    if(pthread_create(&passageiro[i], NULL, Passageiro, (void*) i))
      printf("Erro ao criar passageiro!\n\n");

  /*Espera os passageiros terminarem*/
  for (i = 0; i < N_PASSAGEIROS; i++) 
    if(pthread_join(passageiro[i], NULL))
      printf("Erro ao esperar o passageiro!\n\n"); 

  /*Espera os carros terminarem*/
  sleep(4);

  /*Mata as threads de carro*/ 

  return 0;
}

