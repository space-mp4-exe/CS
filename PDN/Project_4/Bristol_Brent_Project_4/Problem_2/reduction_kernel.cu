__global__
void reduction_kernel(unsigned int* hash_array, unsigned int* min_index, int n) {
    extern __shared__ unsigned int sdata[];
    unsigned int tid = threadIdx.x;
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) {
        sdata[tid] = index; // store index
    } else {
        sdata[tid] = n; // invalid
    }
    __syncthreads();
    for (unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
        if (tid < s) {
            unsigned int other = sdata[tid + s];
            if (other < n && (sdata[tid] >= n || hash_array[other] < hash_array[sdata[tid]])) {
                sdata[tid] = other;
            }
        }
        __syncthreads();
    }
    if (tid == 0) {
        min_index[blockIdx.x] = sdata[0];
    }
} // End Reduction Kernel //