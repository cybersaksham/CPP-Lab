#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define n 5

sem_t empty, freeWorker;
pthread_mutex_t lock, cmdLock;
pthread_cond_t cond;

int busyWorkers = 0;
int works = 0, workerCount = 0;
pthread_t tid[1000];

void *worker(void *arg) {
	int a = *(int *)arg;
	while(1) {
		pthread_mutex_lock(&cmdLock);
		if(workerCount == busyWorkers) pthread_cond_wait(&cond, &cmdLock);
		pthread_mutex_unlock(&cmdLock);
		sem_wait(&empty);
		pthread_mutex_lock(&lock);
		works--;
		printf("Worker %d: works left = %d\n", a, works);
		pthread_mutex_unlock(&lock);
		busyWorkers++;
		sleep(5);
		busyWorkers--;
		sem_post(&freeWorker);
	}
	free(arg);
}

void *boss(void *arg) {
	for(int i=0; i<n; i++) {
		int *a = (int *)malloc(sizeof(int *));		
		*a = workerCount++;
		pthread_create(tid+i, NULL, &worker, a);
	}
	while(1) {
		if(workerCount == busyWorkers) {
			int a;
			pthread_mutex_lock(&cmdLock);
			printf("Enter command = ");
			scanf("%d", &a);
			pthread_mutex_unlock(&cmdLock);
			if(a == 1) {
				pthread_mutex_lock(&lock);
				works++;
				printf("Boss: work added = %d\n", works);
				pthread_mutex_unlock(&lock);
				sem_post(&empty);
				pthread_cond_signal(&cond);
			} else if(a == 2) {
				int *a = (int *)malloc(sizeof(int *));		
				*a = workerCount++;
				pthread_create(&tid[workerCount-1], NULL, &worker, a);
				pthread_cond_signal(&cond);
			} else {
				pthread_cond_signal(&cond);
				sem_wait(&freeWorker);
			}
		} else {
			pthread_mutex_lock(&lock);
			works++;
			printf("Boss: work added = %d\n", works);
			pthread_mutex_unlock(&lock);
			sem_post(&empty);
		}
	}
}

int main() {
	sem_init(&empty, 0, 0);
	sem_init(&freeWorker, 0, 0);
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&cmdLock, NULL);
	
	pthread_t t1, t2;
	
	// pthread_create(&t1, NULL, &worker, NULL);
	pthread_create(&t2, NULL, &boss, NULL);
	
	// pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	return 0;
}
