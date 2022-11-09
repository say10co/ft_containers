#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "inc/vector.hpp"
bool pred(int a , int b)
{
	return (a < b );
}
bool mycomp (char c1, char c2)
{
	return std::tolower(c1)<std::tolower(c2);
}


int main(int ac,  char	**av)
{
		char foo[]="Apple";
		char bar[]="apartment";

		std::cout << std::boolalpha;

		std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

		std::cout << "Using default comparison (operator<): ";
		std::cout << NAME_SPACE::lexicographical_compare(foo,foo+5,bar,bar+9);
		std::cout << '\n';

		std::cout << "Using mycomp as comparison object: ";
		std::cout << NAME_SPACE::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
		std::cout << '\n';

		return 0;	
}

