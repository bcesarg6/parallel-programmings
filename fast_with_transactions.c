/* Teste rápido */
/* Author: Bruno Cesar, bcesar.g6@gmail.com | 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 1000000

static int a;
static int b;
static int c;


static void *program(){
	int i;

	for(i = 0; i < ITERATIONS; i++){
		__transaction_atomic{
			++a;
			b += 2;
			c = a + b;
		}

	}
}

int main(){
	int i;
	a,b,c = 0;
	printf("Iniciando execução...\n");

	//threads
	pthread_t threads[NUM_THREADS];
	void* pth_status;
	
	for(i = 0; i < NUM_THREADS; i++){
		pthread_create(&threads[i], NULL, program, NULL);
        
	}

	for(i = 0; i < NUM_THREADS; i++){
		 pthread_join(threads[i], &pth_status); 
	}

	printf("saida:\n a = %d\n b = %d\n c = %d\n", a, b, c);

	return 0;
}