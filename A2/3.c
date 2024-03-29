#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* PrintHello(void *data) {
	int my_data = *(int *)data;
	pthread_detach(pthread_self());
	sleep(1);
	printf("Hello from new thread - got %d\n", my_data);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int rc;
	pthread_t thread_id;
	int t = 11;
	
	rc = pthread_create(&thread_id, NULL, PrintHello, (void *)&t);
	if(rc) {
		printf("\n ERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	}
	
	printf("Created new thread (%ld) ... \n", thread_id);
	// pthread_exit(NULL);
	
	return 0;
}
