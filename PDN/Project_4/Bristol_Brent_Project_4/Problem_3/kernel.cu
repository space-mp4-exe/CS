#define BLUR_SIZE 2
#define FILTER_DIM 5
/* Nonce Kernel ----------------------------------
*       Generates an array of random nonce values.
*/
__global__
void kernel(const int* input_image, int* output_image, const int* filter, int n_row, int n_col) {

    // Get the row and column indices for this thread
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if(row < n_row && col < n_col) {
        // Implementation from serial code
        int sum_val = 0;

        for (int blurRow = -BLUR_SIZE; blurRow < BLUR_SIZE +1; ++blurRow)
        {
            for(int blurCol = -BLUR_SIZE; blurCol < BLUR_SIZE+1; ++blurCol)
            {
                int curRow = row + blurRow;
                int curCol = col + blurCol;

                int i_row = blurRow + BLUR_SIZE;
                int i_col = blurCol + BLUR_SIZE;

                if( curRow > -1 && curRow < n_row && curCol > -1 && curCol < n_col)
                {
                    sum_val += input_image[curRow * n_col + curCol] * filter[i_row * FILTER_DIM + i_col]; 
                }
            }
        }

        output_image[row * n_col + col] = sum_val;
    }
} // End Nonce Kernel //