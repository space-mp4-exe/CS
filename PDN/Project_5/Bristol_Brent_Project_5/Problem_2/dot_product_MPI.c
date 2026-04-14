#include <stdio.h>
#include <stdlib.h> // for strtol
#include <string.h>
#include <time.h>
#include "mpi.h"

#define MAXCHAR 25
#define BILLION  1000000000.0

int main (int argc, char *argv[])
{
    if( argc != 6)
    {
        printf("USE LIKE THIS: dot_product_MPI vector_size vec_1.csv vec_2.csv result.csv time.csv\n");
        return EXIT_FAILURE;
    }
    
    // MPI
    int my_rank;
    int n_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
    
    // Size
    int vec_size = strtol(argv[1], NULL, 10);

    // To read in
    double* vec_1 = NULL;
    double* vec_2 = NULL;


    if (my_rank == 0) {
        // Input files
        FILE* inputFile1 = fopen(argv[2], "r");
        FILE* inputFile2 = fopen(argv[3], "r");
        if (inputFile1 == NULL) printf("Could not open file %s", argv[2]);
        if (inputFile2 == NULL) printf("Could not open file %s",argv[3]);
    
        vec_1 = malloc(vec_size * sizeof(double));
        vec_2 = malloc(vec_size * sizeof(double));

        // Store values of vector
        int k = 0;
        char str[MAXCHAR];
        while (fgets(str, MAXCHAR, inputFile1) != NULL)
        {
            sscanf( str, "%lf", &(vec_1[k]) );
            k++;
        }
        fclose(inputFile1); 

        // Store values of vector
        k = 0;
        while (fgets(str, MAXCHAR, inputFile2) != NULL)
        {
            sscanf( str, "%lf", &(vec_2[k]) );
            k++;
        }
        fclose(inputFile2); 
    }

    int chunk_size = vec_size / n_procs;

    double* local_vec1 = malloc(chunk_size * sizeof(double));
    double* local_vec2 = malloc(chunk_size * sizeof(double));


    // Scatter the vectors to all processes
    MPI_Scatter(vec_1, chunk_size, MPI_DOUBLE, local_vec1, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vec_2, chunk_size, MPI_DOUBLE, local_vec2, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double starttime = MPI_Wtime(); // Start timer

    // Compute local dot product
    double local_dot_product = 0.0;
    for (int i = 0; i < chunk_size; i++)
        local_dot_product += local_vec1[i] * local_vec2[i];

    // Reduce
    double dot_product = 0.0;
    MPI_Reduce(&local_dot_product, &dot_product, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double endtime = MPI_Wtime(); // End timer
    double time_spent = endtime - starttime;

    // Print to output
    if (my_rank == 0) {
        // Output files
        FILE* outputFile = fopen(argv[4], "w");
        FILE* timeFile = fopen(argv[5], "w");

        fprintf(outputFile, "%lf", dot_product);
        fprintf(timeFile, "%.20f", time_spent);
        
        // Cleanup
        fclose (outputFile);
        fclose (timeFile);
        
        free(vec_1);
        free(vec_2);
    }
    
    free(local_vec1);
    free(local_vec2);
    MPI_Finalize();

    return 0;
}