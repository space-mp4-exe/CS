#include <cuda_runtime_api.h>
#include <curand_kernel.h>
#include <driver_types.h>
#include <curand.h>
#if _WIN32
    #include <io.h>
#else 
    #include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cstdio>
#include <cuda.h>

#include "support.h"
#include "kernel.cu"

#define MAX_LINE_LENGTH 25000
#define BLOCK_SIZE 16

#define BLUR_SIZE 2
#define FILTER_DIM 5


// functions used
//unsigned int generate_hash(unsigned int nonce, unsigned int index, unsigned int* transactions, unsigned int n_transactions);
void read_file(char* file, unsigned int* transactions, unsigned int n_transactions);
void err_check(cudaError_t ret, char* msg, int exit_code);


/* Main ------------------ //
*   This is the main program.
*/
int main(int argc, char* argv[]) {

    // Check console errors
    if( argc != 6)
    {
        printf("USE LIKE THIS: convolution_CUDA n_row n_col mat_input.csv mat_output.csv time.csv\n");
        return EXIT_FAILURE;
    }

    // Get dims
    int n_row = strtol(argv[1], NULL, 10);
    int n_col = strtol(argv[2], NULL, 10);

    // Get files to read/write 
    FILE* inputFile1 = fopen(argv[3], "r");
    if (inputFile1 == NULL){
        printf("Could not open file %s",argv[2]);
        return EXIT_FAILURE;
    }
    FILE* outputFile = fopen(argv[4], "w");
    FILE* timeFile  = fopen(argv[5], "w");

    // Matrices to use
    int* filterMatrix_h = (int*)malloc(5 * 5 * sizeof(int));
    int* inputMatrix_h  = (int*) malloc(n_row * n_col * sizeof(int));
    int* outputMatrix_h = (int*) malloc(n_row * n_col * sizeof(int));

    // read the data from the file
    int row_count = 0;
    char line[MAX_LINE_LENGTH] = {0};
    while (fgets(line, MAX_LINE_LENGTH, inputFile1)) {
        if (line[strlen(line) - 1] != '\n') printf("\n");
        char *token;
        const char s[2] = ",";
        token = strtok(line, s);
        int i_col = 0;
        while (token != NULL) {
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

    filterMatrix_h[0*5+0] = 1;
    filterMatrix_h[1*5+1] = 1;
    filterMatrix_h[2*5+2] = 1;
    filterMatrix_h[3*5+3] = 1;
    filterMatrix_h[4*5+4] = 1;
    
    filterMatrix_h[4*5+0] = 1;
    filterMatrix_h[3*5+1] = 1;
    filterMatrix_h[1*5+3] = 1;
    filterMatrix_h[0*5+4] = 1;

    fclose(inputFile1); 

    // Allocate CUDA variables
    cudaError_t cuda_ret;
    int* device_input_image;    
    cuda_ret = cudaMalloc((void**)&device_input_image, n_row * n_col * sizeof(int));
    err_check(cuda_ret, (char*)"Unable to allocate input image to device memory!", 0);

    int* device_output_image;    
    cuda_ret = cudaMalloc((void**)&device_output_image, n_row * n_col * sizeof(int));
    err_check(cuda_ret, (char*)"Unable to allocate output image to device memory!", 1);

    int* device_filter;    
    cuda_ret = cudaMalloc((void**)&device_filter, FILTER_DIM * FILTER_DIM * sizeof(int));
    err_check(cuda_ret, (char*)"Unable to allocate filter to device memory!", 2);


    // Transfer data to device
    Timer transfer_timer;
    startTime(&transfer_timer);
    cuda_ret = cudaMemcpy(device_input_image, inputMatrix_h, n_row * n_col * sizeof(int), cudaMemcpyHostToDevice);
    err_check(cuda_ret, (char*)"Unable to copy input image to device memory!", 3);

    cuda_ret = cudaMemcpy(device_filter, filterMatrix_h, FILTER_DIM * FILTER_DIM * sizeof(int), cudaMemcpyHostToDevice);
    err_check(cuda_ret, (char*)"Unable to copy filter to device memory!", 4);
    stopTime(&transfer_timer);
    double transfer_time = elapsedTime(transfer_timer);
    //printf("Data transfer time: %.20f seconds\n", transfer_time);

    // Launch kernel
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid(ceil(n_col / (float)BLOCK_SIZE), ceil(n_row / (float)BLOCK_SIZE));
    Timer kernel_timer;
    startTime(&kernel_timer);
    kernel<<<dimGrid, dimBlock>>>(device_input_image, device_output_image, device_filter, n_row, n_col);
    cuda_ret = cudaDeviceSynchronize();
    err_check(cuda_ret, (char*)"Unable to launch kernel!", 5);
    stopTime(&kernel_timer);
    double kernel_time = elapsedTime(kernel_timer);

    // Transfer data back to host
    Timer output_timer;
    startTime(&output_timer);
    cuda_ret = cudaMemcpy(outputMatrix_h, device_output_image, n_row * n_col * sizeof(int), cudaMemcpyDeviceToHost);
    err_check(cuda_ret, (char*)"Unable to copy output image to host memory!", 6);	
    stopTime(&output_timer);
    double output_time = elapsedTime(output_timer);
    
    // Save output matrix as csv file
    for (int i = 0; i < n_row; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            fprintf(outputFile, "%d", outputMatrix_h[i * n_col + j]);
            if (j != n_col - 1)
                fprintf(outputFile, ",");
            else if ( i < n_row - 1)
                fprintf(outputFile, "\n");
        }
    }

    // Print time
    fprintf(timeFile, "%.20f\n", transfer_time);
    fprintf(timeFile, "%.20f\n", kernel_time);
    fprintf(timeFile, "%.20f\n", output_time);

    // Cleanup
    fclose (outputFile);
    fclose (timeFile);

    free(inputMatrix_h);
    free(outputMatrix_h);
    free(filterMatrix_h);

    cudaFree(device_input_image);
    cudaFree(device_output_image);
    cudaFree(device_filter);

    return 0;
}

/* Read File -------------------- //
*   Reads in a file of transactions. 
*/
void read_file(char* file, unsigned int* transactions, unsigned int n_transactions) {

    // open file
    FILE* trans_file = fopen(file, "r");
    if (trans_file == NULL)
        fprintf(stderr, "ERROR: could not read the transaction file.\n"),
        exit(-1);

    // read items
    char line[100] = { 0 };
    for (int i = 0; i < n_transactions && fgets(line, 100, trans_file); ++i) {
        char* p;
        transactions[i] = strtof(line, &p);
    }

    fclose(trans_file);

} // End Read File ------------- //



/* Error Check ----------------- //
*   Exits if there is a CUDA error.
*/
void err_check(cudaError_t ret, char* msg, int exit_code) {
    if (ret != cudaSuccess)
        fprintf(stderr, "%s \"%s\".\n", msg, cudaGetErrorString(ret)),
        exit(exit_code);
} // End Error Check ----------- //
