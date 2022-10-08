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
	Test test;
	test.m = 42;
	(void)ac;
	(void)av;
	std::vector<int> a(20, 42);
	std::vector<int>::iterator it = a.begin();
	*(15 + it) = 13;
	std::cout << *( 15 + it) << std::endl;
	return (0);
}

