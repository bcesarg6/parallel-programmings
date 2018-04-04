/* Problema RB_SOR */
/* Author: Bruno Cesar, bcesar.g6@gmail.com | 2018 */
/* omega = 0.25 */
/* calc : p[i,j] = (p[i-1,j] + p[i+1, j] + p[i, j - 1] + p[i, j + 1] ) / 4 * omega */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>

static int its;
static int num_threads;
static int size;

static pthread_barrier_t barreira;
static float* board;

/* Utils */
void printBoard(){
	int i,j;

	/* Printa o tabuleiro */
    for(i = 0; i < size; i++){
    	printf("[ ");

    	for(j = 0; j < size; j++){
    		printf("%f,", board[i,j]);
    	}

    	printf(" ]\n");
    }
}

/* Exibe ajuda e finaliza o programa */
void help(){
	printf("\nRB_SOR\n 
		i : Número de iterações do programa\n
		n : Número de threads\n
		s : Tamanho do problema (Matriz)\n
		\n");

	exit(1);
}

/* Pega argumentos com getopt */
void getArgs(int argc, char *argv[]){
	extern char *optarg;
	char op;

	if(argc < 3){
		help();
	}

	struct option longopts[] = {
    {"iterations", 1, NULL, 'i'},
    {"threads", 1, NULL, 't'},
	{"size",1, NULL, 's'}
	};

	while ((op = getopt_long(argc, argv, "i:n:s:", longopts, NULL)) != -1) {
		switch (op) {
			case 'i':
				its = atoi(optarg);
				break;

			case 'n':
				num_threads = atoi(optarg);
				break;

			case 's':
				size = atoi(optarg);
				break;
			}
		}
}

/* Checa se os parametros são validos, aborta caso não sejam */
void checkData(){
	if (its < 1){
		printf("Numero de iterações inválido. Abortando...\n");
		exit(1);
	}

	if (num_threads < 1){
		printf("Numero de consumidores inválidos. Deve ser multiplo de 2 e maior que 1! Abortando...\n");
		exit(1);
	}

	if(size < 8 &&  size%2 == 0){
		printf("Tamanho do tabuleiro RB inválido. Deve ser multiplo de 2 e maior que 1! Abortando...\n");
		exit(1);
	}
}


/* Método principal */
static void *program(void* arg){
	int r_status;
	int* tid = (int*) arg;

	/* TODO TODO TODO */ 

	r_status = pthread_barrier_wait(&barrier);
	
	if(r_status == 0) {
		/* Se passar da barreira */
	}



}

int main(int argc, char *argv[]){
	time_t time;
	int i,j;

	printf("Iniciando execução...\n");

	getArgs();
	checkData();
	printf("Argumentos lidos\n");

	printf("\n --- Inicializando o tabuleiro RB --- \n");
	
	board = malloc(sizeof(float) * size);
    srand((unsigned) time(&time));

    /* Preenche o tabuleiro com valorea aleatórios */
    for(i = 0; i < size; i++){
    	for(j = 0; j < size; j++){
    		board[i][j] = rand() % size;
    	}
    }

    /* Se o tabuleiro for pequeno o suficiente printa ele */
    if (size < 128){
    	printBoard();
    	printf("\n");
    }

    printf("\n--- feito\n");

    printf("\n --- inicializando a barreira --- \n");
    pthread_barrier_init(&barreira, NULL, num_threads);

	printf("\n --- Lançando threads --- \n");

	//threads
	pthread_t threads[num_threads];
	void* pth_status;
	
	int* tids;
	tids = malloc(sizeof(int) * num_threads);

	for(i = 0; i < num_threads; i++){
		tids[i] = i;

		thread_status = pthread_create(&threads[i], NULL, program, &tids[i]);
        if (thread_status){
            printf("ERROR: retorno de pthread_create() é %d\n", thread_status);
            exit(-1);
        }
	}

	for(i = 0; i < num_threads; i++){

		thread_status = pthread_join(threads[i], &pth_status);
        if (thread_status){
            printf("ERROR: retorno de pthread_join() é %d\n", thread_status);
            exit(-1);
        }
	}

}