#include "algorithm.h"


void Swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void InterchangeSort(int a[], int n){	
	int i,j;
	for ( i = 0; i < n - 1; i++){
		for ( j = i + 1; j < n; j++){
			if(a[i] < a[j]){
				Swap(&a[i], &a[j]);
			}
		}
	}
}


void SelectionSort(int a[], int n){
	int min,i,j; 
	for ( i = 0; i < n - 1; i++){
		min = i; 
		for( j = i + 1; j < n; j++)
	   	   if (a[j] < a[min])
		       min = j;
		if (min != i)
	   	   Swap(&a[min], &a[i]);
	}
}

void BubbleSort(int a[], int n){
	int i,j;
	for(i = 0; i< n-1; i++){
		for(j = n-1; j>i; j--){
			if(a[i] > a[j]){
				Swap(&a[i],&a[j]);
			}
		}
	}
}