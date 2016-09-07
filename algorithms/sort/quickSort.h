#pragma once
#include <algorithm>
void quickSort(int* A, int first, int last)
{
	if (first >= last)
		return;
	int p = first;
	int q = last;
	int key = A[p];
	while (p < q)
	{
		while (p < q && A[q] >= key)
			q--;
		A[p] = A[q];
		while (p < q && A[p] <= key)
			p++;
		A[q] = A[p];
	}
	A[p] = key;
	quickSort(A, first, p);
	quickSort(A, q + 1, last);
}


int partition(int* A, int p, int r)
{
	int key = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= key)
		{
			i = i + 1;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[r]);
	return i + 1;
}

void quickSort1(int*A, int first, int last)
{
	if (first < last)
	{
		int q = partition(A, first, last);
		quickSort1(A, first, q - 1);
		quickSort1(A, q + 1, last);
	}
}