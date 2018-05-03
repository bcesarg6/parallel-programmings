/* Multiplicação de Matrizes com TBB */
/* Versão A : parallel-for	 */
/* Author: Bruno Cesar, bcesar.g6@gmail.com | 2018 */

#include "tbb/tbb.h"
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace tbb;
using namespace std;

#define SIZE 1000

int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];

/* Cada thread calcula uma linha da matriz */
/* Parametro l -> linha */
void matmul(size_t l){
	int r,i,c;
	r = 0;
	
	for(i = 0; i < SIZE; i++){
		for(c = 0; c < SIZE; c++){
			r += matA[l][c] * matB[c][i];

		}

		matC[l][i] = r;
		r = 0;
	}
}

void init(){
	int i,j;

	srand(time(NULL));

	for (i = 0; i < SIZE; i++){
		for (j = 0; j < SIZE; j++){
			matA[i][j] = (rand() % 3) + 1;;
			matB[i][j] = (rand() % 3) + 1;;
		}
	}

	cout << "This system has " <<  get_nprocs_conf() <<" processors configured and " << get_nprocs() <<" processors available.\n";
	int cpus = get_nprocs_conf();

 	int nDefThreads = tbb::task_scheduler_init::default_num_threads();
 	cout << "TBB configurado para " << nDefThreads << " threads paralelas." << endl;

 	tbb::task_scheduler_init init(2);
}

void printMat(int mat[SIZE][SIZE]){
	int i,j;

	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			cout << mat[i][j] << " ";	
		}

		cout << endl;
	}
}

int main(int argc, char const *argv[]){
	init();

	cout << endl << "PRINTANDO MATRIZ A: " << endl;
	printMat(matA);

	cout << endl << "PRINTANDO MATRIZ B: " << endl;
	printMat(matB);

	parallel_for<size_t>(0,SIZE,1,matmul);

	cout << endl << "PRINTANDO MATRIZ C: " << endl;
	printMat(matC);


	return 0;
}
