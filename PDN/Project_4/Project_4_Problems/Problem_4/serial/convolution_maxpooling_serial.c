#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define BILLION  1000000000.0
#define MAX_LINE_LENGTH 25000

#define BLUR_SIZE 2

int main (int argc, char *argv[])
{
    // Check console errors
    if( argc != 6)
    {
        printf("USE LIKE THIS: convolution_serial n_row n_col mat_input.csv mat_output.csv time.csv\n");
        return EXIT_FAILURE;
    }

    // Get dims
    int n_row = strtol(argv[1], NULL, 10);
    int n_col = strtol(argv[2], NULL, 10);

    // Get input/output files
    FILE* inputFile1  = fopen(argv[3], "r");
    if (inputFile1 == NULL){
        printf("Could not open file %s",argv[2]);
        return EXIT_FAILURE;
    }
    FILE* outputFile = fopen(argv[4], "w");
    FILE* timeFile = fopen(argv[5], "w");

    // Matrices to use
    int* filterMatrix_h = (int*)malloc(5 * 5 * sizeof(int));
    int* inputMatrix_h = (int *) malloc(n_row*n_col*sizeof(int));
    int *outputMatrix_h = (int *) malloc(n_row*n_col*sizeof(int));
    int *outputMatrix2_h = (int *) malloc(n_row*n_col*sizeof(int));

    // read the data from the file
    int row_count = 0;
    char line[MAX_LINE_LENGTH] = {0};
    while (fgets(line, MAX_LINE_LENGTH, inputFile1))
    {
        if (line[strlen(line) - 1] != '\n')  printf("\n");
        char *token;
        const char s[2] = ",";
        token = strtok(line, s);
        int i_col = 0;
        while (token != NULL)
        {
            inputMatrix_h[row_count*n_col + i_col] = strtol(token, NULL,10 );
            i_col++;
            token = strtok (NULL, s);
        }
        row_count++;
    }


    // Filling filter
	// 1 0 0 0 1 
	// 0 1 0 1 0 
	// 0 0 1 0 0 
	// 0 1 0 1 0 
	// 1 0 0 0 1 	
    for(int i = 0; i< 5; i++)
        for(int j = 0; j< 5; j++)
            filterMatrix_h[i*5+j]=0;
    filterMatrix_h[0*5+0]=1;
    filterMatrix_h[1*5+1]=1;
    filterMatrix_h[2*5+2]=1;
    filterMatrix_h[3*5+3]=1;
    filterMatrix_h[4*5+4]=1;
    
    filterMatrix_h[4*5+0]=1;
    filterMatrix_h[3*5+1]=1;
    filterMatrix_h[1*5+3]=1;
    filterMatrix_h[0*5+4]=1;

    fclose(inputFile1); 

    // --------------------------------------------------------------------------- //
    // ------ Algorithm Start ---------------------------------------------------- //
    struct timespec start, end;    
    clock_gettime(CLOCK_REALTIME, &start);

	// Performing convolution
	// Take a look at slides about the blurring example
    for(int i=0; i<n_row; i++)
        for (int j=0; j<n_col; j++)
        {
            int sum_val = 0;

            for (int blurRow = -BLUR_SIZE; blurRow < BLUR_SIZE +1; ++blurRow)
            {
                for(int blurCol = -BLUR_SIZE; blurCol < BLUR_SIZE+1; ++blurCol)
                {
                    int curRow = i + blurRow;
                    int curCol = j + blurCol;

                    int i_row = blurRow + BLUR_SIZE;
                    int i_col = blurCol + BLUR_SIZE;

                    if( curRow > -1 && curRow < n_row && curCol > -1 && curCol < n_col)
                    {
                        sum_val += inputMatrix_h[curRow*n_col + curCol]*filterMatrix_h[i_row*5 + i_col]; 
                    }
                }
            }
            outputMatrix_h[i*n_col+j] = sum_val;
        }

    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
    // --------------------------------------------------------------------------- //
    clock_gettime(CLOCK_REALTIME, &start);


	// Performing maxpooling
    for(int i=0; i<n_row; i++)
        for (int j=0; j<n_col; j++)
        {
            int max = 0;

            for (int blurRow = -BLUR_SIZE; blurRow < BLUR_SIZE +1; ++blurRow)
            {
                for(int blurCol = -BLUR_SIZE; blurCol < BLUR_SIZE+1; ++blurCol)
                {
                    int curRow = i + blurRow;
                    int curCol = j + blurCol;

                    if( curRow > -1 && curRow < n_row && curCol > -1 && curCol < n_col)
                    {
                        if (outputMatrix_h[curRow*n_col + curCol] > max)
                            max = outputMatrix_h[curRow*n_col + curCol];
                    }

                }
            }

            outputMatrix2_h[i*n_col+j] = max;

        }

    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent2 = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;
    // --------------------------------------------------------------------------- //
    // ------ Algorithm End ------------------------------------------------------ //

	// Save output matrix as csv file
     for (int i = 0; i<n_row; i++)
    {
        for (int j = 0; j<n_col; j++)
        {
            fprintf(outputFile, "%d", outputMatrix2_h[i*n_col +j]);
            if (j != n_col -1)
                fprintf(outputFile, ",");
            else if ( i < n_row-1)
                fprintf(outputFile, "\n");
        }
    }

     // Print time
    fprintf(timeFile, "%.20f", time_spent+time_spent2);

    // Cleanup
    fclose(outputFile);
    fclose(timeFile);

    free(inputMatrix_h);
    free(filterMatrix_h);
    free(outputMatrix_h);
    free(outputMatrix2_h);

    return 0;
}