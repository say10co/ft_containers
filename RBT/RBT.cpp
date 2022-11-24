#include "RBT.hpp"
#include <iostream>

template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::Insert(value_type value)
{
	this->_root = Insert_helper(this->_root, NULL, value);
	this->_root->_color = BLACK;
}

template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::deleteRBT(RBT *& root)
{
	if (root == NULL)
		return;
	deleteRBT(root->_child[LEFT]);
	deleteRBT(root->_child[RBT]);
	delete root;
	root = NULL;
}

template<typename value_type, typename Compare, typename Alloc> 
RBT<value_type,Compare,Alloc>::~RBT()
{
	deleteRBT(this->_root);
	std::cout << (this->_root == NULL ? "root is null" : "root is not null") << std::endl;
	std::cout << "~RBT() called" << std::endl;
}

template<typename value_type, typename Compare, typename Alloc> 
bool RBT<value_type,Compare,Alloc>::isRednode(const Node *node)
{
	if (node == NULL)
		return false;
	return (node->_color == RED);
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT<value_type,Compare,Alloc>::rotate(Node *node, bool dir)
{
	Node *new_root;
	new_root = node->_child[!dir];

	node->_child[!dir] = new_root->_child[dir];
	if (new_root->_child[dir])
		new_root->_child[dir]->_parent = node;

	new_root->_child[dir] = node;
	new_root->_parent = node->_parent;
	node->_parent = new_root;

	new_root->_color = node->_color;
	node->_color = RED;
	return new_root;
}

template<typename value_type, typename Compare, typename Alloc> 
Node  *RBT<value_type,Compare,Alloc>::doubleRotate(Node *node, bool dir)
{
	// inverse rotation for midle node
	node->_child[!dir] = rotate(node->_child[!dir], !dir);
	// dir rotaion for node
	return (rotate(node, dir));
}

template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::colorFlip(Node *node)
{
	node->_color = !(node->_color);
	node->_child[LEFT]->_color = !(node->_child[LEFT]->_color);
	node->_child[RIGHT]->_color  = !(node->_child[RIGHT]->_color);
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT<value_type,Compare,Alloc>::Insert_helper(Node *node, Node *parent, int key)
{
	bool side;

	if (node == NULL)
		return new Node(value, parent);

	side = this->_comp_obj(node->_p->first, key);

	node->_child[side] = Insert_helper(node->_child[side], node, value);
	return BalanceSubTree(node, side);
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT<value_type,Compare,Alloc>::BalanceSubTree(Node *node, bool side)
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
Node *RBT<value_type,Compare,Alloc>::getMax(Node *node)
{
	if (! node || !(node->_child[RIGHT]))
		return (node);
	return (getMax(node->_child[RIGHT]));
}


template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::delete_(int data)
{
	bool isBalanced = false;
	this->root = DeleteHelper(root, data, isBalanced);
	if(root != NULL)
		root->_color = BLACK;
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT<value_type,Compare,Alloc>::DeleteHelper(Node *node, int key, bool &isBalanced)
{
	Node *child;
	bool dir;

	if (!node)
	{
		isBalanced = true;
		return node;
	}
	if (node->_key == key)
	{
		// Has at most one child
		if (!node->_child[LEFT] || !node->_child[RIGHT])
		{	
			child  = NULL;
			if (node->_child[RIGHT])
				child = node->_child[RIGHT];
			else if (node->_child[LEFT])
				child = node->_child[LEFT];
			// updating parent of child with parent of node
			if (child != NULL)
				child->_parent = node->_parent;

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
				//std::cout << "deleted  : " << node->_key << std::endl;
				delete(node);
				return NULL; // node is replaced with NULL (deleted)
			}
		}
		// node has tow children 
		else
		{
			// replace node whith max key in left sub tree
			Node *max = getMax(node->_child[LEFT]);
			node->_key = max->_key;
			value = max->_key; // delete max node by updating the value ; recurse on max_node
		}

	}

	dir = this->_comp_obj(node->p->first, key); //(value > node->_key);//  left 0; right 1
	//dir = (value > node->_key);//  left 0; right 1
	node->_child[dir] = DeleteHelper(node->_child[dir], value, isBalanced);

	if (isBalanced)
		return (node);
	return (BalanceDelete(node, dir, isBalanced));
}

template<typename value_type, typename Compare, typename Alloc> 
Node *RBT<value_type,Compare,Alloc>::BalanceDelete(Node *node, bool dir, bool &isBalanced)
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
		isBalanced = true;
		parentColor = parent->_color;
		
		if (isRednode(siblling->_child[!dir]))
			parent = rotate(parent, dir);
		else
			parent = doubleRotate(parent, dir);

		parent->_child[dir]->_color = BLACK;
		parent->_child[!dir]->_color= BLACK;
		parent->_color = parentColor;

		if (!redsibllingRotation) // parent == node
			return parent;

		node->_child[dir] = parent; // with original color
		parent->_parent = node;
	}
	return node;
}
