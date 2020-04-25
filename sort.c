#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"

void merge(Input *in, int arr[], int head, int mid, int tail){
	int lenA = mid - head + 1;
	int lenB = tail - (mid+1) + 1;
	int A[lenA];
	int B[lenB];

	int i, j, k;
	for(i = 0; i < lenA; i++){
		A[i] = arr[head+i];
	}
	for(i = 0; i < lenB; i++){
		B[i] = arr[mid+1+i];
	}

	i = 0;
	j = 0;
	k = head;
	while(i < lenA && j < lenB){
		if(in->p[A[i]].R <= in->p[B[j]].R){
			arr[k] = A[i];
			i++;
		}
		else{
			arr[k] = B[j];
			j++;
		}
		k++;
	}

	while(i < lenA){
		arr[k] = A[i];
		i++;
		k++;
	}

	while(j < lenB){
		arr[k] = B[j];
		j++;
		k++;
	}
	return;
}

void merge_sort(Input *in, int arr[], int head, int tail){
	if(head < tail){
		int mid = (head + tail) / 2;
		merge_sort(in, arr, head, mid);
		merge_sort(in, arr, mid+1, tail);
		merge(in, arr, head, mid, tail);
	}
}