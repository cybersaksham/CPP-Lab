#include <stdio.h>
#include <pthread.h>

int balance = 1000;
pthread_mutex_t lock;

void *deposit(void *arg) {
	for(int i=0; i<50; i++) {
		pthread_mutex_lock(&lock);
		balance += 50;
		printf("Depositted. Balance = %d\n", balance);
		pthread_mutex_unlock(&lock);
	}
}

void *withdraw(void *arg) {
	for(int i=0; i<20; i++) {
		pthread_mutex_lock(&lock);
		balance -= 20;
		printf("Withdrawn. Balance = %d\n", balance);
		pthread_mutex_unlock(&lock);
	}
}

int main() {
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, &deposit, NULL);
	pthread_create(&t2, NULL, &withdraw, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	return 0;
}
