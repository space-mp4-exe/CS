__host__ float reduceArray(float* array, unsigned int size){
    float result = 0;

    float *d_in, *d_out;

    // Each block reduces 2*BLOCK_SIZE elements
    unsigned int numBlocks = (size + 2*BLOCK_SIZE - 1) / (2*BLOCK_SIZE);

    // Allocate device memory
    cudaMalloc((void**)&d_in, size * sizeof(float));
    cudaMalloc((void**)&d_out, numBlocks * sizeof(float));

    // Copy input array to device
    cudaMemcpy(d_in, array, size * sizeof(float), cudaMemcpyHostToDevice);

    // Launch kernel
    reductionTree<<<numBlocks, BLOCK_SIZE>>>(d_out, d_in, size);

    // Allocate host memory for partial sums
    float *h_out = (float*)malloc(numBlocks * sizeof(float));

    // Copy partial sums back
    cudaMemcpy(h_out, d_out, numBlocks * sizeof(float), cudaMemcpyDeviceToHost);

    // Finish reduction on CPU
    for(unsigned int i = 0; i < numBlocks; i++)
        result += h_out[i];

    // Free memory
    cudaFree(d_in);
    cudaFree(d_out);
    free(h_out);

    return result;
}