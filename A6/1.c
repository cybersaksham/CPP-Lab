#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int a = 0;
#pragma omp threadprivate(a)

int main() {
	#pragma omp parallel
	{
		#pragma omp master
		{
			printf("%d\n", a);
			a++;
			printf("No of threads = %d\n", omp_get_num_threads());
		}
		printf("Hello World. TID = %d\n", omp_get_thread_num());
	}
	#pragma omp parallel
	{
		#pragma omp master
		printf("%d\n", a);
		#pragma omp single nowait
		{
			printf("Single thread enters\n");
			sleep(1);
		}
		printf("Thread %d waiting\n", omp_get_thread_num());
		#pragma omp barrier
		printf("After barrier\n");
	}
	
	return 0;
}
