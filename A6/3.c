#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#define N 1000

int main() {
	int ptr = 0;
	int buffer[N];

	#pragma omp parallel num_threads(2)
	{
		int tid = omp_get_thread_num();
		if(tid == 0) {
			while(1) {
				while(ptr == N);
				#pragma omp critical
				{
					buffer[ptr] = ptr;
					printf("Added %d to buffer\n", ptr);
					ptr++;
				}
				//sleep(0.9);
			}
		}
		else {
			while(1) {
				while(ptr == 0);
				#pragma omp critical
				{
					int a = buffer[ptr - 1];
					printf("Consumed %d from buffer\n", a);
					ptr--;
				}
				sleep(1);
			}
		}
	}
	
	return 0;
}
