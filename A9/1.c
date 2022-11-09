#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0) {
		char *msg = "Hello World";
		MPI_Bcast(msg, 12, MPI_CHAR, 0, MPI_COMM_WORLD);
	} else {
		char *msg = (char *)malloc(100 * sizeof(char));
		MPI_Status status;
		MPI_Bcast(msg, 12, MPI_CHAR, 0, MPI_COMM_WORLD);
		printf("%d - %s\n", rank, msg);
	}

	MPI_Finalize();
	
	return 0;
}

