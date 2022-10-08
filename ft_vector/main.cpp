#include  <iostream>
#include <vector>

#include "inc/ft_vector.hpp"

class Test
{
	private:

	public:
		char key;
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
			this->key = r.key;
			std::cout << "Assignment operator called" << std::endl;
			return (*this);
		}	
};
/*
template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator operator+(int n, const typename ft_vector<type, Alloc>::iterator &it)
{
	typedef typename ft_vector<type, Alloc>::value_type value_type; 
	typedef typename ft_vector<type, Alloc>::iterator iterator; 
	
	value_type *tmp_ptr = it._ptr;
	tmp_ptr += n * sizeof(value_type);
	iterator ret(tmp_ptr);
	return (ret);
}
*/
std::ostream &operator<<(std::ostream &os, const Test &t)
{
	os << t.get_key() ;
	return (os);
}

int main(int ac,  char	**av)
{
	(void)ac;
	(void)av;

/*
	ft_vector<char> vec(1, 'a');
	ft_vector<char>::iterator vec_it = vec.begin();
	--vec_it++;
	vec_it--;
	*vec_it = '*'; 
	std::cout << vec_it->key << std::endl;
	std::cout <<  *vec_it << std::endl;
	return (1);

*/
	ft_vector<Test> t(3, 'c');
	ft_vector<Test>::iterator it = t.begin();
	ft_vector<Test>::iterator it1;

	Test a('x');
	Test a1('*');
	*it = a;
	*(it + 2) = a1; 
	it1 = it--;
	std::cout << *(2 + ++it ) << std::endl;

	std::cout << "------------" << std::endl;
	std::cout << "output 1 " << *it++ << std::endl;
	std::cout << "output 2 " << it1->key << std::endl;
	std::cout << "output 3 " << (--it)->key << std::endl;
	std::cout << "output 4 " << *it1 << std::endl;
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
