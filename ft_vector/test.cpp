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
	std::vector<int> empty;

	std::cout << empty.empty() << std::endl;
	empty.pop_back();
	return (1);
}	
