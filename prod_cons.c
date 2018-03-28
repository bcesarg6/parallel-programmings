/* Produtor consumidor (PC 2018)    */
/* Bruno Cesar, bcesar.g6@gmail.com */
/* -------------------------------- */
/* 1. Buffer circular inteiro -> B  */
/* 2. P - Produtores		    	*/
/* 3. C - Consumidores				*/
/* Problema */
/* Cada produtor e consumidor possui uma matriz local:
1. Cada um deve preencher aleatoriamente sua matriz
2. Os produtores devem calcular o determinante da sua matriz e armazenar no buffer
3. Os consumidores devem ler o buffer e somar o valor a sua matriz

Versão A: Buffer exclusivo (Usa Lock)
Versão B: Buffer não exclusivo -> Trabalhar com o buffer de modo a melhor utiliza-lo (semaforos)

3 semaforos : SP (produtores) & SC (consumidores) & SE (semaforo binario na versão A)
SP é inicilizado com P
SC é inicializado com 0 (nada foi produzido ainda)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <getopt.h>

#define SIZE 512 // Tamanho do problema

static int n_prods;
static int n_cons;
static int tam_buffer;

sem_t sp;
sem_t sc;
sem_t se;

/* Exibe ajuda e finaliza o programa */
void help(){
	printf("\nPrograma Produtor & Consumidor\n 
		p : Número de produtores\n
		c : Número de consumidores\n
		b : Tamanho do buffer\n
		v : versão <0 : A | 1 : B>\n
		\n");

	exit(1);
}

/* Pega argumentos com getopt */
void getArgs(int argc, char *argv[]){
	extern char *optarg;
	char op;

	if(argc < 4){
		help();
	}

	struct option longopts[] = {
    {"produtores", 1, NULL, 'p'},
    {"consumidores", 1, NULL, 'c'},
	{"buffer",1, NULL, 'b'}
	};

	while ((op = getopt_long(argc, argv, "p:c:b:", longopts, NULL)) != -1) {
		switch (op) {
			case 'p':
				n_prods = atoi(optarg);
				break;

			case 'c':
				n_cons = atoi(optarg);
				break;

			case 'b':
				tam_buffer = atoi(optarg);
				break;

		

}

/* Checa se os parametros são validos, aborta caso não sejam */
void checkData(){
	if (n_prods < 1){
		printf("Numero de produtores inválido. Abortando...\n");
		exit(1);
	}

	if (n_cons < 1){
		printf("Numero de consumidores inválidos. Abortando...\n");
		exit(1);
	}

	if(tam_buffer < 1){
		printf("Tamanho do buffer invalido. Abortando...\n");
		exit(1);
	}

}

/* Metodo do produtor */
static void *produzir(){
	time_t time;
	/* Intializes random number generator */
    srand((unsigned) time(&time));

    

}

/* Metodo do consumidor */
static void *consumir(){
}


int main(int argc, char *argv[]){
	printf("Iniciando execução...\n");

	getArgs();
	checkData();
	printf("Argumentos lidos\n");

	int thread_status; //
	int i;

	//semaforos
	sem_init(&sp, 0, n_prods);
	sem_init(&sc, 0, 0);
	sem_init(&se, 0, 1);	

	printf("Semaforos inicializados\n");

	//threads
	pthread_t produtores[n_prods];
	pthread_t consumidores[n_cons];	

	printf("\n --- Lançando threads produtoras --- \n");
	for(i = 0; i < n_prods; i++){
		thread_status = pthread_create(&produtores[i], NULL, produzir, NULL);
        if (thread_status){
            printf("ERROR: retorno de pthread_create() é %d\n", thread_status);
            exit(-1);
        }
	}

	printf("\n --- Lançando threads consumidoras --- \n");
	for(i = 0; i < n_cons; i++){
		thread_status = pthread_create(&consumidores[i], NULL, consumir, NULL);
        if (thread_status){
            printf("ERROR: retorno de pthread_create() é %d\n", thread_status);
            exit(-1);
        }
	}
	
	

}


