#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int *arr, int low, int mid, int high) {
	int m = mid - low + 1, n = high - mid;
	int *tmp = (int *)malloc((m+n) * sizeof(int));
	int i=low, j=mid+1, k=0;
	
	while(i<=mid && j<=high) {
		if(arr[i] <= arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while(i<=mid) tmp[k++] = arr[i++];
	while(j<=high) tmp[k++] = arr[j++];
	
	for(int p=0; p<(m+n); p++) arr[low+p] = tmp[p];
	free(tmp);
}

void mergesort(int *arr, int low, int high) {
	if(low >= high) return;
	int mid = low + (high - low) / 2;
	#pragma omp task shared(arr)
	mergesort(arr, low, mid);
	#pragma omp task shared(arr)
	mergesort(arr, mid+1, high);
	#pragma omp taskwait
	merge(arr, low, mid, high);
}

int main() {
	int n;
	scanf("%d", &n);
	
	int *arr = (int *)malloc(n * sizeof(int));
	for(int i=0; i<n; i++) scanf("%d", arr+i);
	
	#pragma omp parallel
	{
		#pragma omp single nowait
		mergesort(arr, 0, n-1);
	}
	
	printf("Sorted Array:\n");
	for(int i=0; i<n; i++) printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}
