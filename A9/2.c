#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define n 10
  
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  
// Temporary array for slave process
int a2[50];
  
int main(int argc, char* argv[]) {
	int pid, np, count;
    MPI_Status status;
  
    MPI_Init(&argc, &argv);
  
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    
    count = n / (np - 1);

    if (pid == 0) {
        int index, i;
  
        if (np > 1) {
            for (i = 1; i < np; i++) {
                index = (i - 1) * count;
                MPI_Send(&a[index],
                         count,
                         MPI_INT, i, 0,
                         MPI_COMM_WORLD);
            }
        }
        
        index = (i - 1) * count;
        
        int sum = 0;
        for (i = index; i < n; i++) sum += a[i];
  
        int tmp;
        for (i = 1; i < np; i++) {
            MPI_Recv(&tmp, 1, MPI_INT,
                     MPI_ANY_SOURCE, 0,
                     MPI_COMM_WORLD,
                     &status);  
            sum += tmp;
        }
  
        // prints the final sum of array
        printf("Sum of array is : %d\n", sum);
    }
    else {  
        MPI_Recv(&a2, count,
                 MPI_INT, 0, 0,
                 MPI_COMM_WORLD,
                 &status);
  
        int partial_sum = 0;
        for (int i = 0; i < count; i++) partial_sum += a2[i];
  
        MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  
    MPI_Finalize();
  
    return 0;
}
