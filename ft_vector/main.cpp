#include  <iostream>
#include <vector>

#include "inc/ft_vector.hpp"

class Test
{
	private:

		char key;
	public:
		Test(char c)
		{
			key = c;
			std::cout << "Test Constructor Called" << std::endl;
		}	
		~Test()
		{
			std::cout << "Test distructor called" << std::endl;
		}
		Test(const Test &test)
		{
			(void) test;
			this->key = test.get_key();
			std::cout << "Test Copy Constructor Called" << std::endl;
		}
		char get_key() const
		{
			return (this->key);
		}
		Test &operator=(const Test &r)
		{
			(void) r;
			std::cout << "Assignment operator called" << std::endl;
			return (*this);
		}	
};

std::ostream &operator<<(std::ostream &os, const Test &t)
{
	os << t.get_key() ;
	return (os);
}

int main(int ac,  char	**av)
{
	(void)ac;
	(void)av;

	ft_vector<Test> t(1, 'c');
	ft_vector<Test>::iterator it = t.begin();
	ft_vector<Test>::iterator it1;

	it1 = it;
	std::cout << *it1 << std::endl;
	return (1);
	
/*	
	std::allocator<Test> alloc;
	Test* v = alloc.allocate(42);
	Test t('*');
	alloc.construct(v, t);
	return (1);
*/
	ft_vector<Test> v1(2, '*');
	ft_vector<Test> v2(3, 'a');
	v1 = v2;

	//std::vector<Test> v3(2, 'R');
	//std::vector<Test> v4(2, 'I');
	//v3 = v4;

	std::cout << "Size v1: " << v1.size() << " Capacity v1: " << v1.capacity() << std::endl;
	std::cout << "Size v2 : " << v2.size() << " Capacity v2 : " << v2.capacity() << std::endl;

	//std::cout << "Size v1: " << v3.size() << " Capacity v1: " << v3.capacity() << std::endl;
	//std::cout << "Size v2 : " << v4.size() << " Capacity v2 : " << v4.capacity() << std::endl;
	return (0);
}

