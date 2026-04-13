#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

#define PING_PONG_TIMES 1000

int main(int argc, char* argv[]) {
    // Catch console errors
    if (argc != 3)
    {
        printf("USE LIKE THIS: pingpong_MPI n_items time_prob1_MPI.csv\n");
        return EXIT_FAILURE;
    }

    /* Read in command line items */
    int n_items = strtol(argv[1], NULL, 10);
    FILE* outputFile = fopen(argv[2], "w");

    /* Start up MPI */
    int my_rank;
    int n_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

    int* ping_array = (int*)malloc(n_items * sizeof(int));
    if (ping_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    // Start time
    double starttime;
    starttime = MPI_Wtime();




    if (my_rank == 0) {
    
        // Fill array with incremental values
        for (int i = 0; i < n_items; i++)
            ping_array[i] = i;

        for(int i = 0; i < PING_PONG_TIMES; i++) {
            MPI_Send(ping_array, n_items, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(ping_array, n_items, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }


        // End time
        double endtime = MPI_Wtime();
        double total_time = endtime - starttime;

        double avg_oneway = total_time / (2 * PING_PONG_TIMES);

        fprintf(outputFile, "n_items,total_time,avg_oneway_time\n");
        fprintf(outputFile, "%d, %f, %f\n", n_items, total_time, avg_oneway);
        fclose(outputFile);
        
        //printf("n_items: %d\n", n_items);
        //printf("Total time for %d ping-pongs: %.6f seconds\n", PING_PONG_TIMES, total_time);
        //printf("Average one-way trip time:    %.6f seconds\n", avg_oneway);
    } else {
        for (int i = 0; i < PING_PONG_TIMES; i++) {
            MPI_Recv(ping_array, n_items, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(ping_array, n_items, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    free(ping_array);
    MPI_Finalize();
    return 0;
} /* main */

