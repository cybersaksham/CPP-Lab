#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fun(void *arg) {
	int ind = *(int *)arg;
	for(int i=0; i<5; i++) {
		printf("Hello, World (thread %d)\n", ind);
	}
}	

int main() {
	pthread_t arr[10];
	
	for(int i=0; i<10; i++) {
		int *a = (int *)malloc(sizeof(int));
		*a = i;
		pthread_create(arr+i, NULL, &fun, a);
	}
	
	for(int i=0; i<10; i++) {
		pthread_join(arr[i], NULL);
	}
	
	return 0;
}
