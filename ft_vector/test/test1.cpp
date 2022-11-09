#include <stdio.h>
#include <unistd.h>
#include <vector>
#include  <iostream>
#include "inc/vector.hpp"


int main(int ac,  char	**av)
{
	const int _ratio = 1;
	ft::vector<int> vector;
	std::vector<int> std_vector;

	//vector.reserve(500 * 100);
	//std::cout << vector.size() << std::endl;
	//std::cout << vector.capacity() << std::endl;

	for (int i = 0 ; i < 10 ; i++)
	{
		vector.push_back(i);
		std_vector.push_back(i);
	}
	vector.erase(vector.begin(), vector.begin()+3);
	std::cout << "my_vector content : ";
	for (ft::vector<int>::iterator it  = vector.begin(); it != vector.end();  it++)
		std::cout << *it <<  " ";
	std::cout << "my_vector size :" << vector.size();
	std::cout << "my_vector cap :" << vector.capacity();

	std_vector.erase(std_vector.begin(), std_vector.begin()+3);
	std::cout <<  std::endl << "std_vector content : ";
	for (std::vector<int>::iterator it  = std_vector.begin(); it != std_vector.end();  it++)
		std::cout << *it <<  " ";
	std::cout << "std_vector size :" << std_vector.size();
	std::cout << "std_vector cap :" << std_vector.capacity();

	return (0);
}

