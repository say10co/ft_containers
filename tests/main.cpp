#include <iostream>
#include "../RBT/RBT.hpp"
#include "../ft_map/source/map.hpp"
#include "../ft_vector/source/vector.hpp"
#include "../ft_stack/source/stack.hpp"
#include "../utils/pair.hpp"
#include <unistd.h>
#include <map>
#include  <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <stack>
#include <vector>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

#if MAP

	template <typename value_type, typename Alloc>
	void check_parent(const Node<value_type, Alloc> *node)
	{
		if (!node)
			return ;
		if ((node->_child[LEFT]))
		{
			if ((node->_child[LEFT]->_parent) == node)
				std::cout << "parent ok" << std::endl;
			else
				std::cout << "!!!!!!!!" << std::endl;
		}
		if ((node->_child[RIGHT]))
		{
			if ((node->_child[RIGHT]->_parent) == node)
				std::cout << "parent ok" << std::endl;
			else
				std::cout << "!!!!!!!!" << std::endl;
		}
		check_parent(node->_child[LEFT]);
		check_parent(node->_child[RIGHT]);
	}
	
	int main(int ac,  char	**av)
	{
		(void)ac;
		(void)av;
	
		{
			NAMESPACE::pair<int, std::string > arr[] = {
				NAMESPACE::make_pair(1, "42"),
				NAMESPACE::make_pair(2, "43"),
				NAMESPACE::make_pair(3, "44"),
				NAMESPACE::make_pair(4, "45"),
				NAMESPACE::make_pair(5, "46"),
				NAMESPACE::make_pair(6, "47"),
				NAMESPACE::make_pair(7, "48")
	
			};
			NAMESPACE::map<int, std::string > my_map(arr, arr+sizeof(arr)/ sizeof(arr[0]));
			NAMESPACE::map<int, std::string> my_second_map = my_map;
			NAMESPACE::map<int, std::string>::iterator it = my_second_map.begin();
			for (; it != my_second_map.end(); it++)
				std::cout << it->first << " " << it->second << std::endl;	
			return (1);
	
		}                                                                	
		{                                                                	
			NAMESPACE::map<char,int> mymap;                                     	
			// Iterator with default comparison object std::less         	
			NAMESPACE::map<char,int>::iterator it;                              	
	
			// Iterator with comparison object std::grater               
			NAMESPACE::map<char,int, std::greater<int> >::iterator my_it(mymap.begin()); // Compiles OK 
			(void) my_it;                                               	
			return 1;                                                   	
	
		}
		{
			std::map<char, std::string> m;
			NAMESPACE::map<char, std::string> ft_m;
	
			m['a'] = "an element";
			m['b'] = "another element";
			m['c'] = m['b'];
			m['a'] = "test";
	
			ft_m['a'] = "an element";
			std::cout << "ft_m['a'] " << ft_m['a'] << std::endl;
			return 1;
			ft_m['b'] = "another element";
			ft_m['c'] = ft_m['b'];
			ft_m['a'] = "test";
			std::cout << "std::map : " << m['a'] << m['b'] <<  m['c']<< std::endl;
			std::cout << "NAMESPACE::map : " << ft_m['a'] << ft_m['b']<< ft_m['c']<< std::endl;
	
			EQUAL(m['a'] == ft_m['a'] && m['b'] == ft_m['b'] && m['c'] == ft_m['c'] && m.size() == ft_m.size());
			return 1;
	
			NAMESPACE::map<int, std::string > my_map;
			for (size_t i = 0; i < 1e6; i++)
			{
				my_map[i] = "stack_overflow";	
			}
			return (1);
	
		}
		{
			NAMESPACE::pair<int, std::string > arr[] = {
				NAMESPACE::make_pair(1, "42"),
				NAMESPACE::make_pair(2, "43"),
				NAMESPACE::make_pair(3, "44"),
				NAMESPACE::make_pair(4, "45"),
				NAMESPACE::make_pair(5, "46"),
				NAMESPACE::make_pair(6, "47"),
				NAMESPACE::make_pair(7, "48")
	
			};
			NAMESPACE::map<int, std::string > my_map(arr, arr+sizeof(arr)/ sizeof(arr[0]));
			NAMESPACE::map<int, std::string> my_second_map = my_map;
	
			for (int i = 0; i < 10; i++)
				my_map[i] = "10e5";
	
			{
				std::cout << "my_map size :"<< my_map.size() << std::endl;
				std::cout << "my_map " << std::endl;
				std::cout << "my_second_map size :"<< my_second_map.size() << std::endl;
				std::cout << "my_second_map " << std::endl;
			}
	
			my_second_map.swap(my_map);
			NAMESPACE::map<int, std::string>::iterator tmp_end = my_second_map.end();
			std::cout << (--tmp_end)->first << std::endl;
			std::cout << (++tmp_end == my_second_map.end()) << std::endl;
			{
				std::cout << "my_map size :"<< my_map.size() << std::endl;
				std::cout << "my_map " << std::endl;
				std::cout << "my_second_map size :"<< my_second_map.size() << std::endl;
				std::cout << "my_second_map " << std::endl;
			}
			std::cout << "found value :" <<   my_map.find(7)->second << std::endl;
			my_second_map.clear();
	
			const NAMESPACE::map<int, std::string> const_map(my_map);				
			std::cout << "const_map found value :" <<   const_map.find(7)->second << std::endl;
	
			my_second_map.insert(NAMESPACE::make_pair(1, "shiiit"));
			my_second_map.insert(my_second_map.begin(), NAMESPACE::make_pair(1, "shiiit"));
			my_map.insert(NAMESPACE::make_pair(1, "shiiit"));
			my_map[1] = "shiiiiit";
			my_map[0] = "zerooo";
			my_map.erase(1);
			my_map.erase(0);
			std::cout << "After erase call" << std::endl;
			typedef NAMESPACE::map<int, std::string>::const_iterator c_iterator;
			for (c_iterator it = my_map.begin(); it != my_map.end(); )
			{
				std::cout << "key  : " << it->first ;
				std::cout << " associated value : " << it->second << std::endl;
				my_map.erase(it++);
			}
			std::cout << "After erasing all" << std::endl;
			std::cout << "my_map size : " << my_map.size() << std::endl;
			my_map.swap(my_second_map);
			std::cout << "my_map size : " << my_map.size() << std::endl;
			std::cout << my_second_map.count(1) << std::endl;
			{
				NAMESPACE::map<char,int> mymap;
				NAMESPACE::map<char,int>::iterator itlow,itup;
	
				mymap['a']=20;
				mymap['b']=40;
				mymap['c']=60;
				mymap['d']=80;
				mymap['e']=100;
	
				itlow=mymap.lower_bound ('b');  // itlow points to b
				itup=mymap.upper_bound ('d');   // itup points to e (not d!)
				std::cout << "lower bound " << itlow->first << std::endl;
				std::cout << "upper bound " << itup->first << std::endl;
			}
			{
				NAMESPACE::map<char,int> mymap;
	
				mymap['a']=10;
				mymap['b']=20;
				mymap['c']=30;
	
				NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,NAMESPACE::map<char,int>::iterator> ret;
				ret = mymap.equal_range('b');
	
				std::cout << "lower bound points to: ";
				std::cout << ret.first->first << " => " << ret.first->second << '\n';
	
				std::cout << "upper bound points to: ";
				std::cout << ret.second->first << " => " << ret.second->second << '\n';
			}
			{
				NAMESPACE::map<char,int> foo,bar;
				foo['a']=100;
				foo['b']=200;
				bar['a']=10;
				bar['z']=1000;
	
				if (foo==bar) std::cout << "foo and bar are equal\n";
				if (foo!=bar) std::cout << "foo and bar are not equal\n";
				if (foo< bar) std::cout << "foo is less than bar\n";
				if (foo> bar) std::cout << "foo is greater than bar\n";
				if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
				if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		}
		{
	
			NAMESPACE::map<char,int> mymap;
	
			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;
	
			// show content:
			NAMESPACE::map<char,int>::const_reverse_iterator rit;
			for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << '\n';
		}
		return (1);
	
	}
}

#endif 

#if VECTOR

	using namespace NAMESPACE;
	
	class Test
	{
		private:
	
		public:
			char key;
			Test() : key('A'){}
			Test(char c)
			{
				key = c;
			}	
			~Test()
			{
			}
			Test(const Test &test)
			{
				(void) test;
				this->key = test.get_key();
			}
			char get_key() const
			{
				return (this->key);
			}
			Test &operator=(const Test &r)
			{
				this->key = r.key;
				return (*this);
			}	
	};
	std::ostream &operator<<(std::ostream &os, const Test &t)
	{
		os << t.get_key() ;
		return (os);
	}
	
		template < typename T1>
	bool pred(const T1 &a, const T1 &b)
	{	
		return (a == b);
	}
	
	bool hello(int  a, int b)
	{	
		return (a == b);
	}
	
	int main(int ac,  char	**av)
	{
		(void)ac;
		(void)av;
	
		{
			vector<Test> int_vec;
			int_vec.reserve(100);
			for (int i = 0; i < 10; i++)
				int_vec.push_back(i + 48);
	
			std::cout << "------------" << std::endl;
			int_vec.erase(int_vec.begin());
			for (vector<Test>::iterator it = int_vec.begin(); it != int_vec.end() ; it++)
				std::cout << *it << " ";
			return 1;
		}
	
		{
			{
				bool eq;
	
				std::string str = "Hello World";
				std::string str1 = "HELLO WORLD";
				const char *c_str = "Hello World";
	
				eq = NAMESPACE::equal(str.begin(), str.end(), str1.begin(), pred<char>);
				std::cout << std::boolalpha << eq << std::endl; 
	
				eq = NAMESPACE::equal(str.begin(), str.end(), c_str, pred<char>);
				std::cout << std::boolalpha << eq << std::endl; 
	
			}
			{
				bool eq;
	
				std::string str = "Hello World";
				std::string str1 = "HELLO WORLD";
				const char *c_str = "Hello World";
	
				eq = NAMESPACE::equal(str.begin(), str.end(), str1.begin());
				std::cout << std::boolalpha << eq << std::endl; 
	
				eq = NAMESPACE::equal(str.begin(), str.end(), c_str);
				std::cout << std::boolalpha << eq << std::endl; 
			}
			return 1;
		}
		{
	
			{
				pair<const char *, unsigned int > str_uint = make_pair("hello", 42);
				std::cout << "first :" << str_uint.first << " second :" << str_uint.second << std::endl;
				return  1;
			}
			{
				pair<std::string, unsigned int > str_uint("hello", 42);
				pair<std::string, int > str_int(std::string("hello 1337"), 1337);
				str_uint = str_int;
				std::cout << "first :" << str_uint.first << " second :" << str_uint.second << std::endl;
				return 1;
			}
			{
				pair<int, Test> int_test;
				std::cout << "first :" << int_test.first << " second :" << int_test.second << std::endl;
				pair<int, char> int_char(42, 'X');
				std::cout << "first :" << int_char.first << " second :" << int_char.second << std::endl;
				int_test = int_char; 
				std::cout << "first :" << int_test.first << " second :" << int_test.second << std::endl;
			}
	
			return (1);
		}
		{
			vector<int> int_vec(10, 10);
			vector<int> int_vec1(10, 11);
			int_vec1.swap(int_vec);
	
			return (1);
		}
		{
			std::istringstream s("12345678901234567890");
			std::istreambuf_iterator<char> begin(s), end;
			vector<char> char_vec(begin, end);
			return 1;
		}
		{
	
			vector<int> int_vec; 
			std::vector<int> std_int_vec; 
			vector<int>::iterator it ;
			std::vector<int>::iterator std_it ;
	
			it = int_vec.insert(int_vec.end(), 5);
			int_vec.insert(it, 4);
			it = int_vec.insert(int_vec.begin()+2, 6);
			int_vec.insert(it, 7);
	
			std_it = std_int_vec.insert(std_int_vec.end(), 5);
			std_int_vec.insert(std_it, 4);
			std_it = std_int_vec.insert(std_int_vec.begin()+ 2, 6);
			std_int_vec.insert(std_it, 7);
	
			for (vector<int>::iterator i = int_vec.begin(); i != int_vec.end(); i++)
				std::cout  <<  *i  << " " << std::endl;
	
			std::cout << "-----------" << std::endl;
			for (std::vector<int>::iterator i = std_int_vec.begin(); i != std_int_vec.end(); i++)
				std::cout  <<  *i  << " " << std::endl;
			return 1;
		}
		{
			std::cout << "TEST : vector.insert() (1)(2)(3) " << std::endl;
			int arr[] = {42, 43, 44, 45, 46, 47};
	
			vector<int> int_vec;
			int_vec.insert(int_vec.begin(), 6);
			int_vec.insert(int_vec.begin(), 5);
			int_vec.insert(int_vec.begin(), 4);
	
			int_vec.insert(int_vec.begin() + 1, 10, 1337);
			int_vec.insert(int_vec.begin() + 2,  arr, arr+6);
	
			for (vector<int>::iterator i = int_vec.begin(); i != int_vec.end(); i++)
				std::cout << "v :" << *i  << std::endl;
			std::cout << "size : " << int_vec.size() << " capacity : "
				<< int_vec.capacity() << std::endl;
	
		}
		{
			vector<int> x(10, 42);
			vector<int>::iterator it = x.insert(x.end(), 1337);
			std::cout << *it << std::endl;
			return 1;
	
		}
		{
			vector<int> x(10, 42);
			vector<int> y(10, 42);
			std::cout << (x == y) << std::endl;
			return 1;
			swap(x, y);
			std::cout << "x.size() : " << x.size() << "  " << "y.size() : " << y.size() << std::endl;
	
		}
		{
			vector<int> int_vec(21, 42);
			vector<int>::const_reverse_iterator begin(int_vec.end());
			vector<int>::const_reverse_iterator end(int_vec.begin());
			std::cout << (begin <= end) << std::endl;
		}
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
		}
		{
			std::cout << "TEST : iterator_traits " << std::endl;
			typedef	iterator_traits<const int *> test_trait;	
			std::cout << (typeid(test_trait::pointer) == typeid(const int* )) << std::endl;
		}
		{
	
			std::cout << "TEST : vector.clear() " << std::endl;
			vector<Test> foo(4, 'Z');
			std::cout << "before clear" << std::endl;
			foo.clear();
			std::cout << "After clear" << std::endl;
			std::cout << "foo.zie() : "<<  foo.size() << " foo.capacity() : " << foo.capacity() << std::endl;
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
		}
		{
			std::cout << "TEST : vector.operator[]() " << std::endl;
			vector<Test>  test_vec(1, 'a');
			std::cout << "Before assigning "  << std::endl;
			test_vec[0] = 'z';
			std::cout << "After assigning "  << std::endl;
		}
		{
			std::cout << "TEST : is_integral " << std::endl;
			std::cout << "int : " << is_integral<const int>::value << std::endl;
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
		}
		{
	
			std::cout << "TEST : vector.pop_back() " << std::endl;
			vector<Test> test_vec;
			test_vec.push_back('a');
			test_vec.push_back('x');
			test_vec.pop_back();
			std::cout << test_vec[0] << std::endl;
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
		}
		{
			vector<Test> t(10, 'c');
			t.front() = 'A'; std::cout << "t.front() " << t.front() <<  std::endl; 
			t.at(t.size() - 1) = 'P';
			std::cout << t.back() << std::endl;
			std::cout << "t.at(1) : " << t.at(1) << std::endl;
			std::cout << "t.at(0) : " << t.at(0) << std::endl;
			std::cout << t[0] << std::endl;
			t.reserve(20);
			std::cout << "T capacity : :" <<  t.capacity() << std::endl;
			std::cout << "T size : "  << t.size() << std::endl;
			std::cout << "T capacity : :" <<  t.capacity() << std::endl;
			std::cout << t.max_size() << std::endl;
			for (vector<Test>::const_iterator it  = t.begin(); it != t.end(); it++ )
				std::cout << *it << std::endl;
			t.resize(0, 'x');
			std::cout << std::endl << t.empty() << std::endl;
	
			vector<Test>::iterator it = t.begin();
			vector<Test>::iterator it1;
	
			Test a('x');
			Test a1('9');
			Test a2('L');
			*it = a;
			*(it + 2) = a1; 
	
			it[0] = a2; 
			std::cout << it[0] << std::endl;
			std::cout << (std::addressof(it += 42) == std::addressof(it)) << std::endl;
			it1 = it + 1;
			std::cout <<"(it == it1) " << (it == it1) << std::endl;
			std::cout <<"(it == it1) " << (it == it1) << std::endl;
			std::cout << "(it >= it1) "<< (it >= it1) << std::endl;
			std::cout << "(it <= it1) "<< (it <= it1) << std::endl;
			std::cout << "(it < it1) " << (it < it1) << std::endl;
			std::cout << "(it > it1) " << (it > it1) << std::endl;
			std::cout << (it1 - --it) << std::endl;
			std::cout << "Crafted result : " << *(2 +  (++it - 1) ) << std::endl;
			std::cout << "Crafted result : " << *((1 + it) + 2 ) << std::endl;
	
			it++;
			std::cout << "------------" << std::endl;
			std::cout << "output 1 " << *it++ << std::endl;
			std::cout << "output 2 " << it1->key << std::endl;
			std::cout << "output 3 " << (--it)->key << std::endl;
			std::cout << "output 4 " << *it1 << std::endl;
	
	
			std::allocator<Test> alloc;
			Test* v = alloc.allocate(42);
			Test tl('*');
			alloc.construct(v, tl);
	
			vector<Test> v1(2, '*');
			vector<Test> v2(3, 'a');
			v1 = v2;
	
			std::vector<Test> v3(2, 'R');
			std::vector<Test> v4(2, 'I');
			v3 = v4;
	
			std::cout << "Size v1: " << v1.size() << " Capacity v1: " << v1.capacity() << std::endl;
			std::cout << "Size v2 : " << v2.size() << " Capacity v2 : " << v2.capacity() << std::endl;
	
			std::cout << "Size v1: " << v3.size() << " Capacity v1: " << v3.capacity() << std::endl;
			std::cout << "Size v2 : " << v4.size() << " Capacity v2 : " << v4.capacity() << std::endl;
		}
		return (0);
	
}
#endif
#if STACK 

using namespace NAMESPACE;


int main(void)
{
	vector<int>  larg_vec(10e2, 42);
	stack<int, vector<int> > int_stack;
	int_stack.push(42);
	int_stack.pop();
	
	std::cout << "stack is empty : " << std::boolalpha << int_stack.empty() << std::endl;
	std::cout << "stack size : "  <<  int_stack.size() << std::endl;
	stack<int, vector<int> > larg_stack(larg_vec);
	const stack<int, vector<int> > larg_stack_ccp(larg_vec);
	stack<int, vector<int> > larg_stack_cp;

	std::cout << "larg_stack is empty : " << std::boolalpha << larg_stack.empty() << std::endl;
	std::cout << "larg_stack size : "  <<  larg_stack.size() << std::endl;

	std::cout << "larg_stack_cp is empty : " << std::boolalpha << larg_stack_cp.empty() << std::endl;
	std::cout << "larg_stack_cp size : "  <<  larg_stack_cp.size() << std::endl;
	
	while (!larg_stack.empty())
	{
		larg_stack_cp.push(larg_stack.top());
		larg_stack.pop();
	}

	std::cout << "larg_stack is empty : " << std::boolalpha << larg_stack.empty() << std::endl;
	std::cout << "larg_stack size : "  <<  larg_stack.size() << std::endl;

	std::cout << "larg_stack_cp is empty : " << std::boolalpha << larg_stack_cp.empty() << std::endl;
	std::cout << "larg_stack_cp size : "  <<  larg_stack_cp.size() << std::endl;

	std::cout <<  std::boolalpha  <<  (larg_stack_cp == larg_stack_ccp )<< std::endl;

	return (0);
}

#endif 
