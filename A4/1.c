#include <stdio.h>
#include <pthread.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#define max 4

int count[max] = { 0 };
char str[200] = "Hello we are doing pthread testing with string";
char sub[200] = "in";

void* str_seq_count(void* args)
{
	int value = *(int*)args;
	int i, j, k, l1, l2, flag;

	l1 = strlen(str);

	l2 = strlen(sub);

	for (i = 0 + value; i < l1; i = i + max) {

		flag = 0;
		k = i;

		for (j = 0; j < l2; j++) {

			if (sub[j] == str[k])
				k++;
			else {
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			count[value] += 1;
	}
}

int main()
{
	int sum = 0;
	int x[max];
	for (int a = 0; a < max; a++)
		x[a] = a;
		
	int i, l1;

	pthread_t tid[max];

	for (i = 0; i < max; i++) {
		pthread_create(&tid[i], NULL,str_seq_count,(void*)&x[i]);
	}
	for (i = 0; i < max; i++)
		pthread_join(tid[i], NULL);
	for (i = 0; i < max; i++)
		sum = sum + count[i];
	printf("Substrings: %d\n",sum);

	return 0;
}
