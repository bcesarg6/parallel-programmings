#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
    int nprocs; //holder for the number of cores
    int rank;   //holder for the ID number of this core

    // Initialise MPI
    MPI_Init(&argc, &argv);

    // Get the number of cores in the MPI cluster
    MPI_Comm_size( MPI_COMM_WORLD, &nprocs );

    // Get the ID number of this core in the MPI cluster
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    printf("I am process %d. The number of processes is %d.\n", rank, nprocs);

    // Shut down MPI
    MPI_Finalize();

    return 0;
} 