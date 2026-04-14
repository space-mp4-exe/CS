#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"

#define MAXLINE 25
#define DEBUG   0

// to read in file
float* read_input(FILE* inputFile, int n_items);
int cmpfloat(const void* a, const void* b);
// merge local arrays
float* merge_sorted(float* A, int m, float* B, int n);

/* Main Program -------------- */
int main (int argc, char *argv[])
{
    if( argc != 5)
    {
        printf("USE LIKE THIS: merge_sort_MPI n_items input.csv output.csv time.csv\n");
        return EXIT_FAILURE;
    }

    // input file and size
    FILE* inputFile = fopen(argv[2], "r");
    int  n_items = strtol(argv[1], NULL, 10);

    // Start MPI
    int my_rank, comm_size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int chunk_size = n_items / comm_size;

    // arrays to use
    float* global_arr = NULL;
    if (my_rank == 0) {
        global_arr = read_input(inputFile, n_items);
        fclose(inputFile);
    }

    // scatter array to processes
    float* local_arr = (float*)malloc(chunk_size * sizeof(float));
    MPI_Scatter(global_arr, chunk_size, MPI_FLOAT, local_arr, chunk_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    // get start time
    double local_start, local_finish, local_elapsed, elapsed;
    MPI_Barrier(MPI_COMM_WORLD);
    local_start = MPI_Wtime();


    // sort the local array on each process
    qsort(local_arr, chunk_size, sizeof(float), cmpfloat);


    // tree reduction to merge sorted arrays
    int current_size = chunk_size;
    for (int step = 1; step < comm_size; step *= 2){
        if (my_rank % (2 * step) == 0){
            float* recv_arr = (float*)malloc(current_size * sizeof(float));
            MPI_Recv(recv_arr, current_size, MPI_FLOAT, my_rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            float* merged = merge_sorted(local_arr, current_size, recv_arr, current_size);
            
            free(local_arr);
            free(recv_arr);
            local_arr = merged;
            current_size *= 2;
        } else if (my_rank % step == 0){
            int partner = my_rank - step;
            MPI_Send(local_arr, current_size, MPI_FLOAT, partner, 0, MPI_COMM_WORLD);
            free(local_arr);
            break;
        }
    }
    
    // get elapsed time
    local_finish  = MPI_Wtime();
    local_elapsed = local_finish-local_start;

    // send time to main process
    MPI_Reduce(
        &local_elapsed, 
        &elapsed, 
        1, 
        MPI_DOUBLE,
        MPI_MAX, 
        0, 
        MPI_COMM_WORLD
    );

    // Write output (Step 5)
    if (my_rank == 0) {
        FILE* outputFile = fopen(argv[3], "w");
        FILE* timeFile = fopen(argv[4], "w");

        for (int i = 0; i < n_items; i++) 
            fprintf(outputFile, "%f\n", local_arr[i]);

        fprintf(timeFile, "%f\n", elapsed);

        fclose(outputFile);
        fclose(timeFile);

        free(local_arr);
        free(global_arr);
    }


    MPI_Finalize();

    if(DEBUG) printf("Finished!\n");
    return 0;
} // End Main //

float* merge_sorted(float* A, int m, float* B, int n) {
    float* C = (float*)malloc((m + n) * sizeof(float));
    int i = 0, j = 0, k = 0;

    while (i < m && j < n) {
        if (A[i] < B[j]) {
            C[k++] = A[i++];
        } else {
            C[k++] = B[j++];
        }
    }

    while (i < m) C[k++] = A[i++];
    while (j < n) C[k++] = B[j++];

    return C;
} // Merge Sorted //

/* Read Input -------------------- */
float* read_input(FILE* inputFile, int n_items) {
    float* arr = (float*)malloc(n_items * sizeof(float));
    char line[MAXLINE] = {0};
    int i = 0;
    //char* ptr;
    while (fgets(line, MAXLINE, inputFile)) {
        sscanf(line, "%f", &(arr[i]));
        ++i;
    }
    return arr;
} // Read Input //



/* Cmp Int ----------------------------- */
// use this for qsort
// source: https://stackoverflow.com/questions/3886446/problem-trying-to-use-the-c-qsort-function
int cmpfloat(const void* a, const void* b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);
} // Cmp Int //
