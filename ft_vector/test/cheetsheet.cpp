#include <memory> // for std::allocator
#include <iostream>
#include <vector>

class Test_Allocator { 

	private: 
		int m_value;

	public:
		Test_Allocator()
		{
				m_value = 1337;
				std::cout << "Test_Allocator Called" << std::endl;
		}
		Test_Allocator(const int val) 
		{
			m_value = val;
			std::cout << "Test_Allocator Parameterised  constructor  Called" << std::endl;
		}
		Test_Allocator(const char *s)
		{
				(void) s;
		}
		int getvalue(void ) const
		{
			return this->m_value ;
		}
		//std::ostream& operator<<(std::ostream &os, const Test_Allocator &operand) const; 
};

std::ostream& operator<<(std::ostream &os, const Test_Allocator &operand)
{
	os << operand.getvalue();
	return (os);
}

int main(int ac,  char	**av)
{

	(void)ac;
	(void)av;

	/*	

		Test_Allocator *test = new Test_Allocator[10];
		std::allocator<Test_Allocator> Allocator;


		std::cout << "Allcator Allocation " << std::endl;
		Test_Allocator *test1 = Allocator.allocate(10);

	//Allocator.construct(test1[0], 42); //unsuported by the standard 
	test1[0] = 100;
	std::cout << "Constructed Allocator value " << test1[0] << std::endl;
	(void) test;
	(void) test1;

	std::vector<Test_Allocator> *vec = new std::vector<Test_Allocator>(42);
	std::cout << "Vector size : " <<  vec->size() << " Vector Cpacity " << vec->capacity()  << std::endl;
	size_t vec_capacity = vec->capacity();
	vec->push_back(Test_Allocator() );
	if (vec->capacity() != vec_capacity)
	std::cout << "New  Capacity : " << vec->capacity() << std::endl;
	*/
	typedef std::vector<Test_Allocator>::iterator int_it;

	std::vector<Test_Allocator> test;
	test.push_back(Test_Allocator(42));
	test.resize(13, "hello"); 
	for (int_it i = test.begin(); i != test.end(); i++)
		std::cout << *i << std::endl;
	std::cout << test.capacity() << std::endl;
	/*	
		std::vector<int>::iterator it  = test.begin();
		std::cout << *it << std::endl;
		*/
	return (0);
}

