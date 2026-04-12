#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

bool check_partner(int my_int, int my_rank, int comm_sz, MPI_Comm comm)

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

   bool my_lower_partner_smaller = check_lower_partner(my_number, my_rank, p, comm);
    
   MPI_Reduce(&my_lower_partner_smaller, &sorted, 1, MPI_C_BOOL, MPI_LAND, 0, comm);
    
   if (my_rank == 0)
       if(sorted){
           printf("the list is sorted\n");
       }else{
           printf("the list is not sorted\n");
       }

   MPI_Finalize();
   return 0;
}  /* main */

bool check_lower_partner(
      int my_int    /* in */,
      int my_rank   /* in */,
      int comm_sz   /* in */,
      MPI_Comm comm /* in */) {
    
    bool isSmaller = true;

    int send_partner = my_rank + 1;
    if(send_partner < comm_sz - 1)
        send_partner = MPI_PROC_NULL;

    int recv_partner = my_rank - 1;
    if(recv_partner < 0)
        recv_partner = MPI_PROC_NULL;

    int recv_int = 0;
    MPI_Sendrecv(&my_int, 1, MPI_INT, send_partner, 0,
                 &recv_int, 1, MPI_INT, recv_partner, 0,
                 comm, MPI_STATUS_IGNORE);

    if(my_rank != 0)
        isSmaller= my_int >= recv_int;
    else
        isSmaller = true;

    return isSmaller;
}