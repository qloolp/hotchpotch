#pragma once
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
