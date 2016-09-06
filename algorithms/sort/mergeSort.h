#pragma once
#include <climits>
void merge(int* A, int p, int q, int r)
{
	int size1 = q - p + 1;
	int size2 = r - q;
	int* left = new int[size1 + 1];
	for (int i = 0; i < size1; i++)
		left[i] = A[p + i];
	left[size1] = INT_MAX;
	int* right = new int[size2 + 1];
	for (int i = 0; i < size1; i++)
		right[i] = A[q + 1 + i];
	right[size2] = INT_MAX;

	int i = 0, j = 0;
	for (q = p; q <= r; q++)
	{
		if (left[i] < right[j])
			A[q] = left[i++];
		else
			A[q] = right[j++];
	}
	delete[] left;
	delete[] right;

}

void mergeSort(int* A, int p, int r)
{

	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}