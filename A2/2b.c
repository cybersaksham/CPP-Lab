#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* PrintHello(void *data) {
	long int my_data = *(long int *)data;
	pthread_detach(pthread_self());
	pthread_t currId = pthread_self();
	printf("Hello from new thread (%ld) - got %ld\n", currId, my_data);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int rc;
	pthread_t thread_id;
		
	pthread_t currId = pthread_self();
	
	rc = pthread_create(&thread_id, NULL, PrintHello, (void *)&currId);
	if(rc) {
		printf("\n ERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	}
	
	printf("I am thread (%ld). Created new thread (%ld) ... \n", currId, thread_id);
	pthread_exit(NULL);
	
	return 0;
}
