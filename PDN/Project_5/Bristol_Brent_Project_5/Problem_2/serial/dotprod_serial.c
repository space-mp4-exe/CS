#include <stdio.h>
#include <stdlib.h> // for strtol
#include <string.h>
#include <time.h>

#define MAXCHAR 25
#define BILLION  1000000000.0

int main (int argc, char *argv[])
{
    if( argc != 6)
    {
        printf("USE LIKE THIS: dotprod_serial vector_size vec_1.csv vec_2.csv result.csv time.csv\n");
        return EXIT_FAILURE;
    }

    // Size
    int vec_size = strtol(argv[1], NULL, 10);

    // Input files
    FILE* inputFile1 = fopen(argv[2], "r");
    FILE* inputFile2 = fopen(argv[3], "r");
    if (inputFile1 == NULL) printf("Could not open file %s", argv[2]);
    if (inputFile2 == NULL) printf("Could not open file %s",argv[3]);

    // Output files
    FILE* outputFile = fopen(argv[4], "w");
    FILE* timeFile = fopen(argv[5], "w");

    // To read in
    double* vec_1 = malloc(vec_size * sizeof(double));
    double* vec_2 = malloc(vec_size * sizeof(double));

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
  

    // info about timing in C -------------------------------------
    // https://www.techiedelight.com/find-execution-time-c-program/
    struct timespec start, end;
    
    // Get start time
    clock_gettime(CLOCK_REALTIME, &start);

    // Get dot product
    double dot_product = 0.0;
    for (int i = 0; i < vec_size; i++)
        dot_product += vec_1[i] * vec_2[i];
    printf("DP in C: %lf\n", dot_product);

    // Get finish time
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;

    // Print to output
    fprintf(outputFile, "%lf", dot_product);
    fprintf(timeFile, "%.20f", time_spent);

    // Cleanup
    fclose (outputFile);
    fclose (timeFile);

    free(vec_1);
    free(vec_2);

    return 0;
}