#ifndef RBT_HPP
# define RBT_HPP 

#include <stddef.h>

#define RED 1
#define BLACK 0
#define LEFT 0
#define RIGHT 1

//template<typename value_type, typename Alloc> 
template<typename value_type> 
struct Node
{
	int _color;
	value_type *_p;
	struct Node *_parent;
	struct Node **_child;
	//Alloc _allocator;

	Node() {}
	Node(const value_type &c_pair, Node *parent)
	{
		//this->_p =  _allocator.allocate(sizeof(value_type)) ;
		this->_p = new value_type(c_pair);
		//this->_allocator.construct(this->_p, c_pair);
		this->_color = RED;

		_child = new Node* [2];
		this->_child[LEFT] = NULL;
		this->_child[RIGHT] = NULL;
		this->_parent = parent;
	}
	~Node()
	{
		std::cout << "~Node() dcalled" << std::endl;
		//this->_allocator.deallocate(this->_p, sizeof(value_type));
		delete this->_p;
		delete (_child);
		_child = NULL;
	}

};

//template<typename value_type, typename Alloc> 
template<typename value_type> 
//void printBT(const std::string& prefix, const Node<value_type, Alloc>* node, bool isLeft)
void printBT(const std::string& prefix, const Node<value_type>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << "k: " << node->_p->first << " v: " << node->_p->second << (node->_color ? " (R)" : " (B)") << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->_child[0], true);

        printBT( prefix + (isLeft ? "│   " : "    "), node->_child[1], false);
    }
}

//template<typename value_type, typename Alloc> 
template<typename value_type> 
//void printBT(const Node<value_type, Alloc>* node)
void printBT(const Node<value_type>* node)
{
    printBT("", node, false);
}

template<typename value_type, typename Compare, typename Alloc> 
class RBT
{
	private:
		typedef struct Node<value_type> Node;
		//typedef struct Node<value_type, Alloc> Node;
		Node *_root;
		Compare _comp_obj;

	protected:

		bool isRednode(const Node *node);
		void colorFlip(Node *node);
		Node *getMax(Node *node);
		Node *rotate(Node *node, bool dir);
		Node *doubleRotate(Node *node, bool dir);
		Node *Insert_helper(Node *node, Node *parent, const value_type &value);
		Node *BalanceSubTree(Node *node, bool side);
		Node *BalanceDelete(Node *node, bool dir, bool &isBalanced);
		Node *DeleteHelper(Node *node, value_type data, bool &isBalanced);

	public:
		void deleteRBT(Node *&node);
		void  delete_(value_type data);
		Node *get_root() { return this->_root; }
		void Insert(const value_type &value);
		Node *getMin(); // uses internal pointer

		RBT(): _root(NULL) {}

		RBT(const value_type &node)
		{
			this->_root = new Node(node, NULL);
		}
		~RBT();
};

	template<typename value_type, typename Compare, typename Alloc> 
	Node<value_type> *RBT<value_type, Compare, Alloc>::getMin()
	{	
			Node* tmp_node;

			tmp_node = this->_root;
			while (tmp_node && tmp_node->_child[LEFT])
				tmp_node = tmp_node->_child[LEFT];
			return (tmp_node);
	}
	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::Insert(const value_type &value)
{
	this->_root = Insert_helper(this->_root, NULL, value);
	this->_root->_color = BLACK;
}
	template<typename value_type, typename Compare, typename Alloc> 
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::Insert_helper(Node *node, Node *parent, const value_type &value)
Node<value_type>* RBT<value_type,Compare,Alloc>::Insert_helper(Node *node, Node *parent, const value_type &value)
{
	bool side;

	if (node == NULL)
		return new Node(value, parent);

	side = this->_comp_obj(node->_p->first, value.first);
	node->_child[side] = Insert_helper(node->_child[side], node, value);
	return BalanceSubTree(node, side);
}

	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::deleteRBT(Node *&node)
{
	if (node == NULL)
		return;
	deleteRBT(node->_child[LEFT]);
	deleteRBT(node->_child[RIGHT]);
	delete node;
	node = NULL;
}

	template<typename value_type, typename Compare, typename Alloc> 
RBT<value_type,Compare,Alloc>::~RBT()
{
	deleteRBT(this->_root);
	//std::cout << (this->_root == NULL ? "root is null" : "root is not null") << std::endl;
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
//Node<value_type,Alloc> *RBT<value_type,Compare,Alloc>::rotate(Node *node, bool dir)
Node<value_type> *RBT<value_type,Compare,Alloc>::rotate(Node *node, bool dir)
{
	Node *new_root;
	new_root = node->_child[!dir];

	node->_child[!dir] = new_root->_child[dir];
	if (new_root->_child[dir])
		new_root->_child[dir]->_parent = node;

	new_root->_child[dir] = node;
	// Update the parent
	new_root->_parent = node->_parent;
	node->_parent = new_root;

	new_root->_color = node->_color;
	node->_color = RED;
	return new_root;

}

	template<typename value_type, typename Compare, typename Alloc> 
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::doubleRotate(Node *node, bool dir)
Node<value_type>* RBT<value_type,Compare,Alloc>::doubleRotate(Node *node, bool dir)
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
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::BalanceSubTree(Node *node, bool side)
Node<value_type>* RBT<value_type,Compare,Alloc>::BalanceSubTree(Node *node, bool side)
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
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::getMax(Node *node)
Node<value_type>* RBT<value_type,Compare,Alloc>::getMax(Node *node)
{
	if (!(node->_child[RIGHT]))
		return (node);
	return (getMax(node->_child[RIGHT]));
}


	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::delete_(value_type data)
{
	bool isBalanced = false;
	this->_root = DeleteHelper(this->_root, data, isBalanced);
	if(this->_root != NULL)
		this->_root->_color = BLACK;
}

	template<typename value_type, typename Compare, typename Alloc> 
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::DeleteHelper(Node *node, value_type data, bool &isBalanced)
Node<value_type>* RBT<value_type,Compare,Alloc>::DeleteHelper(Node *node, value_type data, bool &isBalanced)
{
	Node *child;
	bool dir;

	if (!node)
	{
		isBalanced = true;
		return node;
	}
	if (node->_p->first == data.first)
	{
		// Has at most one child
		if (!node->_child[LEFT] || !node->_child[RIGHT])
		{	
			child  = NULL;
			if (node->_child[RIGHT])
				child = node->_child[RIGHT];
			else if (node->_child[LEFT])
				child = node->_child[LEFT];
			
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
			node->_p->first = max->_p->first;
			data = *(max->_p); // delete max node by updating the value ; recurse on max_node
		}

	}

	dir = this->_comp_obj(node->_p->first, data.first); //(value > node->_key);//  left 0; right 1
	//dir = (value > node->_key);//  left 0; right 1
	node->_child[dir] = DeleteHelper(node->_child[dir], data, isBalanced);

	if (isBalanced)
		return (node);
	return (BalanceDelete(node, dir, isBalanced));
}

	template<typename value_type, typename Compare, typename Alloc> 
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::BalanceDelete(Node *node, bool dir, bool &isBalanced)
Node<value_type>* RBT<value_type,Compare,Alloc>::BalanceDelete(Node *node, bool dir, bool &isBalanced)
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
		node = rotate(node, dir);
		siblling = parent->_child[!dir];
		redsibllingRotation =  true;
	}
	if (!siblling)
		return node;

	if (!isRednode(siblling->_child[LEFT]) && !isRednode(siblling->_child[RIGHT]))
	{
		if (isRednode(parent)) 
			isBalanced = true; 
		parent->_color = BLACK;
		siblling->_color = RED;
	}
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
		{
			node->_child[dir] = parent; // with original color
			parent->_parent = node;
		}	
		else
			node = parent;
		isBalanced = true;
	}
	return node;
}

#endif /* RBT_HPP */
