#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int *arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	
	for(int j=low; j<high; j++) {
		if(arr[j] <= pivot) swap(arr + ++i, arr + j);
	}
	
	swap(arr + i + 1, arr + high);
	return i+1;
}

void quickSort(int *arr, int low, int high) {
	if(low < high) {
		int pi = partition(arr, low, high);
		#pragma omp task firstprivate(arr, low, pi)
		quickSort(arr, low, pi-1);
		#pragma omp task firstprivate(arr, high, pi)
		quickSort(arr, pi+1, high);
	}
}

void printArray(int arr[], int size) {
	for(int i=0; i<size; i++) printf("%d ", arr[i]);
	printf("\n");
}

int main() {
	int n;
	printf("Enter n = ");
	scanf("%d", &n);
	
	int *arr = (int *)malloc(n * sizeof(int));
	printf("Enter array\n");
	for(int i=0; i<n; i++) scanf("%d", &arr[i]);
	
	#pragma omp parallel
	{
		#pragma omp single nowait
		quickSort(arr, 0, n-1);
	}
	
	printf("Sorted Array\n");
	printArray(arr, n);
	
	return 0;
}
