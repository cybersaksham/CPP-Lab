#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

void *fun(void *arg) {
	double *arr = (double *)malloc(100 * sizeof(double));
	for(int i=0; i<100; i++) arr[i] = (double)sqrt(i);
	return (void *)arr;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, &fun, NULL);
	
	printf("Calculating square roots:\n");
	
	double *arr;
	pthread_join(tid, (void **)&arr);
	
	for(int i=0; i<100; i++) {
		printf("Square root of %d = %lf\n", i, arr[i]);
	}
	
	return 0;
}
