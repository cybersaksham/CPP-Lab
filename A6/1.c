#include <stdio.h>
#include <omp.h>

int main() {
	#pragma omp parallel
	{
		#pragma omp single
		printf("No of threads = %d\n", omp_get_num_threads());
		printf("Hello World. TID = %d\n", omp_get_thread_num());
	}
	
	return 0;
}
