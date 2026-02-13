#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// Use more libraries as necessary

#define DEBUG 0

/* ---------- Project 1 - Problem 2 - Mat-Vec Mult ----------
    This file will multiply a matrix and vector.
    Complete the TODOs left in this file.
*/ // ------------------------------------------------------ //


// multiplies two matrixies 
// matrix is a n_col1 x n_row2 matrix 
void matMult(long int* matrix, int n_col1, int n_row1, long int* vector, long int* output){
    for(int i = 0; i < n_col1; i++){
        output[i] = 0;// presetting output entry to 0
        for (int j = 0; j < n_row1; j++){
            output[i] += matrix[i * n_row1 + j] * vector[j];
        }
    }
}

int main (int argc, char *argv[])
{
    // Catch console errors
    if( argc != 7)
    {
        printf("USE LIKE THIS: serial_mult_mat_vec in_mat.csv n_row_1 n_col_1 in_vec.csv n_row_2 output_file.csv \n");
        return EXIT_FAILURE;
    }

    // Get the input files
    FILE *matFile = fopen(argv[1], "r");
    FILE *vecFile = fopen(argv[4], "r");

    // Get dim of the matrix
    char* p1;
    char* p2;
    int n_row1 = strtol(argv[2], &p1, 10 );
    int n_col1 = strtol(argv[3], &p2, 10 );

    // Get dim of the vector
    char* p3;
    int n_row2 = strtol(argv[5], &p3, 10 );

    // Get the output file
    FILE *outputFile = fopen(argv[6], "w");



    // Use malloc to allocate memory for the matrices
    long int *matrix = (long int *)malloc(n_row1 * n_col1 * sizeof(long int));
    long int *vector = (long int *)malloc(n_row2 * sizeof(long int));
    long int *output = (long int *)malloc(n_col1 * sizeof(long int));

    // Parse the input CSV files
    // first it puts part of the file into an input buffer
    // Tokens are then parsed from that buffer and put into the matrix
    char line[1024];// char array to buffer file input
    int index = 0;
    // inserting information into matrix
    while(fgets(line, 1024, matFile)){
        char* token;
        token = strtok(line, ",");
        while(token != NULL && index < n_row1 * n_col1){
            long int value;
            //char* endptr;

            value = strtol(token, NULL, 10); //convert parsed token to an int
            matrix[index] = value;
            index++; //increment index of matrix
            token = strtok(NULL, ","); //token takes on next value in row
        }
    }

    // inserting information into vector
    index = 0; // resetting index for the new array
    while(fgets(line, 1024, vecFile)){
        char* token;
        token = strtok(line, ",");
        while(token != NULL && index < n_row2){
            long int value;
            //char* endptr;

            value = strtol(token, NULL, 10);
            vector[index] = value;
            index++;
            token = strtok(NULL, ",");
        }
    }

    // Perform the matrix-vector multiplication
    matMult(matrix, n_col1, n_row1, vector, output);

    // Write the output CSV file
    for (int i = 0; i < n_col1; i++){
        fprintf(outputFile, "%ld \n", output[i]);
    }

    // Free memory
    free(matrix);
    free(vector);
    free(output);

    // Cleanup
    fclose (matFile);
    fclose (vecFile);
    fclose (outputFile);
    // Free buffers here as well!

    return 0;
}
