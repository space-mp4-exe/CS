#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    // Catch console errors
    if (argc != 10)
    {
        printf("USE LIKE THIS: pingpong_MPI n_items time_prob1_MPI.csv\n");
        return EXIT_FAILURE;
    }

    /* Read in command line items */
    int n_items = strtol(argv[1], NULL, 10);
    FILE* outputFile = fopen(argv[2], "w");

    /* Start up MPI */
    int my_rank;
    // TODO: finish setting up MPI


    // Start time
    double starttime;
    starttime = MPI_Wtime();




    // TODO: Create your MPI program.
    if (my_rank == 0) {
    
        // Fill array with incremental values
        for (i = 0; i < n_items; i++)
            ping_array[i] = i;

        // TODO: if myrank is 0



        // End time
        double endtime = MPI_Wtime();
        // TODO: output
    }
    else {

        // TODO: if my rank not 0

    }

    return 0;
} /* main */

