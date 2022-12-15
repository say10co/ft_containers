#ifndef RBT_HPP
# define RBT_HPP 

#include <stddef.h>

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

		Node() : _p(NULL), _parent(NULL)
		{
				_child = new Node* [2];
				this->_child[LEFT] = NULL;
				this->_child[RIGHT] = NULL;
		}
		Node(const value_type &c_pair, Node *parent)
		{
				//this->_p =  _allocator.allocate(sizeof(value_type)) ;
				//this->_allocator.construct(this->_p, c_pair);
				this->_p = new value_type(c_pair);
				this->_color = 1;

				_child = new Node* [2];
				this->_child[LEFT] = NULL;
				this->_child[RIGHT] = NULL;
				this->_parent = parent;
		}
		~Node()
		{
				//this->_allocator.deallocate(this->_p, sizeof(value_type));
				delete (_child);
				delete (_p);
				_child = NULL;
		}
};

		template<typename value_type> 
bool operator==(const Node<value_type> &lhs, const Node<value_type> &rhs)
{
		if (lhs._p == NULL && rhs._p == lhs._p)
				return (true);
		if (lhs._p && rhs._p)
				return (lhs._p->first == rhs._p->first);
		return false;
}

template<typename value_type, typename Compare, typename Alloc> 
class RBT
{
		private:
				typedef struct Node<value_type> Node;
				typedef size_t size_type;
				Node _root;
				Compare _comp_obj;
				size_type _size;

		protected:
				bool isRednode(const Node *node);
				void colorFlip(Node *node);
				Node *getMax(Node *node);
				Node *rotate(Node *node, bool dir);
				Node *doubleRotate(Node *node, bool dir);
				Node *Insert_helper(Node *node, Node **in_node);
				Node *BalanceSubTree(Node *node, bool side);
				Node *BalanceDelete(Node *node, bool dir, bool &isBalanced);
				Node *DeleteHelper(Node *node, value_type *data, bool &isBalanced);

		public:
				const Node *get_root() const { return &this->_root; }
				const Node *getMin() const;
				void  delete_(value_type data);
				void deleteRBT(Node *&node);
				void delete_all(Node *&node);

				Node *find_node(const typename value_type::first_type &key) const;
				Node *get_bound(const typename  value_type::first_type &key, bool bound) const;

				Node *get_root() { return &this->_root; }
				size_type GetTreesize() { return this->_size; }
				Node *Insert(const value_type &value);

				RBT():_size(0) {}
				RBT(const RBT &rbt);
				RBT &operator=(const RBT &rbt);
				~RBT();

				Node *begin() const;
				Node *end();
				const Node *end() const;
				
};

//		template<typename value_type, typename Compare, typename Alloc> 
//			typename RBT<value_type, Compare, Alloc>::Node *RBT<value_type, Compare, Alloc>::begin() const
//			{
//					//return (this->getMin());
//					return (NULL);
//			}
//
		template<typename value_type, typename Compare, typename Alloc>
RBT<value_type, Compare, Alloc>::RBT(const RBT &rbt)
		:_size(rbt._size)
{
		this->_root =  rbt._root; 
		this->_comp_obj = rbt._comp_obj;
}

		template<typename value_type, typename Compare, typename Alloc>
RBT<value_type, Compare, Alloc> & RBT<value_type, Compare, Alloc>::operator=(const RBT &rbt)
{
		this->_root =  rbt._root; 
		this->_comp_obj = rbt._comp_obj;
		this->_size = rbt._size;
		return (*this);
}

		template<typename value_type, typename Compare, typename Alloc> 
typename RBT<value_type, Compare, Alloc>::Node *RBT<value_type, Compare, Alloc>::end()
{
		return (&this->_root);
}

		template<typename value_type, typename Compare, typename Alloc> 
const typename RBT<value_type, Compare, Alloc>::Node *RBT<value_type, Compare, Alloc>::end() const
{
		return (&this->_root);
}

		template<typename value_type, typename Compare, typename Alloc> 
const Node<value_type> *RBT<value_type, Compare, Alloc>::getMin() const
{	
		const Node* tmp_node;

		tmp_node = &this->_root;
		while (tmp_node && tmp_node->_child[LEFT])
				tmp_node = tmp_node->_child[LEFT];
		return (tmp_node);
}
		template<typename value_type, typename Compare, typename Alloc> 
Node<value_type> *RBT<value_type,Compare,Alloc>::Insert(const value_type &value)
{
		Node *inserted_node = new Node(value, &this->_root);

		this->_root._child[LEFT] = Insert_helper(this->_root._child[LEFT], &inserted_node);
		this->_root._child[RIGHT] = this->_root._child[LEFT]; // dumy root children are the same
		this->_root._child[LEFT]->_color = 0;

		return inserted_node;
}
	template<typename value_type, typename Compare, typename Alloc> 
Node<value_type>* RBT<value_type,Compare, Alloc>::Insert_helper(Node *node, Node **in_node) // smashes stack 
{
		bool side;
		value_type &value = *(*in_node)->_p;
		Node *new_node;

		if (node == NULL)
		{
				new_node = *in_node;
				this->_size++;
				return new_node;
		}
		if (!this->_comp_obj(node->_p->first, value.first) && !this->_comp_obj(value.first, node->_p->first))
		{
				delete *in_node; // No insertion performed
				*in_node = node;
				return (node);
		}
		side = this->_comp_obj(node->_p->first, value.first);
		(*in_node)->_parent = node;
		node->_child[side] = Insert_helper(node->_child[side], in_node); 

		return BalanceSubTree(node, side);

}

	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::deleteRBT(Node *&node)
{
		this->_size = 0;
		delete_all(node);
}

	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::delete_all(Node *&node)
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
		this->_size = 0;
		deleteRBT(this->_root._child[LEFT]);
}

		template<typename value_type, typename Compare, typename Alloc> 
bool RBT<value_type,Compare,Alloc>::isRednode(const Node *node)
{
		if (node == NULL)
				return false;
		return (node->_color == 1);
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
		node->_color = 1;
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

		this->_root._child[LEFT] = DeleteHelper(this->_root._child[LEFT], &data, isBalanced);
		this->_root._child[RIGHT] = this->_root._child[LEFT];

		if(this->_root._child[LEFT] != NULL)
				this->_root._child[LEFT]->_color = 0;

}

	 	template<typename value_type, typename Compare, typename Alloc> 
typename RBT<value_type,Compare,Alloc>::Node *RBT<value_type,Compare,Alloc>::find_node(const typename  value_type::first_type &key) const
{
		bool side;
		Node *node = this->_root._child[RIGHT];

		while (node)
		{
				if (!this->_comp_obj(node->_p->first, key) && !this->_comp_obj(key, node->_p->first))
						return (node);
				side = this->_comp_obj(node->_p->first, key);
				node = node->_child[side];
		}
		return (NULL);
}

	template<typename value_type, typename Compare, typename Alloc> 
typename RBT<value_type,Compare,Alloc>::Node *RBT<value_type,Compare,Alloc>::get_bound(const typename  value_type::first_type &key, bool bound) const
{
		bool side;
		bool upper(1);
		bool cond;
		Node *node = this->_root._child[RIGHT];

		while (node)
		{
				cond = this->_comp_obj(key, node->_p->first);
				if (bound == upper && cond) //this->_comp_obj(key, node->_p->first))
						return (node);
				else if (bound == 0 && !cond) //!this->_comp_obj(node->_p->first, key))
						return (node);

				side = !bound;
				node = node->_child[side];
		}
		return (NULL);
}


		template<typename value_type, typename Compare, typename Alloc> 
//Node<value_type,Alloc>* RBT<value_type,Compare,Alloc>::DeleteHelper(Node *node, value_type data, bool &isBalanced)
Node<value_type>* RBT<value_type,Compare,Alloc>::DeleteHelper(Node *node, value_type *data, bool &isBalanced)
{
		Node *child;
		bool dir;

		if (!node)
		{
				isBalanced = true;
				return node;
		}
		if (node->_p->first == data->first)
		{
				// Has at most one child
				if (!node->_child[LEFT] || !node->_child[RIGHT])
				{	
						this->_size--;
						child  = NULL;
						if (node->_child[RIGHT])
								child = node->_child[RIGHT];
						else if (node->_child[LEFT])
								child = node->_child[LEFT];

						if (child != NULL)
								child->_parent = node->_parent;

						if (isRednode(node))
						{
								isBalanced= true;
								delete(node);
								return child;
						}
						if (isRednode(child))
						{
								child->_color = node->_color;  // preseving node color after replace (Keeping 0)
								isBalanced = true;
								delete (node);
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
						node->_p = new value_type(*(max->_p));
						//node->_p->first = max->_p->first;
						data = (max->_p); // delete max node by updating the value ; recurse on max_node
				}
		}

		dir = this->_comp_obj(node->_p->first, data->first); 
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
				parent->_color = 0;
				siblling->_color = 1;
		}
		else
		{
				parentColor = parent->_color;
				if (isRednode(siblling->_child[!dir]))
						parent = rotate(parent, dir);
				else
						parent = doubleRotate(parent, dir);

				parent->_child[dir]->_color = 0;
				parent->_child[!dir]->_color= 0;
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

/*
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
*/

#endif /* RBT_HPP */
