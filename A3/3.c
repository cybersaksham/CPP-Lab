#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arrSt{
	int size;
	int *start;
};

void merge(int *arr1, int m, int *arr2, int n) {
	int p = m + n;
	int *ans = (int *)malloc(p * sizeof(int));
	
	int i=0, j=0, k=0;
	while(i<m && j<n) {
		if(arr1[i] <= arr2[j]) ans[k++] = arr1[i++];
		else ans[k++] = arr2[j++];
	}
	while(i<m) ans[k++] = arr1[i++];
	while(j<n) ans[k++] = arr2[j++];
	
	k = 0;
	while(k < p) {
		arr1[k] = ans[k];
		k++;
	}
}

void *mergeSort(void *arg) {
	struct arrSt myarr = *(struct arrSt *)arg;
	int n = myarr.size;
	int *start = myarr.start;
	
	if(n <= 1) return NULL;
	
	int mid = n / 2;
	
	struct arrSt *arr1 = (struct arrSt *)malloc(sizeof(struct arrSt));
	(*arr1).size = mid;
	(*arr1).start = start;
	pthread_t tid1;
	pthread_create(&tid1, NULL, &mergeSort, arr1);
	
	struct arrSt *arr2 = (struct arrSt *)malloc(sizeof(struct arrSt));
	(*arr2).size = n - mid;
	(*arr2).start = start + mid;
	pthread_t tid2;
	pthread_create(&tid2, NULL, &mergeSort, arr2);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	merge(start, mid, start + mid, n - mid);
	
	free(arr1);
	free(arr2);
	
	return NULL;
}

int main() {
	int n;
	printf("Enter size of array = ");
	scanf("%d", &n);
	
	int *arr = (int *)malloc(n * sizeof(int));
	printf("Enter array\n");
	for(int i=0; i<n; i++) scanf("%d", arr+i);
	
	struct arrSt *arr1 = (struct arrSt *)malloc(sizeof(struct arrSt));
	(*arr1).size = n;
	(*arr1).start = arr;
	pthread_t tid;
	pthread_create(&tid, NULL, &mergeSort, arr1);
	pthread_join(tid, NULL);
	
	printf("Sorted array:\n");
	for(int i=0; i<n; i++) printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}
