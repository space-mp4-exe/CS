#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_LINE_LENGTH 1000000
#define DEBUG 0

/* ------------ Project 2 - Problem 3 - Encryption ------------
    This file encrypts a text file serially.
    Most of the work is done for you.
    Just find what in the program can be parallelized and how to encrypt a character.
    Don't forget to log the output time of your modified code!
*/ // ------------------------------------------------------ //

int main (int argc, char *argv[])
{
    // Catch console errors
    //  Make sure you include the # of threads and your output time file.
    if (argc != 4) {
        printf("USE LIKE THIS: encrypt_serial key input_text.txt output_text.txt\n");
        return EXIT_FAILURE;
    }

    // Read in the encryption key
    char* p1;
    int key = strtol(argv[1], &p1, 10 );

    // Open the input, unencrypted text file
    FILE* inputFile = fopen(argv[2], "r");

    // Open the output, encrypted text file
    FILE* outputFile = fopen(argv[3], "w");


    // Allocate and open a buffer to read in the input
    fseek(inputFile, 0L, SEEK_END);
    long lSize = ftell(inputFile);
    rewind(inputFile);
    unsigned char* buffer = calloc(1, lSize + 1);
    if (!buffer)
        fclose(inputFile),
        fclose(outputFile),
        // fclose(timeFile),
        free(buffer),
        fputs("Memory alloc for inputFile1 failed!\n", stderr), 
        exit(1);

    // Read the input into the buffer
    if(1 != fread(buffer, lSize, 1, inputFile))
        fclose(inputFile),
        fclose(outputFile),
        // fclose(timeFile),
        free(buffer),
        fputs("Failed reading into the input buffer!\n", stderr),
        exit(2);

    // Allocate a buffer for the encrypted data
    unsigned char* encrypted_buffer = calloc(1, lSize+1);
    if (!encrypted_buffer)
        fclose(inputFile),
        fclose(outputFile),
        // fclose(timeFile),
        free(encrypted_buffer),
        free(buffer),
        fputs("Memory alloc for the encrypted buffer failed!\n", stderr),
        exit(3);


    // ----> Begin Encryption <----- //
    // Encrypt the buffer into the encrypted_buffer
    for (int i = 0; i<lSize; i++) {
        // encrypted_buffer[i] = ??? ;  // TODO: Encrypt a character from the input buffer.
    }
    if (DEBUG) printf("Values encypted! \n");

    // Print to the output file
    for (int i = 0; i<lSize; i++) {
        fprintf(outputFile, "%c", encrypted_buffer[i]);
    }



    // Cleanup
    fclose(inputFile);
    fclose(outputFile);
    // fclose(timeFile);
    free(encrypted_buffer);
    free(buffer);

    return 0;
} // End main //

/* ---------------------------------------------------------------------------------------------------
    Sources used:
        https://stackoverflow.com/questions/3747086/reading-the-whole-text-file-into-a-char-array-in-c
*/