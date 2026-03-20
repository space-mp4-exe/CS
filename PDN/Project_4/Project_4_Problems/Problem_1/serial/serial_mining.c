#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

// to activate debug statements
#define DEBUG 1

// program constants
#define SEED 123

// solution constants
#define MAX     123123123
#define TARGET  20

// functions used
unsigned int generate_hash(unsigned int nonce, unsigned int index, unsigned int* transactions, unsigned int n_transactions);
void read_file(char* file, unsigned int* transactions, unsigned int n_transactions);
 


/* Main ------------------ //
*   This is the main program.
*/
int main(int argc, char* argv[]) {

    // Catch console errors
    if (argc != 6) {
        printf("USE LIKE THIS: serial_mining transactions.csv n_transactions trials out.csv time.csv\n");
        return EXIT_FAILURE;
    }

    // Output files
    FILE* output_file = fopen(argv[4], "w");
    FILE* time_file   = fopen(argv[5], "w");

    // Read in the transactions
    unsigned int n_transactions = strtol(argv[2], NULL, 10);
    unsigned int* transactions = (unsigned int*)calloc(n_transactions, sizeof(unsigned int));
    read_file(argv[1], transactions, n_transactions);

    // get the number of trials
    unsigned int trials = strtol(argv[3], NULL, 10);


    // -------- Start Mining ------------------------------------------------------- //
    // ----------------------------------------------------------------------------- //
    double start = omp_get_wtime();

    // ------ Step 1: generate the nonce values ------ //

    srand(SEED); // set random seed
    unsigned int* nonce_array = (unsigned int*)calloc(trials, sizeof(unsigned int));
    for (int i = 0; i < trials; ++i)
        nonce_array[i] = rand() % MAX;


    // ------ Step 2: Generate the hash values ------ //

    unsigned int* hash_array = (unsigned int*)calloc(trials, sizeof(unsigned int));
    for (int i = 0; i < trials; ++i)
        hash_array[i] = generate_hash(nonce_array[i], i, transactions, n_transactions);


    // Free memory
    free(transactions);

    // ------ Step 3: Find the nonce with the minimum hash value ------ //

    unsigned int min_hash  = MAX;
    unsigned int min_nonce = MAX;
    for(int i = 0; i < trials; i++){
        if(hash_array[i] < min_hash){
            min_hash  = hash_array[i];;
            min_nonce = nonce_array[i];;
        }
    }

    // Free memory
    free(nonce_array);
    free(hash_array);

    double end = omp_get_wtime();
    // ----------------------------------------------------------------------------- //
    // -------- Finish Mining ------------------------------------------------------ //


   // Get if suceeded
    char* res = (char*)malloc(8 * sizeof(char));
    if (min_hash < TARGET)  res = (char*)"Success!";
    else                    res = (char*)"Failure.";

    // Show results in console
    if (DEBUG)
        printf("%s\n   Min hash:  %u\n   Min nonce: %u\n   %f seconds\n",
            res,
            min_hash,
            min_nonce,
            end - start
        );

    // Print results
    fprintf(output_file, "%s\n%u\n%u\n", res, min_hash, min_nonce);
    fprintf(time_file, "%f\n", end - start);

    // Cleanup  
    fclose(time_file);
    fclose(output_file);


    return 0;
} // End Main -------------------------------------------- //



/* Generate Hash ----------------------------------------- //
*   Generates a hash value from a nonce and transaction list.
*/
unsigned int generate_hash(unsigned int nonce, unsigned int index, unsigned int* transactions, unsigned int n_transactions) {

    unsigned int hash = (nonce + transactions[0] * (index + 1)) % MAX;
    for(int j = 1; j < n_transactions; j++){
        hash = (hash + transactions[j] * (index + 1)) % MAX;
     }
     return hash; 

} // End Generate Hash ---------- //



/* Read File -------------------- //
*   Reads in a file of transactions. 
*/
void read_file(char* file, unsigned int* transactions, unsigned int n_transactions) {

    // open file
    FILE* trans_file = fopen(file, "r");
    if (trans_file == NULL)
        fprintf(stderr, "ERROR: could not read the transaction file.\n"),
        exit(1);

    // read items
    char line[100] = { 0 };
    for (int i = 0; i < n_transactions && fgets(line, 100, trans_file); ++i) {
        char* p;
        transactions[i] = strtof(line, &p);
    }

    fclose(trans_file);

} // End Read File ------------- //
