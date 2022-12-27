#include "enable_if.hpp"
#include <iostream>

int main()
{
	std::cout << "const char " << ft::is_integral<const char>::value << std::endl;
	std::cout << " char " << ft::is_integral< char>::value << std::endl;
	std::cout << " std::string " << ft::is_integral<std::string>::value << std::endl;
	return (1);
}
