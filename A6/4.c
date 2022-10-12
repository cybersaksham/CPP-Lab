#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#define N 8

int main() {
	FILE *ptr = fopen("input.txt", "r");
	if(ptr == NULL) {
		printf("Couldn't open file input.txt\n");
		return 0;
	}
	
	char ch;
	int start = 0, end = 0, empty = 1, full = 0;
	char buffer[N];
	
	#pragma omp parallel num_threads(2)
	{
		int tid = omp_get_thread_num();
		if(tid == 0) {
			while(ch != EOF) {
				while(full);
				ch = fgetc(ptr);
				#pragma omp critical
				{
					buffer[end] = ch;
					//printf("Added %c to buffer\n", ch);
					end = (end + 1) % N;
					empty = 0;
					if(end == start) full = 1;
				}
				//sleep(0.9);
			}
		}
		else {
			while(ch != EOF || (start != end)) {
				while(empty);
				#pragma omp critical
				{
					char a = buffer[start];
					//printf("Consumed %c from buffer\n", a);
					printf("%c", a);
					start = (start + 1) % N;
					full = 0;
					if(start == end) empty = 1;
				}
				//sleep(1);
			}
		}
	}
	
	return 0;
}
