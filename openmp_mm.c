/* OPEN MP */
/* Código sequencial com partes paralelas atráves de diretivas de compilação */
/* #pragma omp parallel for        */
/* #pragma omp parallel section    */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

/* Dados globais */
int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];

void printMat(int mat[SIZE][SIZE]){
    int i,j;

    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%d ",mat[i][j]);   
        }

        printf("\n");
    }
}

/* Inicializa os dados (preenche as matrizes) */
void init(){
    int i,j;

    srand(time(NULL));

    #pragma omp for
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            matA[i][j] = (rand() % 3) + 1;
            matB[i][j] = (rand() % 3) + 1;
        }
    }

    if(SIZE < 5) {
        printf("Printando a matriz A\n");
        printMat(matA);

        printf("Printando a matriz B\n");
        printMat(matB);
    }
}

void matmul(){
	int i, j, k, thread_id, nloops;

    #pragma omp parallel private(thread_id, nloops)
	{
		nloops = 0;

		#pragma omp for
		for(i = 0; i < SIZE; i++){

			for(j = 0; j < SIZE; j++){
					matC[i][j] = 0;
			
				for(k = 0; k < SIZE; k++){
					matC[i][j] += matA[i][k] * matB[k][j];
					nloops++;

				}	
			}

		}

		thread_id = omp_get_thread_num();

        printf("Thread %d performed %d iterations of the loop.\n", thread_id, nloops);
		
	}
}


int main(int argc, char **argv){
	printf("Mat mul OPEN MP\n");

	init();
	matmul();

	if(SIZE < 5) {
        printf("Printando a matriz C\n");
        printMat(matC);
    }

	printf("\nFim da execução\n");

	return 0;
}
