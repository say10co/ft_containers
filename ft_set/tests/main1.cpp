#include <iostream>
#include "../RBT.hpp"
#include "../source/set.hpp"
#include "../../utils/pair.hpp"
#include <unistd.h>
#include <map>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

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

int main()
{
	ft::set<int> set;
	set.insert(10);
}
