#pragma once

void heapify(int* A, int i, int size)
{
	int left = 2 * i+1;
	int right = 2 * i + 2;
	int max;
	if (left<size && A[left]>A[i])
		max = left;
	else
		max = i;
	if (right < size && A[right] > A[max])
		max = right;
	if (max != i)
	{
		int temp = A[i];
		A[i] = A[max];
		A[max] = temp;
		heapify(A, max, size);
	}
}


void buildHeap(int* A, int size)
{
	for (int i = size / 2; i >= 0; i--)
		heapify(A, i, size);
}


void heapSort(int* A, int size)
{
	int temp;
	buildHeap(A, size);
	while (size > 1)
	{
		temp = A[0];
		A[0] = A[size - 1];
		A[--size] = temp;
		heapify(A, 0, size);
	}
}


