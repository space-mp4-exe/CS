#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <omp.h>

#define DEBUG 0

/* ----------- Project 2 - Problem 1 - Matrix Mult -----------

    This file will multiply two matricies.
    Complete the TODOs in order to complete this program.
    Remember to make it parallelized!
*/ // ------------------------------------------------------ //

int main(int argc, char* argv[])
{
    // Catch console errors
    if (argc != 10)
    {
        printf("USE LIKE THIS: parallel_mult_mat_mat file_A.csv n_row_A n_col_A file_B.csv n_row_B n_col_B result_matrix.csv time.csv num_threads \n");
        return EXIT_FAILURE;
    }

    // Get the input files
    FILE* inputMatrix1 = fopen(argv[1], "r");
    FILE* inputMatrix2 = fopen(argv[4], "r");

    char* p1;
    char* p2;

    // Get matrix 1's dims
    int n_row1 = strtol(argv[2], &p1, 10);
    int n_col1 = strtol(argv[3], &p2, 10);

    // Get matrix 2's dims
    int n_row2 = strtol(argv[5], &p1, 10);
    int n_col2 = strtol(argv[6], &p2, 10);

    // Get num threads
    int thread_count = strtol(argv[9], NULL, 10);

    // Get output files
    FILE* outputFile = fopen(argv[7], "w");
    FILE* outputTime = fopen(argv[8], "w");


    // TODO: malloc the two input matrices and the output matrix
    // Please use long int as the variable type

    // TODO: Parse the input csv files and fill in the input matrices


    // We are interesting in timing the matrix-matrix multiplication only
    // Record the start time
    double start = omp_get_wtime();
    
    // TODO: Parallelize the matrix-matrix multiplication

    // Record the finish time        
    double end = omp_get_wtime();
    
    // Time calculation (in seconds)
    double time_passed = end - start;

    // Save time to file
    fprintf(outputTime, "%f", time_passed);

    // TODO: save the output matrix to the output csv file

    // Cleanup
    fclose(inputMatrix1);
    fclose(inputMatrix2);
    fclose(outputFile);
    fclose(outputTime);
    // Remember to free your buffers!

    return 0;
}

