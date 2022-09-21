#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#define N 5

void *calc(void *arg) {
	int a = *(int *)arg;
	printf("Thread %d starting...\n", a);
	double res = 0;
	for(int i=0; i<=10000; i++) res += (sin(i) + tan(i));
	printf("Thread %d done. Result = %lf\n", a, res);
	pthread_exit(arg);
}

int main() {
	pthread_t tids[N];
	
	for(int i=0; i<N; i++) {
		int *a = (int *)malloc(sizeof(int *));
		*a = i;
		printf("Main: creating thread %d\n", i);
		pthread_create(tids+i, NULL, &calc, a);
	}
	
	for(int i=0; i<N; i++) {
		int *st;
		pthread_join(tids[i], (void **)&st);
		printf("Main: completed join with thread %d having a status of %d\n", i, *(int *)st);
	}
	
	return 0;
}
