#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main() {
	#pragma omp parallel
	{
		int a, b;
		#pragma omp task depend(out:a)
		{
			sleep(1);
			a = 5;
		}
		#pragma omp task depend(out:b)
		b = 5;
		#pragma omp task depend(in:a, inout:b)
		{
			printf("%d %d\n", a, b);
			b = 10;
		}
		#pragma omp task depend(in:b)
		printf("%d\n", b);
	}
	
	return 0;
}
