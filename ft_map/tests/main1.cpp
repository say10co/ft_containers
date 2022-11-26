#include <iostream>
#include "../../RBT/RBT.hpp"
#include "../../ft_vector/source/vector.hpp"
#include "../../ft_map/source/map.hpp"

//void printBT(const std::string& prefix, const Node* node, bool isLeft)
//{
//    if( node != nullptr )
//    {
//        std::cout << prefix;
//
//        std::cout << (isLeft ? "├──" : "└──" );
//
//        // print the value of the node
//        std::cout << node->_value << (node->_color ? "(R)" : " (B)") << std::endl;
//
//        // enter the next tree level - left and right branch
//        printBT( prefix + (isLeft ? "│   " : "    "), node->_child[0], true);
//
//        printBT( prefix + (isLeft ? "│   " : "    "), node->_child[1], false);
//    }
//}
//
//void printBT(const Node* node)
//{
//    printBT("", node, false);
//}

//template <typename value_type, typename Alloc>
template <typename value_type>
void check_parent(const Node<value_type> *node)
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
	
	ft::pair<int, int> arr[] = {
		ft::make_pair(1, 42),
		ft::make_pair(2, 43),
		ft::make_pair(3, 44),
		ft::make_pair(4, 45),
		ft::make_pair(5, 46),
		ft::make_pair(6, 47),
		ft::make_pair(7, 48)

	};

	ft::map<int, int>  tree;
	tree.insert(arr[1]);
	tree.insert(arr[2]);
	tree.insert(arr[0]);
	tree.insert(arr[3]);
	tree.insert(arr[6]);
	tree.insert(arr[4]);
	tree.insert(arr[5]);
	tree.print();
	tree.get_root()->delete_(arr[0]);
	tree.insert(ft::make_pair(8, 33));
	ft::map<int, int>::iterator it = tree.begin();
	ft::map<int, int>::iterator end = tree.end();
	while (it != end)
	{
		std::cout << "value.first :" << (*it).first << std::endl;
		++it;
	}
	while (it != tree.begin())
	{	
		std::cout << "value.first :" << (*it).first << std::endl;
		--it;
	}

	tree.print();

	//tree.delete_(arr[2]);
	//tree.print();
	//tree.delete_(arr[1]);
	//tree.print();
	//tree.delete_(arr[4]);
	//tree.print();
	//tree.delete_(arr[3]);
	//tree.print();
	check_parent(tree.get_root()->get_root());
	//tree.delete_(30);
	//printBT(tree.get_root());
	//printBT(tree.get_root());
	
	return (0);
}

