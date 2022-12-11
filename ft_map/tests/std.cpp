#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <map>



int main(int ac,  char	**av)
{
	(void)ac;
	(void)av;
	std::map<int, std::string> my_map;

	for (int i = 0; i < 10e2; i++)
		my_map[i] = "hello";
	return (0);
}

