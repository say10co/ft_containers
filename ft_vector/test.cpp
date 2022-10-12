#include <vector>
#include <iostream> 

struct test
{
	int m;
};

int main()
{
	char *s =  NULL;
	std::cout << (s + 1) << std::endl;
	return (0);
	typedef std::iterator_traits<test*> traits;
	std::cout << (typeid(std::random_access_iterator_tag) == typeid(traits::iterator_category) ) << std::endl;
	return (0);
}
int main1(int ac,  char	**av)
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

