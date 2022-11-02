#include <stdio.h>
#include <omp.h>

int main() {
	#pragma omp parallel
	printf("%d %d %d\n", omp_get_thread_limit(), omp_get_num_threads(), omp_get_thread_num());
	
	#pragma omp parallel num_threads(5)
	printf("%d %d %d\n", omp_get_thread_limit(), omp_get_num_threads(), omp_get_thread_num());
	
	return 0;
}
