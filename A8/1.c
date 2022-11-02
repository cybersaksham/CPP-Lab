#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 10
#define M 2

int **matrixMultiply(int **A, int **B, int i, int j, int k) {
	int **C = (int **)malloc(M * sizeof(int *));
	for(int p=0; p<M; p++) {
		C[p] = (int *)malloc(M * sizeof(int));
	}
	
	for(int p=i; p<(i+M); p++) {
		for(int r=k; r<(k+M); r++) {
			int sum = 0;
			for(int q=j; q<(j+M); q++) sum += (A[p][q] * B[q][r]);
			C[p-i][r-k] = sum;
		}
	}	
	return C;
}

int main() {
	int **A = (int **)malloc(N * sizeof(int *));
	int **B = (int **)malloc(N * sizeof(int *));
	int **C = (int **)malloc(N * sizeof(int *));
	for(int p=0; p<N; p++) {
		A[p] = (int *)malloc(N * sizeof(int));
		B[p] = (int *)malloc(N * sizeof(int));
		C[p] = (int *)malloc(N * sizeof(int));
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			A[i][j] = B[i][j] = 1;
			C[i][j] = 0;
		}
	}
	
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			int x = N / M;
			for(int i=0; i<x; i++) {
				for(int j=0; j<x; j++) {
					int row = i * M;
					int col = j * M;
					for(int k=0; k<x; k++) {
						int **tmp = (int **)malloc(M * sizeof(int *));
						for(int p=0; p<M; p++) {
							tmp[p] = (int *)malloc(M * sizeof(int));
						}
						#pragma omp task shared(tmp)
						tmp = matrixMultiply(A, B, row, k*M, col);
						#pragma omp taskwait
						for(int p=0; p<M; p++) {
							for(int q=0; q<M; q++) {
								#pragma omp critical
								C[row+p][col+q] += tmp[p][q];
							}
						}
					}
				}
			}
		}
	}
	
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) printf("%d ", C[i][j]);
		printf("\n");
	}
	
	return 0;
}
