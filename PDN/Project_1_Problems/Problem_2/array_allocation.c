#include <stdio.h>
#include <stdlib.h>


int main(void) {

    // Dynamically allocate a 2D array with arbitrary dimensions
    int height = 3;     // 3 rows high
    int width = 4;      // 4 columns wide 

    // Allocate a 1D array to store all the elements in the 2D array
    int* array = (int*)malloc((height * width) * sizeof(int));

    /* 
     * Row-major order - values are written row by row
     * Example at: 
     * https://learningmonkey.in/courses/c-programming/lessons/row-major-order-and-column-major-order-in-c/ 
     */

    // Write values into array
    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            array[row * width + column] = row * width + column + 1;
        }
    }

    // The values of the 1D array printed
    // Output should be: 
    //      1 2 3 4 5 6 7 8 9 10 11 12
    printf("\t");
    for(int i = 0; i < width * height; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");


    // Print values as a 2D array
    // Output should be:
    //      1 2 3 4
    //      5 6 7 8
    //      9 10 11 12
    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            printf("\t%d ", array[row * width + column]);
        }
        printf("\n");
    }

    free(array);

    return 0;
}