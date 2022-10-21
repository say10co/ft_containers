#include  <iostream>
#include <vector>

#include "inc/vector.hpp"
using namespace ft;
class Test
{
	private:

	public:
		char key;
		Test(char c)
		{
			key = c;
			//std::cout << "Test Constructor Called" << std::endl;
		}	
		~Test()
		{
			std::cout << "Test distructor called" << std::endl;
		}
		Test(const Test &test)
		{
			(void) test;
			this->key = test.get_key();
			//std::cout << "Test Copy Constructor Called" << std::endl;
		}
		char get_key() const
		{
			return (this->key);
		}
		Test &operator=(const Test &r)
		{
			this->key = r.key;
			//std::cout << "Assignment operator called" << std::endl;
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

	{
		vector<int> int_vec;
		vector<Test> test_vec(1, 'a');
		vector<Test>::reverse_iterator rit(test_vec.end());
		std::cout << "rit->key() " << rit->get_key() << std::endl; 
		int_vec.reserve(10);
		for (int i = 0; i < 10; i++)
			int_vec.push_back(i);
		vector<int>::reverse_iterator rit_e(int_vec.begin());
		vector<int>::reverse_iterator rit_b (int_vec.end());
		for (; rit_e != rit_b; )
			std::cout << "*rit : " << *--rit_e << std::endl; 
		return (1);
	}
	{
		vector<int> int_vec(1);
		vector<int>::const_iterator const_it = int_vec.begin();
		vector<int>::iterator  it = int_vec.begin();
		*it = 21;
		std::cout <<"*it : " <<  *const_it << std::endl;
		//return (1);
	}
	{
		std::cout << "TEST : iterator_traits " << std::endl;
		typedef	iterator_traites<const int *> test_trait;	
		std::cout << (typeid(test_trait::pointer) == typeid(const int* )) << std::endl;
		//return (1);
	}
	{

		std::cout << "TEST : vector.clear() " << std::endl;
		vector<Test> foo(4, 'Z');
		std::cout << "before clear" << std::endl;
		foo.clear();
		std::cout << "After clear" << std::endl;
		std::cout << "foo.zie() : "<<  foo.size() << " foo.capacity() : " << foo.capacity() << std::endl;
		//return (1);
	}
	{

		std::cout << "TEST : vector.swap() " << std::endl;
		vector<int> foo(3, 42);
		vector<int> bar(5, 21);
		foo.reserve(42);
		foo.swap(bar);
		std::cout << "foo.capacity() :" << foo.capacity() << std::endl;
		std::cout << "bar.capacity() :" << bar.capacity() << std::endl;
		std::cout << "foo : " ;
		for (unsigned int i = 0; i < foo.size(); i++)
			std::cout << foo[i] << " ";
		std::cout << std::endl << "bar : " ;
		for (unsigned int i = 0; i < bar.size(); i++)
			std::cout << bar[i] << " ";
		//return (1);

	}
	{
		std::cout << "TEST : vector.erase() " << std::endl;
		char arr[] = {'2', '3', '4', '5', '6', '7'};
		vector<Test> int_vec(arr, arr+6);	

		vector<Test>::iterator ret =  int_vec.erase(int_vec.end() -1 );
		std::cout << "ret :  " << *ret << std::endl;
		for (vector<Test>::iterator i = int_vec.begin(); i != int_vec.end(); i++)
			std::cout << "v :" << *i  << std::endl;
		std::cout << int_vec.size() << " " << int_vec.capacity() << std::endl;
		//return (1);
	}
	{
		std::cout << "TEST : vector.operator[]() " << std::endl;
		vector<Test>  test_vec(1, 'a');
		std::cout << "Before assigning "  << std::endl;
		test_vec[0] = 'z';
		std::cout << "After assigning "  << std::endl;
		//return (0);
	}
	{
		std::cout << "TEST : is_integral " << std::endl;
		std::cout << "int : " << is_integral<const int>::value << std::endl;
		//return (1);
	}
	{
		std::cout << "TEST : vector.insert() (1)(2)(3) " << std::endl;
		int arr[] = {42, 43, 44, 45, 46, 47};

		vector<int> int_vec;
		int_vec.reserve(50);
		int_vec.insert(int_vec.begin(), 6);
		int_vec.insert(int_vec.begin(), 5);
		int_vec.insert(int_vec.begin(), 4);

		int_vec.insert(int_vec.begin() + 1, 10, 1337);
		int_vec.insert(int_vec.begin() + 2,  arr, arr);

		for (vector<int>::iterator i = int_vec.begin(); i != int_vec.end(); i++)
			std::cout << "v :" << *i  << std::endl;
		std::cout << "size : " << int_vec.size() << " capacity : "
			<< int_vec.capacity() << std::endl;
		//return (1);

	}
	{

		std::cout << "TEST : vector.insert() (1)(2)(3) " << std::endl;
		vector<int> int_vec;
		int_vec.push_back(1);
		int_vec.push_back(2);
		int_vec.push_back(3);
		int_vec.insert(int_vec.end(), 4);
		int_vec.reserve(10);
		vector<int>::iterator it = int_vec.begin() + 2;
		std::cout << "insert iterator old_value : " << *it << std::endl;
		const int n   = 4; const int v = 1337;
		int_vec.insert(int_vec.end(), n,  v);
		std::cout << "Begin :" << *(int_vec.begin()) << " End :" << int_vec.back() << std::endl; 

		for (vector<int>::iterator i = int_vec.begin(); i != int_vec.end(); i++)
			std::cout << "v :" << *i  << std::endl;
		std::cout << "size : " << int_vec.size() << " capacity : "  << int_vec.capacity() << std::endl;
		//return (1);
	}
	{
		
		std::cout << "TEST : vector.pop_back() " << std::endl;
		vector<Test> test_vec;
		test_vec.push_back('a');
		test_vec.push_back('x');
		test_vec.pop_back();
		std::cout << test_vec[0] << std::endl;
		//return (1);
	}
	{
		std::cout << "TEST : vector.back() " << std::endl;
		vector<int> myvector;
		int sum (0);
		myvector.push_back (100);

		myvector.push_back (200);
		myvector.push_back (300);
		int &i = myvector.back();
		myvector.pop_back();
		i = 1337;
		std::cout << i << std::endl;
		while (!myvector.empty())
		{
			sum+=myvector.back();
			std::cout << "Back : " << myvector.back() << std::endl;
			myvector.pop_back();
		}
		std::cout << "The elements of myvector add up to " << sum << '\n';
		std::cout << "Capacity : " << myvector.capacity() << " size : " << myvector.size() << std::endl;
		//return (0);
	}
	/*
	   {
	   vector<Test> test_vec;
	   test_vec.push_back('y');
	   test_vec.push_back('z');
	   std::cout << "test_vec.begin() :" << *(test_vec.begin())
	   << " test_vec.back() : " << test_vec.back() << std::endl;
	   std::cout << "test_vec.size : " << test_vec.size() 
	   << " test_vector capacity : " << test_vec.capacity()<< std::endl;

	   vector<int> int_vec;
	   int i = 0;
	   do {
	   std::cout << "I = " << i << " _Capacity = " << int_vec.capacity() << std::endl;
	   int_vec.push_back(i++);
	   if (i == 50)
	   int_vec.shrink_to_fit();
	   } while (i < 200);
	   std::cout << "int_vec stores " << int(int_vec.size()) << " numbers.\n";
	   return 0;
	   }
	   */
	{
		//int arr[] =  {16, 13, 42, 1337};
		{
			vector<int> int_vec;
			int_vec.assign(7, 1337);
			for (vector<int>::iterator std_it = int_vec.begin(); std_it != int_vec.end(); std_it++)
				std::cout << "std::it value : " << *std_it << std::endl;
		}	

		char char_arr[] = {'a', 'b', 'c','d'};
		vector<char> first;
		first.assign(char_arr , char_arr+3);
		std::vector<char> char_first;
		char_first.assign(char_arr+1, char_arr+4);
		for (std::vector<char>::iterator std_it = char_first.begin(); std_it != char_first.end(); std_it++)
			std::cout << "std::it value : " << *std_it << std::endl;
		for (vector<char>::iterator it = first.begin(); it != first.end(); it++)
			std::cout << "it value : " << *it << std::endl;
		std::cout << "first size : " << first.size() << std::endl;
		std::cout << "first capacity : " << first.capacity() << std::endl;
		//return (1);
	}
	{
		vector<Test> t(10, 'c');
		t.front() = 'A'; std::cout << "t.front() " << t.front() <<  std::endl; 
		t.at(t.size() - 1) = 'P';
		std::cout << t.back() << std::endl;
		std::cout << "t.at(1) : " << t.at(1) << std::endl;
		std::cout << "t.at(0) : " << t.at(0) << std::endl;
		std::cout << t[0] << std::endl;
		return (1);
		t.reserve(20);
		std::cout << "T capacity : :" <<  t.capacity() << std::endl;
		std::cout << "T size : "  << t.size() << std::endl;
		//t.shrink_to_fit();
		std::cout << "T capacity : :" <<  t.capacity() << std::endl;
		std::cout << t.max_size() << std::endl;
		for (vector<Test>::const_iterator it  = t.begin(); it != t.end(); it++ )
			std::cout << *it << std::endl;
		t.resize(0, 'x');
		std::cout << std::endl << t.empty() << std::endl;

		return (1);	
		vector<Test>::iterator it = t.begin();
		vector<Test>::iterator it1;

		Test a('x');
		Test a1('9');
		Test a2('L');
		*it = a;
		*(it + 2) = a1; 

		it[0] = a2; 
		std::cout << it[0] << std::endl;
		return (1);
		std::cout << (std::addressof(it += 42) == std::addressof(it)) << std::endl;
		return (1);
		it1 = it + 1;
		vector<Test>::iterator tmp = (it += 1);	
		std::cout <<"(it == it1) " << (it == it1) << std::endl;
		return (1);
		std::cout <<"(it == it1) " << (it == it1) << std::endl;
		std::cout << "(it >= it1) "<< (it >= it1) << std::endl;
		std::cout << "(it <= it1) "<< (it <= it1) << std::endl;
		std::cout << "(it < it1) " << (it < it1) << std::endl;
		std::cout << "(it > it1) " << (it > it1) << std::endl;
std::cout << (it1 - --it) << std::endl;
		std::cout << "Crafted result : " << *(2 +  (++it - 1) ) << std::endl;
		std::cout << "Crafted result : " << *((1 + it) + 2 ) << std::endl;
		return (1);

		it++;
		std::cout << "------------" << std::endl;
		std::cout << "output 1 " << *it++ << std::endl;
		std::cout << "output 2 " << it1->key << std::endl;
		std::cout << "output 3 " << (--it)->key << std::endl;
		std::cout << "output 4 " << *it1 << std::endl;
		return (1);


		std::allocator<Test> alloc;
		Test* v = alloc.allocate(42);
		Test tl('*');
		alloc.construct(v, tl);
		return (1);
		vector<Test> v1(2, '*');
		vector<Test> v2(3, 'a');
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

}
