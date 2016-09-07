#pragma once
/*
¼Ù¶¨ÊäÈë·¶Î§Îª[0,k]
*/
#include <iostream>
void countSort(int* A, int* B, int k, int size)
{
	int* C = new int[k+1];
	for (int i = 0; i <= k; i++)
	{
		C[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		C[A[i]] = C[A[i]] + 1;
	}
	for (int i = 1; i <= k; i++)
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		int temp = C[A[i]];
		B[C[A[i]]-1] = A[i];
		std::cout <<"B["<<temp<<"]:"<< B[C[A[i]]] << "   ";
		C[A[i]] = C[A[i]] - 1;
	}
	std::cout << std::endl;
}