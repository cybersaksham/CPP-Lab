#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* PrintHello(void *data) {
	pthread_t my_data = *(pthread_t *)data;
	pthread_join(my_data, NULL);
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
	
	sleep(1);
	printf("I am thread (%ld). Created new thread (%ld) ... \n", currId, thread_id);
	pthread_exit(NULL);
	
	return 0;
}
