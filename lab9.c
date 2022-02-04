#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS  5

// Variaveis globais
int contadorThreadsExecutadas = 0;    
sem_t primeiro_semaforo, segundo_semaforo;     

void *PrimeiraThread (void *threadid) {
  sem_wait(&segundo_semaforo); 
  printf("Volte sempre!\n");
  
  pthread_exit(NULL);
}

void *SegundaThread (void *threadid) {
  sem_wait(&primeiro_semaforo); 
  
  printf("Fique a vontade!\n");
  contadorThreadsExecutadas++;
  
  sem_post(&primeiro_semaforo);
  if(contadorThreadsExecutadas == 4){
  	sem_post(&segundo_semaforo);
  } 
  
  pthread_exit(NULL);
}

void *TerceiraThread (void *threadid) {
  sem_wait(&primeiro_semaforo); 
  
  printf("Sente-se por favor!\n");
  contadorThreadsExecutadas++;
  
  sem_post(&primeiro_semaforo);
  if(contadorThreadsExecutadas == 4){
  	sem_post(&segundo_semaforo);
  } 
  
  pthread_exit(NULL);
}

void *QuartaThread (void *threadid) {
  sem_wait(&primeiro_semaforo);
   
  printf("Aceita um copo d'água?!\n");
  contadorThreadsExecutadas++;
  
  sem_post(&primeiro_semaforo);
  if(contadorThreadsExecutadas == 4){
  	sem_post(&segundo_semaforo);
  } 
  
  pthread_exit(NULL);
}

void *QuintaThread (void *threadid) {
  printf("Seja bem-vindo!\n");
  contadorThreadsExecutadas++;
  
  sem_post(&primeiro_semaforo); 
  
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t tid[NTHREADS];
  int t; 

  sem_init(&primeiro_semaforo, 0, 0);
  sem_init(&segundo_semaforo, 0, 0);

  if (pthread_create(&tid[4], NULL, PrimeiraThread, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[0], NULL, SegundaThread, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, TerceiraThread, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[2], NULL, QuartaThread, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[3], NULL, QuintaThread, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  
  //--espera todas as threads terminarem
  for (t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  } 
  
  pthread_exit(NULL);
}
