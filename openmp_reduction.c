#include <stdio.h>
#include <omp.h>

#define SIZE 1024

int main(int argc, char **argv)
{
    int i;
    int private_nloops, nloops, nthreads, thread_id; 

    nloops = 0;

    #pragma omp parallel private(private_nloops, nthreads, thread_id) \
                         reduction(+ : nloops)
    {
        private_nloops = 0;

        #pragma omp for
        for (i=0; i<SIZE; ++i){
            ++private_nloops;
        }

        nthreads = omp_get_num_threads();
        thread_id = omp_get_thread_num();
        printf("Hello. I am thread %d out of a team of %d\n", thread_id, nthreads);
        printf("I've calculated %d iterations\n", private_nloops);

        /* Reduction step - reduce 'private_nloops' into 'nloops' */
        nloops = nloops + private_nloops;
    }

    printf("The total number of loop iterations is %d\n", nloops);

    return 0;
}