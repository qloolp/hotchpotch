#include "allocator.h"
using namespace li;

int main()
{
	allocator<int> all;
	int* p = all.allocate(10);
	for (int i = 0; i < 10; i++)
	{
		all.construct(p + i, i);
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << i << std::endl;
	}
	std::cin.get();
}