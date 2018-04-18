/* criar threads opacas -> thread trabalhadora                   */
/* thread gerente -> manda nas trabalhadoras.  				     */
/* BT = Bolsa de tarefas. Onde as gerentes colocam trabalhos     */
/* Autor:Bruno Cesar, @bcesarg6 bcesar.g6@gmail.com | Abril 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/* Estrutura para transporte de valores */
struct thread_arg{
	int in;
	int out;
} thread_arg;

typedef thread_arg* pthread_arg;

void (*funcs[4]) (void* arg);

static int size = 10;
static int num_threads = 2;

void* fibonacci(void* arg){
	pthread_arg parg = (pthread_arg) arg;
	int n,n2,aux,i;
	n = 1;
	n2 = 1;

	for(i = 0; i < parg->in; i++){
		aux = n2;
		n2 += n;
		n = aux;
	}

	parg->out = n;
}

void* fatorial(void* arg){
	pthread_arg parg = (pthread_arg) arg;
	int i,aux;
	aux = parg->in;

	for(i = parg->in - 1; i >= 1; i--){
		aux = aux * i;
	}

	parg->out = aux;

}

void* matMul(void* arg){
	pthread_arg parg = (pthread_arg) arg;
	int i,j, sum;
	int tam = parg->in * 10;
	int mat[tam][tam];
	sum = 0;

	//popula
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			mat[i][j] = i + j;
		}
	}

	//multiplica por in
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			mat[i][j] = mat[i][j] * parg->in;
			sum += mat[i][j];
		}
	}

	parg->out = sum;
} 

/* Pega argumentos com getopt */
void getArgs(int argc, char *argv[]){
	extern char *optarg;
	char op;

	struct option longopts[] = {
    {"size", 1, NULL, 's'},
    {"threads", 1, NULL, 't'}
	};

	while ((op = getopt_long(argc, argv, "s:t:h", longopts, NULL)) != -1) {
		switch (op) {
			case 's':
				size = atoi(optarg);
				break;

    	case 't':
      	num_threads = atoi(optarg);
      	break;

    	case 'h':
      	help(0);
      	break;

			default:
      	help(2);
      	break;
    	}
  }
}

/* Checa se os parametros são validos, aborta caso não sejam */
void checkData(){
	if (size < 1){
		printf("Tamanho da bolsa de tarefas inválido. Abortando...\n");
		exit(1);
	}

  if(num_threads < 1){
  	printf("Número inválido de threads. Abortando...\n");
  	exit(1);
	}
}

int main(int argc, char const *argv[]) {
  int i;
  printf("\nBolsa de tarefas!\n");

	getArgs(argc, argv);
	checkData();
	printf("Dados de execução:\n Problemas: lalalalala\n");
	printf("Tamanho da bolsa = %d | Número de threads = %d\n", size, num_threads);

	/* Popula o  
	funcs[0] = fibonacci;
	funcs[1] = fatorial;
	funcs[2] = matMul;

}
