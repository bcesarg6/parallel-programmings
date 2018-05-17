#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 1024

static int vec[SIZE];

/* Printa o vetor */
void printVec(int pVec[SIZE]){
    int i;

    if(SIZE > 20){
        printf("Too big to print :)\n");
        return;
    }

    printf("Vetor: ");
    for(i = 0; i < SIZE; i++)
        printf("%d ", pVec[i]);

    printf("\n");  
}

/* Popula aleatoriamente o vetor */
void init(){
    int i;
    srand(time(NULL));

    for (i = 0; i < SIZE; i++){
        vec[i] = rand() % SIZE + 1;
    }
}

void check(int vec[SIZE]){
    int i;
    int check = 0;

    for(i = 0; i < SIZE - 1; i++){
        if(vec[i+1] < vec[i]){
            check = 1;
            break;
        }

    }

    if(check)
        printf("Vetor não ordenado!\n");
    else
        printf("Vetor ordenadinho bunitinho\n");
    
}

void sort(){
    int i,j;
    int min_val, aux, pos; 

    for(i = 0; i < SIZE; i++){

        min_val = SIZE + 2;

        #pragma omp parallel for reduction(min : min_val)
        for (j = i; j < SIZE; j++){

            if(vec[j] < min_val){
                min_val = vec[j];
            }
        }

        //printf("Menor valor = %d\n", min_val);

        pos = 0;
        for(j = i; j  < SIZE; j++){
            if(vec[j] == min_val)
                pos = j;
        }

        aux = vec[i];
        vec[i] = min_val;
        vec[pos] = aux;
    }
}

int main(int argc, char **argv){
    init();
    printVec(vec);
    check(vec);    
    sort();
    printVec(vec);
    check(vec);

    return 0;
}