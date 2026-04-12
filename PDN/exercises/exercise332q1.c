#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int my_rank, comm_sz;
    MPI_Comm comm;
    MPI_Init(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);
    srandom(my_rank+1);
    int my_number = random() % 100 + my_rank*50;
    printf("Proc %d > my_number = %d\n", my_rank, my_number);
    bool sorted = false;

    int* all_numbers;
    if (my_rank == 0) {
        all_numbers = (int*)malloc(comm_sz * sizeof(int));
        MPI_Gather( &my_number, 1, MPI_INT, all_numbers, 1, MPI_INT, 0, comm);
        sorted = true;
        for (int i = 1; i < comm_sz; i++){
            if(all_numbers[i - 1] > all_numbers[i]){
                sorted = false;
                break;
            }
        }
        free(all_numbers);
    } else {
        MPI_Gather( &my_number, 1, MPI_INT, all_numbers, 1, MPI_INT, 0, comm);
    }
    
    if (my_rank == 0) {
        if(sorted)
            printf("the list is sorted\n");
        else
            printf("the list is not sorted\n");
    }

    MPI_Finalize();
    return 0;
}  /* main */