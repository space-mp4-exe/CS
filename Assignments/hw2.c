#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUMBERS_PER_THREAD 1000

// Structure to pass parameters to the thread
typedef struct {
    int start;
    int end;
    long partial_sum;
} ThreadData;

// Function executed by each thread to calculate the partial sum
void* calculate_partial_sum(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->partial_sum = 0;

    for (int i = data->start; i <= data->end; i++) {
        data->partial_sum += i;
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    long total_sum = 0;

    // Create the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * NUMBERS_PER_THREAD;
        thread_data[i].end = (i + 1) * NUMBERS_PER_THREAD - 1;
        thread_data[i].partial_sum = 0;

        if (pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join the threads and accumulate the total sum
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
        total_sum += thread_data[i].partial_sum;
    }

    // Print the total sum
    printf("Total sum from 0 to 9999: %ld\n", total_sum);

    return 0;
}
