/* Multiplicação de Matrizes com MPI               */
/* Author: Bruno Cesar, bcesar.g6@gmail.com | 2018 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

/* Dados globais */
int matA[SIZE * SIZE];
int matB[SIZE * SIZE];
int matC[SIZE * SIZE];

int workload;

/* Dados MPI */
int nprocs; //holder for the number of cores
int tid;   //holder for the tID number of this core
int stop;
int start;


void printMat(int mat[SIZE * SIZE]){
    int i,j;

    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%d ",mat[i * SIZE + j]);   
        }

        printf("\n");
    }
}

/* Cada thread calcula um conjunto de linhas da matriz */
void matmul(){
    int r,i,c,l;
    r = 0;
    
    for (l = start; l < stop; l++){
        for(i = 0; i < SIZE; i++){
            for(c = 0; c < SIZE; c++){
                r += matA[l * SIZE + c] * matB[c * SIZE + i];

            }

            matC[l * SIZE + i] = r;
            r = 0;
        }
    }

    if(SIZE < 5) {
        printf("O processo %d (START = %d E STOP = %d ) vai printar:\n", tid,start,stop);
        printMat(matC);
    }
}


/* Inicializa os dados (preenche as matrizes) */
void init(){
    int i,j;

    srand(time(NULL) + tid);

    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            matA[i * SIZE + j] = (rand() % 3) + 1;
            matB[i * SIZE + j] = (rand() % 3) + 1;
        }
    }

    printf("Numero de processos: %d\n", nprocs);
    printf("Cada processo irá calcular %d%% da matriz!\n", workload * 100 / SIZE);

    if(SIZE < 5) {
        printf("Printando a matriz A\n");
        printMat(matA);

        printf("Printando a matriz B\n");
        printMat(matB);
    }
}

int main(int argc, char **argv){
    int status, i;

    // Initialise MPI
    MPI_Init(&argc, &argv);

    // Get the number of cores in the MPI cluster
    MPI_Comm_size( MPI_COMM_WORLD, &nprocs );

    // Get the tID number of this core in the MPI cluster
    MPI_Comm_rank( MPI_COMM_WORLD, &tid );

    /* Configuração para paralelização */
    workload = SIZE / nprocs;
    start = tid * workload;
    stop = start + workload;

    /* Somente o processo 0 inicializa os dados */
    if(tid != 0){
        /* Os demais processos esperam os dados */
        MPI_Recv( matA, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, 0 );
        MPI_Recv( matB, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, 0 );
    } else {

        init();
        
        for (i = 1; i < nprocs; i++){
            MPI_Send( matA, SIZE * SIZE, MPI_INT, i, 0, MPI_COMM_WORLD );
            MPI_Send( matB, SIZE * SIZE, MPI_INT, i, 0, MPI_COMM_WORLD );
        }
    }

    matmul();

    /* Os processos diferentes de 0 irão enviar os dados calculados para o processo 0 */
    if(tid != 0){
        MPI_Send( matC + start * SIZE, workload * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD );
    } else {

        for (i = 1; i < nprocs; i++){
            MPI_Recv( matC + (i * workload * SIZE), workload * SIZE, MPI_INT, i, 0, MPI_COMM_WORLD, 0);
        }

        printf("O processo 0 -> Printando a matriz C = A * B\n");
        printMat(matC);
    }

    // Shut down MPI
    MPI_Finalize();

    return 0;
}
