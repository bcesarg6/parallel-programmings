/* Multiplicação de Matrizes */
/* Versão B : Tarefas 		 */
/* Author: Bruno Cesar, bcesar.g6@gmail.com | 2018 */

#include "tbb/tbb.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace tbb;
using namespace std;

#define SIZE 100000

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
	int i;
	init();

	cout << endl << "PRINTANDO MATRIZ A: " << endl;
	printMat(matA);

	cout << endl << "PRINTANDO MATRIZ B: " << endl;
	printMat(matB);

	for (int i = 0; i < count; ++i)
	{
		/* code */
	}

	cout << endl << "PRINTANDO MATRIZ C: " << endl;
	printMat(matC);


	return 0;
}
