#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
	int max = 20;
	int sum = 0;
	/*
	#pragma omp parallel for reduction(+:sum) schedule(runtime)
	for(int i=1; i<=max; i++) {
		printf("%d -> %d\n", omp_get_thread_num(), i);
		sleep(i < 4 ? (i + 1) : 1);
		sum += i;
	}
	
	#pragma omp parallel for reduction(+:sum) schedule(dynamic, 1)
	for(int i=1; i<=max; i++) {
		printf("%d -> %d\n", omp_get_thread_num(), i);
		sleep(i < 4 ? (i + 1) : 1);
		sum += i;
	}
	
	#pragma omp parallel for reduction(+:sum) schedule(dynamic, 2)
	for(int i=1; i<=max; i++) {
		printf("%d -> %d\n", omp_get_thread_num(), i);
		sleep(i < 4 ? (i + 1) : 1);
		sum += i;
	}*/
	
	#pragma omp parallel for reduction(+:sum) schedule(dynamic, 3)
	for(int i=1; i<=max; i++) {
		printf("%d -> %d\n", omp_get_thread_num(), i);
		sleep(i < 4 ? (i + 1) : 1);
		sum += i;
	}
	
	printf("%d\n", sum);
	
	return 0;
}
