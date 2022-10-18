#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

struct Test
{
	int m;
};

int main(int ac,  char	**av)
{
ac--; av--;
std::allocator<int> allocator;
	int *n = allocator.allocate(0);
	allocator.deallocate(n, 0);
		return (0);
}

