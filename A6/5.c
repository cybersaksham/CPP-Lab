#include <stdio.h>
#include <omp.h>
#define N 10
#define step 3

int main() {
	int v1[N][N], v2[N][1], v3[N][1];
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) v1[i][j] = 1;
		v2[i][0] = 1;
		v3[i][0] = 0;
	}
	
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0; i<N; i+=step) {
			int start = i;
			int end = start + step - 1;
			if(end >= N) end = N;
			
			printf("Thread %d created task for rows %d to %d\n", omp_get_thread_num(), start, end);
			#pragma omp task
			{
				printf("Thread %d started task for rows %d to %d\n", omp_get_thread_num(), start, end);
				for(int k=start; k<=end; k++) {
					for(int j=0; j<N; j++) {
						v3[k][0] += (v1[k][j] * v2[j][0]);
					}
				}
			}
		}
	}
	
	printf("Result:\n");
	for(int i=0; i<N; i++) printf("%d\n", v3[i][0]);
	
	return 0;
}
