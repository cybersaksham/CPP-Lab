#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define bufSize 10

sem_t empty;
sem_t full;
pthread_mutex_t lock;

int buffer[bufSize];
int ptr = 0;

void *producer(void *arg) {
	while(1) {
		int a = rand() % 100;
		printf("Producer waiting...\n");
		sem_wait(&empty);
		pthread_mutex_lock(&lock);
		buffer[ptr] = a;
		pthread_mutex_unlock(&lock);
		printf("Added %d to buffer at index %d\n", a, ptr++);
		sem_post(&full);
	}
}

void *consumer(void *arg) {
	while(1) {
		printf("Consumer waiting...\n");
		sem_wait(&full);
		pthread_mutex_lock(&lock);
		int a = buffer[--ptr];
		pthread_mutex_unlock(&lock);
		printf("Got %d from buffer from index %d\n", a, ptr);
		sem_post(&empty);
		sleep(1);
	}
}

int main() {
	pthread_t prod, con;
	pthread_mutex_init(&lock, NULL);
	sem_init(&empty, 0, bufSize);
	sem_init(&full, 0, 0);
	
	pthread_create(&prod, NULL, &producer, NULL);
	pthread_create(&con, NULL, &consumer, NULL);
	
	pthread_join(prod, NULL);
	pthread_join(con, NULL);
	
	pthread_mutex_destroy(&lock);
	sem_destroy(&empty);
	sem_destroy(&full);
}
