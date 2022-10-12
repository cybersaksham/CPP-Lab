#include <stdio.h>
#include <omp.h>
#include <time.h>
#define N 1000000

int arr[N];
clock_t start, end;

void parallelSection(int threads) {
	start = clock();
	int gsum = 0;
	#pragma omp parallel num_threads(threads)
	{
		int lsum = 0;
		#pragma omp for
		for(int i=0; i<N; i++) lsum += arr[i];
		#pragma omp critical
		gsum += lsum;
	}
	end = clock();
	double tm = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("No of threads = %d, Total sum = %d, Time taken = %lf\n", threads, gsum, tm);
}

int main() {
	for(int i=0; i<N; i++) arr[i] = 1;
	parallelSection(2);
	parallelSection(4);
	parallelSection(6);
	parallelSection(8);
	
	return 0;
}
