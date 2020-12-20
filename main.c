#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define N 20

//Declarando as funções
void *usuario(void *num);
void dorme_aleatorio();
void leva_mochila_ate_B_e_volta();

//Declarando as variáveis globais
sem_t mutex;
sem_t mutex2;
int cont=0;
int contPostIt=1; 
int numUsers=0;
int i;

//Função dorme aleatório
void dorme_aleatorio(){
	 sem_wait(&mutex2);
	 sleep(1);
	
}

//Função leva mochila
void leva_mochila_ate_B_e_volta(){
	sem_wait(&mutex);
	sleep(1);
}

//Função colaPostIt
void ColaPostIt(){
	sleep(1);
}

//Thread usuário

void *usuario (void *num){
 while(1){
 dorme_aleatorio();
 sem_post(&mutex2);
 ColaPostIt();
 contPostIt++;
 if (contPostIt == N)
 {
 printf("mochila cheia\n");
 sem_post(&mutex);
 }
 }
} 


//Thread pombo
void *pombo() {
 while(1){
 for ( i=1; i<=N; i++)
 {
 printf("Adic. msg %d\n", i);
 }
 sem_wait(&mutex);
  leva_mochila_ate_B_e_volta();
  sem_post(&mutex);
  contPostIt = 1;
 
 }
} 

//main
int main() {
 //Declarando as variáveis da main
   int i=0;
   int numPombo=1;
 //Recebendo o número de usuários
   printf("Digite o número de usuarios da thread:\n");
   scanf("%d",&numUsers);
   int nUsers[numUsers]; 
   sem_t S[numUsers]; //inicializacao do semáforo
   sem_t S2[numUsers]; //inicializacao do semáforo
   pthread_t thread_id[numUsers],thread_id2; //identificadores das threads
 
 //Inicializando semáforo 1
   sem_init(&mutex,0,1);
   for(i=0;i<numUsers;i++)
      sem_init(&S[i],0,0);
      
 //Inicializando semáforo 2    
       sem_init(&mutex2,0,1);
   for(i=0;i<numUsers;i++)
      sem_init(&S2[i],0,0);
	
 //Criando thread 1 
   for(i=0;i<numUsers;i++)
   {
      pthread_create(&thread_id[i], NULL, usuario, &nUsers[i]);
   }
  // Criando thread 2
   pthread_create(&thread_id2, NULL, pombo, &numPombo);

   for(i=0;i<numUsers;i++)
   pthread_join(thread_id[i],NULL); //para fazer a junção das threads
    pthread_join(thread_id2,NULL); //para fazer a junção das threads
   return(0);
}
