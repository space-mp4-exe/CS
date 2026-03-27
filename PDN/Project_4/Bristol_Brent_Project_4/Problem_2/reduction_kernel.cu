#define BLOCK_SIZE 1024
__global__
void reduction_kernel(unsigned int* hash_array, unsigned int* min_hash_array, unsigned int* nonce_array, unsigned int* min_nonce_array, unsigned size) {

    int index = 2 * blockIdx.x * blockDim.x + threadIdx.x;

    __shared__ unsigned int red_hashes[BLOCK_SIZE]; // output array for hash reductions
    __shared__ unsigned int red_nonces[BLOCK_SIZE]; // ouput array for nonce reductions

    // Load first pair
    int hash1, nonce1;
    if(index < size) {
        hash1 = hash_array[index];
        nonce1 = nonce_array[index];
    } else {
        hash1 = UINT_MAX; // invalid
        nonce1 = 0; // invalid
    }

    // Load second pair
    int hash2, nonce2;
    if(index + BLOCK_SIZE < size) {
        hash2 = hash_array[index + BLOCK_SIZE];
        nonce2 = nonce_array[index + BLOCK_SIZE];
    } else {
        hash2 = UINT_MAX; // invalid
        nonce2 = 0; // invalid
    }

    if(hash1 < hash2) {
        red_hashes[threadIdx.x] = hash1;
        red_nonces[threadIdx.x] = nonce1;
    } else {
        red_hashes[threadIdx.x] = hash2;
        red_nonces[threadIdx.x] = nonce2;
    }

    for(int stride = BLOCK_SIZE / 2; stride >= 1; stride /= 2) {
        __syncthreads();
        if(threadIdx.x < stride) {
            int hash_a = red_hashes[threadIdx.x];
            int hash_b = red_hashes[threadIdx.x + stride];
            if(hash_b < hash_a) {
                red_hashes[threadIdx.x] = hash_b;
                red_nonces[threadIdx.x] = red_nonces[threadIdx.x + stride];
            }
            // If hash_a is already smaller, we keep it and its corresponding nonce
        }
    }

    // Write the minimum hash and nonce for this block to global memory
    if(threadIdx.x == 0) {
        min_hash_array[blockIdx.x] = red_hashes[0];
        min_nonce_array[blockIdx.x] = red_nonces[0];
    }
} // End Reduction Kernel //