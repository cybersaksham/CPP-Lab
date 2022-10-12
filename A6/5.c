#include <stdio.h>
#include <omp.h>
#define N 100000
#define step 1000

int main() {
	int v1[N], v2[N];
	for(int i=0; i<N; i++) v1[i] = v2[i] = 1;
	
	int gsum = 0;
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0; i<N; i+=step) {
			int start = i;
			int end = start + step - 1;
			if(end >= N) end = N - 1;
			printf("Thread %d created task for %d to %d\n", omp_get_thread_num(), start, end);
			#pragma omp task
			{
				printf("Thread %d performing the task for %d to %d\n", omp_get_thread_num(), start, end);
				int lsum = 0;
				for(int j=start; j<=end; j++) lsum += (v1[j] * v2[j]);
				#pragma omp critical
				gsum += lsum;
			}
		}
	}
	
	printf("Result = %d\n", gsum);
	
	return 0;
}
