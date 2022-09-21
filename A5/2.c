#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;
pthread_cond_t cond;
int account = 1000;

int deposit(int amt) {
	account += amt;
	printf("Deposited. Account = %d\n", account);
}

int withdrawal(int amt) {
	account -= amt;
	printf("Withdrawan. Account = %d\n", account);
}

void *depositThread(void *arg) {
	while(1) {
		pthread_mutex_lock(&mut);
		deposit(1);
		pthread_mutex_unlock(&mut);
		if(account >= 1000) pthread_cond_signal(&cond);
		sleep(1);
	}
}

void *withdrawThread(void *arg) {
	while(1) {
		pthread_mutex_lock(&mut);
		if(account < 1000) pthread_cond_wait(&cond, &mut);
		withdrawal(1);
		pthread_mutex_unlock(&mut);
	}
}

int main() {
	pthread_mutex_init(&mut, NULL);
	
	pthread_t t1, t2;
	pthread_create(&t1, NULL, &depositThread, NULL);
	pthread_create(&t2, NULL, &withdrawThread, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	pthread_mutex_init(&mut, NULL);
	
	return 0;
}
