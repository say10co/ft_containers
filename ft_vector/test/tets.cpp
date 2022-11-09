#include <vector>
#include <iostream>
#include <sstream> 
#include "../inc/vector.hpp"
#define TESTED_TYPE int
#define TESTTED_NAMESPACE ft

void foo (const int *n)
{
	(void)n;
}

int main()
{
	int u = 0;
	foo(&u);
	return 0;
	std::vector<int> myvector;

	// set some values (from 1 to 10)
	myvector.reserve(100);
	for (int i=1; i<=10; i++) myvector.push_back(i);

	// erase the 6th element
	//myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	std::vector<int>::iterator ret_it = myvector.erase (myvector.begin(),myvector.end()+10);
	(void) ret_it;
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	return 0;
	/*
	   ft::vector<int> int_vec(0, 42);
	   int_vec.assign(2, 42);
	   return (1);
	   std::istringstream str("1 2 3 4 5 6 7");
	   std::istreambuf_iterator<char> it(str), end;

	   ft::vector<char> _vec(it, end);
	   ft::vector<char>::iterator v_it =  _vec.begin();
	   ft::vector<char>::iterator v_ite =  _vec.end();

	   _vec.assign(v_it, v_ite);
	   for (ft::vector<char>::iterator i = _vec.begin(); i != _vec.end();i++)
	   std::cout << *i;
	   std::cout << std::endl;
	   _vec.assign(it, end);
	   for (ft::vector<char>::iterator i = _vec.begin(); i != _vec.end();i++)
	   std::cout << *i;
	   std::cout << std::endl;
	   */
}

/*
   int		main(void)
   {
   const int size = 5;
   TESTTED_NAMESPACE::vector<TESTED_TYPE> vct(size);

//TESTTED_NAMESPACE::vector<tested_type>::reverse_iterator it = vct.rbegin();
//TESTTED_NAMESPACE::vector<tested_type>::const_reverse_iterator ite = vct.rbegin();

TESTTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
TESTTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator  ite = vct.rbegin();

std::cout << *it <<  " " << *it << std::endl;
return (1);
(void) it;
(void) ite;

for (int i = 0; i < size; ++i)
//it[i] = (size - i) * 5;
std::cout << "v : " << it[i]  << std::endl;


it = it + 5;
it = 1 + it;
it = it - 4;

std::cout << *(it += 2) << std::endl;
std::cout << *(it -= 1) << std::endl;

 *(it -= 2) = 42;
 *(it += 2) = 21;

 std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

 std::cout << "(it == const_it): " << (ite == it) << std::endl;
 std::cout << "(const_ite - it): " << (ite - it) << std::endl;
 std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
 */
//printSize(vct, true);
