#include <stdio.h>
#include <omp.h>
#define N 5

int main() {
	int A[N][N], B[N][N], C[N][N];
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			A[i][j] = 1;
			B[i][j] = 1;
			C[i][j] = 0;
		}
	}
	
	printf("Way 1:\n");
	#pragma omp parallel num_threads(4)
	{
		int count = 0;
		#pragma omp for
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				for(int k=0; k<N; k++) {
					C[i][j] = A[i][k] * B[k][j];
					count++;
				}
			}
		}
		printf("TID %d -> %d dot products\n", omp_get_thread_num(), count);
	}
	
	printf("\nWay 2:\n");
	#pragma omp parallel num_threads(4)
	{
		int count = 0;
		#pragma omp for collapse(2)
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				//printf("%d %d %d\n", omp_get_thread_num(), i, j);
				for(int k=0; k<N; k++) {
					C[i][j] = A[i][k] * B[k][j];
					count++;
				}
			}
		}
		printf("TID %d -> %d dot products\n", omp_get_thread_num(), count);
	}
	
	printf("\nWay 3:\n");
	#pragma omp parallel num_threads(4)
	{
		int count = 0;
		#pragma omp for
		for(int i=0; i<N; i++) {
			#pragma omp parallel for
			for(int j=0; j<N; j++) {
				for(int k=0; k<N; k++) {
					C[i][j] = A[i][k] * B[k][j];
					count++;
				}
			}
		}
		printf("TID %d -> %d dot products\n", omp_get_thread_num(), count);
	}
	
	return 0;
}
