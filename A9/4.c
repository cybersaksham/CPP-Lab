#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void swap(int* arr, int i, int j)
{
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}

void quicksort(int* arr, int start, int end)
{
	int pivot, index;

	if (end <= 1)
		return;

	pivot = arr[start + end / 2];
	swap(arr, start, start + end / 2);

	index = start;

	for (int i = start + 1; i < start + end; i++) {

		if (arr[i] < pivot) {
			index++;
			swap(arr, i, index);
		}
	}

	swap(arr, start, index);

	quicksort(arr, start, index - start);
	quicksort(arr, index + 1, start + end - index - 1);
}

int* merge(int* arr1, int n1, int* arr2, int n2)
{
	int* result = (int*)malloc((n1 + n2) * sizeof(int));
	int i = 0;
	int j = 0;
	int k;

	for (k = 0; k < n1 + n2; k++) {
		if (i >= n1) {
			result[k] = arr2[j];
			j++;
		}
		else if (j >= n2) {
			result[k] = arr1[i];
			i++;
		}

		// Indices in bounds as i < n1
		// && j < n2
		else if (arr1[i] < arr2[j]) {
			result[k] = arr1[i];
			i++;
		}

		// v2[j] <= v1[i]
		else {
			result[k] = arr2[j];
			j++;
		}
	}
	return result;
}

// Driver Code
int main(int argc, char* argv[])
{
	srand(time(0));
	int number_of_elements=10;
	int* data = NULL;
	int chunk_size, own_chunk_size;
	int* chunk;
	double time_taken;
	MPI_Status status;

	int number_of_process, rank_of_process;

	if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
		printf("Error in creating MPI program.\n "
			"Terminating......\n");
		exit(1);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_of_process);

	if (rank_of_process == 0) {

		// Computing chunk size
		chunk_size = (number_of_elements % number_of_process == 0) ?	(number_of_elements/number_of_process) : (number_of_elements/(number_of_process - 1));

		data = (int *)malloc(number_of_process * chunk_size * sizeof(int));
		
		for(int i=0;i<number_of_elements;++i) scanf("%d", data+i);

		printf("Elements in the array is: ");
		for(int i = 0; i < number_of_elements; i++)
			printf("%d ", data[i]);
		printf("\n");
	}

	// Blocks all process until reach this point
	MPI_Barrier(MPI_COMM_WORLD);

	// Starts Timer
	time_taken -= MPI_Wtime();

	// BroadCast the Size to all the
	// process from root process
	MPI_Bcast(&number_of_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Computing chunk size
	chunk_size= (number_of_elements % number_of_process == 0) ? (number_of_elements / number_of_process) : (number_of_elements /(number_of_process - 1));

	// Calculating total size of chunk
	// according to bits
	chunk = (int *)malloc(chunk_size * sizeof(int));

	// Scatter the chuck size data to all process
	MPI_Scatter(data, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
	free(data);
	data = NULL;

	own_chunk_size = (number_of_elements >= chunk_size*(rank_of_process + 1)) ? chunk_size : (number_of_elements -
chunk_size*rank_of_process);

	quicksort(chunk, 0, own_chunk_size);

	for(int step = 1; step < number_of_process; step = 2 * step)
	{
			if (rank_of_process % (2 * step) != 0) {
				MPI_Send(chunk, own_chunk_size, MPI_INT, rank_of_process - step, 0, MPI_COMM_WORLD);
				break;
			}

			if (rank_of_process + step < number_of_process) {
				int received_chunk_size = (number_of_elements >= chunk_size * (rank_of_process + 2 * step)) ? (chunk_size * step) : (number_of_elements - chunk_size * (rank_of_process + step));
				int* chunk_received;
				chunk_received = (int*)malloc(received_chunk_size * sizeof(int));
				MPI_Recv(chunk_received, received_chunk_size,MPI_INT, rank_of_process + step, 0,MPI_COMM_WORLD, &status);

				data = merge(chunk, own_chunk_size,chunk_received,received_chunk_size);

				free(chunk);
				free(chunk_received);
				chunk = data;
				own_chunk_size = own_chunk_size + received_chunk_size;
			}
	}

	// Stop the timer
	time_taken += MPI_Wtime();

	if(rank_of_process == 0){
			//printf("Total number of Elements given as input : %d\n", number_of_elements);
				
			printf("Sorted array is: \n");

			for (int i = 0; i < number_of_elements; i++) printf("%d ", chunk[i]);

			printf("\n\nQuicksort %d ints on %d procs: %f secs\n",number_of_elements, number_of_process,time_taken);
	}

	MPI_Finalize();
	return 0;
}
