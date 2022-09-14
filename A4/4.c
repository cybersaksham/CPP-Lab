#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define bufSize 10

pthread_mutex_t lock;

int buffer[bufSize];
int ptr = 0;
int isFull = 0;
int isEmpty = 1;

void *producer(void *arg) {
	while(1) {
		int a = rand() % 100;
		while(isFull) sleep(1);
		pthread_mutex_lock(&lock);
		buffer[ptr++] = a;
		int b = ptr;
		isEmpty = 0;
		if(ptr == bufSize) isFull = 1;
		printf("Added %d to buffer at index %d\n", a, b-1);
		pthread_mutex_unlock(&lock);
	}
}

void *consumer(void *arg) {
	while(1) {
		while(isEmpty) sleep(1);
		pthread_mutex_lock(&lock);
		int a = buffer[--ptr];
		int b = ptr;
		isFull = 0;
		if(ptr == 0) isEmpty = 1;
		printf("Got %d from buffer from index %d\n", a, b);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

int main() {
	pthread_t prod, con;
	pthread_mutex_init(&lock, NULL);
	
	pthread_create(&prod, NULL, &producer, NULL);
	pthread_create(&con, NULL, &consumer, NULL);
	
	pthread_join(prod, NULL);
	pthread_join(con, NULL);
	
	pthread_mutex_destroy(&lock);
}
