#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <omp.h>
#include <math.h> 
#include <float.h>

#define MAXCHAR 25
#define DEBUG   1


int main(int argc, char* argv[]) {
    // Catch console errors
    if (argc != 8) {
        printf("USE LIKE THIS: kmeans_clustering n_points points.csv n_centroids centroids.csv output.csv time.csv num_threads\n");
        exit(-1);
    }

    // points ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    int num_points = strtol(argv[1], NULL, 10);
    FILE* pointsFile = fopen(argv[2], "r");
    if (pointsFile == NULL) {
        printf("Could not open file %s", argv[2]);
        exit(-2);
    }

    // centroids ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    int num_centroids = strtol(argv[3], NULL, 10);
    FILE* centroidsFile = fopen(argv[4], "r");
    if (centroidsFile == NULL) {
        printf("Could not open file %s", argv[4]);
        fclose(pointsFile);
        exit(-3);
    }

    // output ~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    FILE* outputFile = fopen(argv[5], "w");
    FILE* timeFile = fopen(argv[6], "w");

    // threads ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    int num_threads = strtol(argv[7], NULL, 10);

    // array ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    double* points_x = malloc(num_points * sizeof(double));
    double* points_y = malloc(num_points * sizeof(double));

    // centroid array /////////////////////////////////////////
    double* centroids_x = malloc(num_centroids * sizeof(double));
    double* centroids_y = malloc(num_centroids * sizeof(double));



    // Store values ~~~~~~~~ //  
    // temporarily store values
    char str[MAXCHAR];

    // Storing point values //
    int k = 0;
    while (fgets(str, MAXCHAR, pointsFile) != NULL) {
        sscanf(str, "%lf,%lf", &(points_x[k]), &(points_y[k]));
        k++;
    }
    fclose(pointsFile);

    // Storing centroid values //
    k = 0;
    while (fgets(str, MAXCHAR, centroidsFile) != NULL) {
        sscanf(str, "%lf,%lf", &(centroids_x[k]), &(centroids_y[k]));;
        k++;
    }
    fclose(centroidsFile);



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    // start time
    double start = omp_get_wtime();


    // TODO: implement algorithm here :)


    // end time
    double end = omp_get_wtime();
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //



    // print time //
    double time_passed = end - start;
    fprintf(timeFile, "%f", time_passed);

    // print centroids //
    for (int c = 0; c < num_centroids; ++c) {
        fprintf(outputFile, "%f, %f", centroids_x[c], centroids_y[c]);
        if (c != num_centroids - 1) fprintf(outputFile, "\n");
    }



    // close files //
    fclose(outputFile);
    fclose(timeFile);

    // free memory //
    free(points_x);
    free(points_y);
    free(centroids_x);
    free(centroids_y);

    // return //
    return 0;
}