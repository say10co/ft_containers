#include "RBT.hpp"
#include <iostream>

void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->_value << (node->_color ? "(R)" : " (B)") << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->_child[0], true);

        printBT( prefix + (isLeft ? "│   " : "    "), node->_child[1], false);
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);
}

int main(int ac,  char	**av)
{
	(void)ac;
	(void)av;
	
	RBT tree(7);
	tree.Insert(1);
	tree.Insert(0);
	tree.Insert(20);
	//tree.Insert(1);
	//tree.Insert(7);
	//tree.Insert(15);
	tree.Insert(30);
	tree.Insert(31);
	tree.Insert(6);
	tree.Insert(25);
	tree.Insert(40);
	printBT(tree.get_root());
	tree.delete_(31);
	printBT(tree.get_root());
	tree.delete_(25);
	printBT(tree.get_root());
	tree.delete_(30);
	printBT(tree.get_root());
	tree.delete_(40);
	printBT(tree.get_root());
	//tree.delete_(30);
	//printBT(tree.get_root());
	//printBT(tree.get_root());
	
	return (0);
}

