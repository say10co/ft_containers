#include  <iostream>
#include <vector>

#include "src/ft_vector.tpp"

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
			std::cout << "Test Copy Constructor Called" << std::endl;
		}
		char get_key() const
		{
			return (this->key);
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
	
	std::allocator<Test > alloc;
	Test* v = alloc.allocate(42);
	Test t('*');
	alloc.construct(v, t);
	std::vector<Test> v1(v, v + 42 *  (sizeof(Test)));
	for (int i=0; i < 42; i++)
		std::cout << "value : " << v1[i] << std::endl;
	return 1;	
	ft_vector<int> my_vec;

	ft_vector<Test> range_vec(42, '*');
	std::cout << "my_vec size "  << my_vec.size()  << " my_vec capacity : " << my_vec.capacity()<<  std::endl;
	std::cout << "range_vec size "  << range_vec.size()  << " range_vec  capacity : " << range_vec.capacity()<<  std::endl;


	/*
	std::allocator<int> alloc;
	alloc.deallocate(alloc.allocate(42), 42);
	ft_vector<int> vec_int;
	ft_vector<int> vec_char(13, 42); // calling Range constructor instrad of fill constructo 
	int int_ptr[] = {1, 2, 3, 4,5 ,6, 7, 8};
	ft_vector<int> range_vec(int_ptr, int_ptr + (sizeof(int_ptr) / sizeof(*int_ptr)));
	ft_vector<int> cp_vector(vec_int);
	*/
	return (0);
}

