
// To generate random value
__device__
unsigned int random_kernel(unsigned int seed, unsigned int index);


/* Nonce Kernel ----------------------------------
*       Generates an array of random nonce values.
*/
__global__
void nonce_kernel(unsigned int* nonce_array, unsigned int array_size, unsigned int mod, unsigned int seed) {

    // Calculate thread rank
    unsigned int index = blockDim.x * blockIdx.x + threadIdx.x;

    // Generate random nonce values for every item in the array
    if (index < array_size) {
        unsigned int rand = random_kernel(seed, index);
        nonce_array[index] = rand % mod;
    }

} // End Nonce Kernel //



/* Random Kernel ----------------
*       Generates a random value.
*/
__device__
unsigned int random_kernel(unsigned int seed, unsigned int index) {

    curandState_t state;
    curand_init(
        seed,  // the seed can be the same for every thread and is set to be the time
        index, // the sequence number should be different for every thread
        0,     // an offset into the random number sequence at which to begin sampling
        &state // the random state object
    );

    // generate a random number
    return (unsigned int)(curand(&state));

} // End Random Kernel //
