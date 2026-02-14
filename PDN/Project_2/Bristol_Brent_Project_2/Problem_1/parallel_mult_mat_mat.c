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
    long int *matrixA = (long int *)malloc(n_row1 * n_col1 * sizeof(long int));
    long int *matrixB = (long int *)malloc(n_row2 * n_col2 * sizeof(long int));
    long int *output = (long int *)malloc(n_row1 * n_col2 * sizeof(long int));

    // Parse the input CSV files
    // first it puts part of the file into an input buffer
    // Tokens are then parsed from that buffer and put into the matrix
    char line[1024];// char array to buffer file input
    int index = 0;
    // inserting information into matrix
    while(fgets(line, 1024, inputMatrix1)){
        char* token;
        token = strtok(line, ",");
        while(token != NULL && index < n_row1 * n_col1){
            long int value;
            //char* endptr;

            value = strtol(token, NULL, 10); //convert parsed token to an int
            matrixA[index] = value;
            index++; //increment index of matrix
            token = strtok(NULL, ","); //token takes on next value in row
        }
    }

    // inserting information into vector
    index = 0; // resetting index for the new array
    while(fgets(line, 1024, inputMatrix2)){
        char* token;
        token = strtok(line, ",");
        while(token != NULL && index < n_row2 * n_col2){
            long int value;
            //char* endptr;

            value = strtol(token, NULL, 10);
            matrixB[index] = value;
            index++;
            token = strtok(NULL, ",");
        }
    }

    // We are interesting in timing the matrix-matrix multiplication only
    // Record the start time
    double start = omp_get_wtime();
    
    // TODO: Parallelize the matrix-matrix multiplication
#   pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < n_row1; i++) {
        for (int j = 0; j < n_col2; j++) {
            output[i * n_row1 + j] = 0;

            for (int k = 0; k < n_row2; k++) {
                output[i * n_row1 + j] += matrixA[i * n_row1 + k] * matrixB[k * n_col2 + j];
            }
        }
    }

    // Record the finish time        
    double end = omp_get_wtime();
    
    // Time calculation (in seconds)
    double time_passed = end - start;

    // Save time to file
    fprintf(outputTime, "%f", time_passed);

    // TODO: save the output matrix to the output csv file
    for (int i = 0; i < n_row1; i++){
        for(int j = 0; j < n_col2; j++){
            fprintf(outputFile, "%ld, ", output[i * n_row1 + j]);
        }
        fprintf(outputFile, "\n"); //end of row, move to next row
    }

    // Cleanup
    fclose(inputMatrix1);
    fclose(inputMatrix2);
    fclose(outputFile);
    fclose(outputTime);
    // Remember to free your buffers!

    return 0;
}

