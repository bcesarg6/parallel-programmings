/* Conta tres implementado com transações */
/* Author: Bruno Cesar, bcesar.g6@gmail.com | 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 4
#define SIZE 4000000

static int total;
static int* vetor;

static void *conta3_transactions(void *arg){
	int i;
	int* tid = (int*) arg;

	for(i = *tid * (SIZE / NUM_THREADS); i < (*tid + 1) * (SIZE / NUM_THREADS); i++){
		if(vetor[i] == 3){
			/* REGIÃO CRITICA */
			__transaction_atomic{
				total++;
			}
		}
	}	
}


int main(){
	clock_t begin, end;
	double time_spent;
	int i;

	total = 0;

	printf("Inicializando...\n");
	vetor = malloc(sizeof(int) * SIZE);
	srand(time(NULL));

	for(i = 0; i < SIZE; i++){
		vetor[i] = (rand() % 3) + 1;
		//printf("%d", vetor[i]);
	}

	//Threads and locks iniciatilization
	pthread_t threads[NUM_THREADS];
	void* pth_status;

	int* tids;
	tids = malloc(sizeof(int) * NUM_THREADS);

	for(i = 0; i < NUM_THREADS; i++){
		tids[i] = i;
	}

	printf("\nIniciando execução versão Transações\n");

	begin = clock();
	
	for(i = 0; i < NUM_THREADS; i++){
		pthread_create(&threads[i], NULL, conta3_transactions, &tids[i]);
        
	}

	for(i = 0; i < NUM_THREADS; i++){
		 pthread_join(threads[i], &pth_status); 
	}

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Versão TRANSACTIONS\ntotal de 3 = %d\ntempo: %lf\n", total, time_spent);

	return 0;
}