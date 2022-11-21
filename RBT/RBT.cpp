#include "RBT.hpp"
#include <iostream>

template<typename value_type, typename Compare, typename Alloc> 
void RBT::Insert(value_type value)
{
	this->_root = Insert_helper(this->_root, value);
	this->_root->_color = BLACK;
}

template<typename value_type, typename Compare, typename Alloc> 
RBT::~RBT()
{
}

template<typename value_type, typename Compare, typename Alloc> 
bool RBT::isRednode(const Node *node)
{
	if (node == NULL)
		return false;
	return (node->_color == RED);
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT::rotate(Node *node, bool dir)
{
	Node *new_root;
	new_root = node->_child[!dir];
	node->_child[!dir] = new_root->_child[dir];
	new_root->_child[dir] = node;

	new_root->_color = node->_color;
	node->_color = RED;
	return new_root;
}

template<typename value_type, typename Compare, typename Alloc> 
Node  *RBT::doubleRotate(Node *node, bool dir)
{
	// inverse rotation for midle node
	node->_child[!dir] = rotate(node->_child[!dir], !dir);
	// dir rotaion for node
	return (rotate(node, dir));
}

template<typename value_type, typename Compare, typename Alloc> 
void RBT::colorFlip(Node *node)
{
	node->_color = !(node->_color);
	node->_child[LEFT]->_color = !(node->_child[LEFT]->_color);
	node->_child[RIGHT]->_color  = !(node->_child[RIGHT]->_color);
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT::Insert_helper(Node *node, int value)
{
	bool side;
	bool side1;

	if (node == NULL)
		return new Node(value);

	side = this->_comp_obj(node->_value, value);
	side = value > node->_value ? 1 : 0;
	assert(side1 == side);

	node->_child[side] = Insert_helper(node->_child[side], value);
	return BalanceSubTree(node, side);
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT::BalanceSubTree(Node *node, bool side)
{
	Node *child = node->_child[side];
	Node *op_child = node->_child[!side];

	if (isRednode(child))
	{
		if (isRednode(op_child))
		{
			if (isRednode(child->_child[side]) || isRednode(child->_child[!side]))
				colorFlip(node);
		}
		else
		{
			if (isRednode(child->_child[side]))
				node = rotate(node, !side); // LEFT 0 RIGHT 1; side LEFT rotation RIGHT 
			else if (isRednode(child->_child[!side]))
				node = doubleRotate(node, !side); // returns new root node for subtree
		}
	}
	return node;
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT::getMax(Node *node)
{
	if (!(node->_child[RIGHT]))
		return (node);
	return (getMax(node->_child[RIGHT]));
}


template<typename value_type, typename Compare, typename Alloc> 
void RBT::delete_(int data)
{
	bool isBalanced = false;
	this->root = DeleteHelper(root, data, isBalanced);
	if(root != NULL)
		root->_color = BLACK;
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT::DeleteHelper(Node *node, int value, bool &isBalanced)
{
	Node *child;
	bool dir;


	if (!node)
	{
		isBalanced = true;
		return node;
	}
	if (node->_value == value)
	{
		// Has at most one child
		if (!node->_child[LEFT] || !node->_child[RIGHT])
		{	
			child  = NULL;
			if (node->_child[RIGHT])
				child = node->_child[RIGHT];
			else if (node->_child[LEFT])
				child = node->_child[LEFT];

			if (isRednode(node))
			{
				delete(node);
				isBalanced= true;
				return child;
			}
			if (isRednode(child))
			{
				child->_color = node->_color;  // preseving node color after replace (Keeping BLACK)
				delete (node);
				isBalanced = true;
				return child;
			}
			else // node is black and has no children 
			{
				//std::cout << "deleted  : " << node->_value << std::endl;
				delete(node);
				return NULL; // node is replaced with NULL (deleted)
			}
		}
		// node has tow children 
		else
		{
			// replace node whith max key in left sub tree
			Node *max = getMax(node->_child[LEFT]);
			node->_value = max->_value;
			value = max->_value; // delete max node by updating the value ; recurse on max_node
		}

	}

	dir = this->_comp_obj(node->_value, value); //(value > node->_value);//  left 0; right 1
	//dir = (value > node->_value);//  left 0; right 1
	node->_child[dir] = DeleteHelper(node->_child[dir], value, isBalanced);

	if (isBalanced)
		return (node);
	return (BalanceDelete(node, dir, isBalanced));
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT::BalanceDelete(Node *node, bool dir, bool &isBalanced)
{
	Node *parent;
	Node *siblling;
	bool redsibllingRotation;
	bool parentColor;

	parent = node;
	siblling = node->_child[!dir];
	redsibllingRotation = false;
	if (isRednode(siblling))
	{
		// make it black siblling case
		// make sure to update nod's child[dir] after later rotation
		node = rotate(node, dir);
		siblling = parent->_child[!dir]; // now siblling is black
		redsibllingRotation =  true;
	}
	if (!siblling)
		return node;

	// case sibbling has tow balck children;
	if (!isRednode(siblling->_child[LEFT]) && !isRednode(siblling->_child[RIGHT]))
	{
		// make it black and it's balanced
		if (isRednode(node)) 
			isBalanced = true; 

		//Else we get double black at node ; so  recurse to solve it;
		// double black is then solved at root level
		node->_color = BLACK;
		siblling->_color = RED;
	}
	// sibbling has near red child or far left red child 
	else
	{
		parentColor = parent->_color;
		if (isRednode(siblling->_child[!dir]))
			parent = rotate(parent, dir);
		else
			parent = doubleRotate(parent, dir);

		parent->_child[dir]->_color = BLACK;
		parent->_child[!dir]->_color= BLACK;
		parent->_color = parentColor;

		if (redsibllingRotation)
			node->_child[dir] = parent; // with original color
		else
			node = parent;
		isBalanced = true;
	}
	return node;
}
