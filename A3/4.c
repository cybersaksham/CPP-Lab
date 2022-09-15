#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define N 100

pthread_mutex_t lock;
char s[N] = "a";
char s2[N] = "b";

void *fun(void *arg) {
	char tmp[N];
	strcpy(tmp, s);
	pthread_mutex_lock(&lock);
	sleep(0.1);
	strcat(tmp, s2);
	strcpy(s, tmp);
	pthread_mutex_unlock(&lock);
}

int main() {
	pthread_mutex_init(&lock, NULL);
	
	pthread_t arr[N];
	
	for(int i=0; i<N; i++) {
		pthread_create(arr+i, NULL, &fun, NULL);
	}
	
	for(int i=0; i<N; i++) {
		pthread_join(arr[i], NULL);
	}
	
	// puts(s);
	printf("%ld\n", strlen(s));
	
	pthread_mutex_destroy(&lock);
	
	return 0;
}
