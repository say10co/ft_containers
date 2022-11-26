
#include <iostream>
#include "../source/map.hpp"

int main(int ac,  char	**av)
{
	(void) ac;
	(void) av;

	ft::map<int, int> map;
	ft::pair<int, int> pair1(42, 1);
	ft::pair<int, int> pair2(41, 2);
	ft::pair<int, int> pair3(0, 3);
	ft::pair<int, const char *const > arr[] = {
		ft::make_pair(1, "hello"), ft::make_pair(2, "world"), ft::make_pair(3, "banana") 
	};
	map.insert(pair1);
	map.insert(pair2);
	map.insert(pair3);
	map.print();
	ft::map<int, const char *const> range_map(arr, arr+3);
	map.print();
	
	return (0);
}

