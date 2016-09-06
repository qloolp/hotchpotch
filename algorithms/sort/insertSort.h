#pragma once
void insertSort(int* A, int size)
{
	int key;
	int j;
	for (int i = 1; i < size; i++)
	{
		key = A[i];
		j = i - 1;
		while (j >= 0 && A[j]>key)
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}
}
