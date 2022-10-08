#include <vector>
#include <iostream> 

struct test
{
	int m;
};

int main(int ac,  char	**av)
{
	(void)ac;
	(void)av;
	typedef struct test test;
	test a;
	test b;
	a.m = 42;
	b.m = 1337;

	std::vector<test> vec(10, a);
	std::vector<test>::iterator it = vec.begin();
	it[-1] = b;
	std::cout << (it[-1]).m << std::endl;
	std::cout << vec.size() << " " << vec.capacity() << std::endl;
	return (0);
}

