#include <stdio.h>
#include <omp.h>

int main() {
	int max;
	scanf("%d", &max);
	int ts = omp_get_max_threads() ;
	if (max % ts != 0) return 1;
	
	int sums[ts];
	#pragma omp parallel
	{
		int t = omp_get_thread_num() ;
		int lo = ( max / ts ) * (t + 0) + 1;
		int hi = ( max / ts ) * (t + 1) + 0;
		sums [t] = 0;
		for(int i = lo; i <= hi; i++) sums[t] += i;
	}
	
	int sum = 0;
	for(int i=0; i<ts; i++) sum += sums[i];
	printf("Sum1 = %d\n", sum);
	
	#pragma omp parallel
	{
		#pragma omp for
		for(int t = 0; t < ts; t = t + 2) {
			#pragma omp task
			{
				int lo = t;
				int hi = t + 1;
				sums[lo] += sums[hi];
				if(lo > 0) sums[0] += sums[lo];
			}
		}
	}
	printf("Sum2 = %d\n", sums[0]);
	
	return 0;
}
