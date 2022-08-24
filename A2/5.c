#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* PrintHello(void *data) {
	pthread_detach(pthread_self());
	int my_data = *(int*)data;
	pthread_t currId = pthread_self();
	printf("Hello from new thread (%ld) - created in iteration %d\n", currId, my_data);
	free(data);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int n;
	printf("Enter no of threads = ");
	scanf("%d", &n);
	
	pthread_t currId = pthread_self();
	pthread_t *tids = (pthread_t *)malloc(n * sizeof(pthread_t));
	
	for(int i=0; i<n; i++) {
		if(i%5 == 1) sleep(1);
		
		int rc;
	
		int *x = (int *)malloc(sizeof(int));
		*x = i;
		rc = pthread_create(tids + i, NULL, PrintHello, (void *)x);
		if(rc) {
			printf("\n ERROR: return code from pthread_create is %d \n", rc);
			exit(1);
		}
		
		printf("I am main thread (%ld). Created new thread (%ld) in iteration %d\n", currId, tids[i], i);
	}
	
	pthread_exit(NULL);
	
	return 0;
}
