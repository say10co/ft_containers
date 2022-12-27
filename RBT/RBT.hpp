#ifndef RBT_HPP 
#define RBT_HPP 

#include <stddef.h>
#include <iostream>
#include "NodeClass.hpp"

template<typename value_type, typename Compare, typename Alloc> 
class RBT
{
		protected:

			typedef size_t												size_type;
			typedef struct	 Node<value_type, Alloc>					_NodeType;
			typedef typename Alloc::template rebind<_NodeType>::other	_Node_alloc;
	
		private:

			_NodeType	*copy(const _NodeType *root_node, _NodeType *parent );
			_NodeType	*rotate(_NodeType *node, bool dir);
			_NodeType 	*doubleRotate(_NodeType *node, bool dir);
			_NodeType 	*Insert_helper(_NodeType *node, _NodeType **in_node);
			_NodeType 	*BalanceSubTree(_NodeType *node, bool side);
			_NodeType 	*BalanceDelete(_NodeType *node, bool dir, bool &isBalanced);
			_NodeType 	*DeleteHelper(_NodeType *node, value_type *data, bool &isBalanced);

			void 		colorFlip(_NodeType *node);
			void		delete_all(_NodeType *node);
			bool 		isRednode(const _NodeType *node);


		protected:

			_NodeType		_root;
			Compare			_comp_obj;
			size_type 		_size;
			_Node_alloc 	_node_allocator;
	
			virtual bool	compare_key(const value_type &lhs, const value_type &rhs) const = 0;
	
			template<typename key_type>
				_NodeType *upper_bound(const key_type  &key);
	
			template<typename key_type>
				_NodeType *lower_bound(const key_type  &key);
	
			template<typename key_type>
				const _NodeType *upper_bound(const key_type  &key) const;
	
			template<typename key_type>
				const _NodeType *lower_bound(const key_type  &key) const;
	
		public:

			const	_NodeType	*begin() const;
			const 	_NodeType 	*end() const;
			_NodeType 			*begin();
			_NodeType 			*end();
			_NodeType 			*Insert(const value_type &value);
			void 				deleteRBT();
			void 				delete_(value_type data);
			void				copy_tree(const RBT &tree);
			size_type			GetTreesize();

			RBT();
			RBT(const RBT &rbt);
			RBT &operator=(const RBT &rbt);
			virtual ~RBT();

};

//Constructors 

	template<typename value_type, typename Compare, typename Alloc>
RBT<value_type, Compare, Alloc>::RBT()
	:_root(), _comp_obj(), _size(0)
{
}

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
RBT<value_type,Compare,Alloc>::~RBT()
{
	if (this->_size != 0)
	{
		this->_size = 0;
		deleteRBT();
	}
}
	
// ==	==	==	==	==	==	 Public Members ==	==	==	==	==	==	

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
typename RBT<value_type, Compare, Alloc>::_NodeType *RBT<value_type, Compare, Alloc>::end()
{
		return (&this->_root);
}

template<typename value_type, typename Compare, typename Alloc> 
const typename RBT<value_type, Compare, Alloc>::_NodeType *RBT<value_type, Compare, Alloc>::end() const
{
		return (&this->_root);
}

template<typename value_type, typename Compare, typename Alloc> 
const typename RBT<value_type, Compare, Alloc>::_NodeType *RBT<value_type, Compare, Alloc>::begin() const
{
		if (!this->_size)
				return &this->_root;
		return (getMin(&this->_root));
}

		template<typename value_type, typename Compare, typename Alloc> 
typename RBT<value_type, Compare, Alloc>::_NodeType *RBT<value_type, Compare, Alloc>::begin()
{
		if (!this->_size)
				return &this->_root;
		return (getMin(&this->_root));
}

	template<typename value_type, typename Compare, typename Alloc>
typename RBT<value_type, Compare, Alloc>::size_type	RBT<value_type, Compare, Alloc>::GetTreesize()
{
	return this->_size;
}

	template<typename value_type, typename Compare, typename Alloc>
void RBT<value_type, Compare, Alloc>::copy_tree(const RBT &tree)
{
	_NodeType *root_node = tree._root._child[LEFT];

	this->_size = tree._size;
	this->_root._child[LEFT] = copy(root_node, &this->_root);
	this->_root._child[RIGHT] = this->_root._child[LEFT];
}	

	template<typename value_type, typename Compare, typename Alloc> 
Node<value_type, Alloc> *RBT<value_type,Compare,Alloc>::Insert(const value_type &value)
{
		_NodeType *inserted_node = this->_node_allocator.allocate(1);

		this->_node_allocator.construct(inserted_node, _NodeType(value, &this->_root));
		this->_root._child[LEFT] = Insert_helper(this->_root._child[LEFT], &inserted_node);
		this->_root._child[RIGHT] = this->_root._child[LEFT]; // dumy root children are the same
		this->_root._child[LEFT]->_color = 0;

		return inserted_node;
}

	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::deleteRBT()
{
		this->_size = 0;
		
		delete_all(this->_root._child[LEFT]);
		this->_root._child[LEFT] = NULL;
		this->_root._child[RIGHT] = NULL;
}

// ==	==	==	==	==	==	 Private Members ==	==	==	==	==	==	

	template<typename value_type, typename Compare, typename Alloc> 
Node<value_type, Alloc>* RBT<value_type,Compare,Alloc>::BalanceSubTree(_NodeType *node, bool side)
{
	_NodeType *child = node->_child[side];
	_NodeType *op_child = node->_child[!side];

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
Node<value_type, Alloc> *RBT<value_type,Compare,Alloc>::rotate(_NodeType *node, bool dir)
{
		_NodeType *new_root;
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
Node<value_type, Alloc>* RBT<value_type,Compare,Alloc>::doubleRotate(_NodeType *node, bool dir)
{
		// inverse rotation for midle node
		node->_child[!dir] = rotate(node->_child[!dir], !dir);
		// dir rotaion for node
		return (rotate(node, dir));
}

	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::colorFlip(_NodeType *node)
{
		node->_color = !(node->_color);
		node->_child[LEFT]->_color = !(node->_child[LEFT]->_color);
		node->_child[RIGHT]->_color  = !(node->_child[RIGHT]->_color);
}

	template<typename value_type, typename Compare, typename Alloc> 
bool RBT<value_type,Compare,Alloc>::isRednode(const _NodeType *node)
{
		if (node == NULL)
				return false;
		return (node->_color == 1);
}
	template<typename value_type, typename Compare, typename Alloc>
typename RBT<value_type, Compare, Alloc>::_NodeType *RBT<value_type, Compare, Alloc>::copy(const _NodeType *root_node, _NodeType *parent )
{
	_NodeType *new_node;

	if (!root_node)
		return NULL;
	new_node = this->_node_allocator.allocate(1);
	this->_node_allocator.construct(new_node, _NodeType(*(root_node->_p), parent));

	new_node->_color = root_node->_color;
	new_node->_child[RIGHT] = copy(root_node->_child[RIGHT], new_node);
	new_node->_child[LEFT] = copy(root_node->_child[LEFT], new_node);
	return (new_node);
}

template<typename value_type, typename Compare, typename Alloc> 
Node<value_type,Alloc>* RBT<value_type,Compare, Alloc>::Insert_helper(_NodeType *node, _NodeType **in_node) // smashes stack 
{
		bool side;
		value_type &value = *(*in_node)->_p;
		_NodeType *new_node;

		if (node == NULL)
		{
				new_node = *in_node;
				this->_size++;
				return new_node;
		}
		if (!this->compare_key(*(node->_p), value) && !this->compare_key(value, *(node->_p)))
		{
				this->_node_allocator.destroy(*in_node);
				this->_node_allocator.deallocate(*in_node, 1);
				*in_node = node;
				return (node);
		}
		side = this->compare_key(*(node->_p), value);
		(*in_node)->_parent = node;
		node->_child[side] = Insert_helper(node->_child[side], in_node); 

		return BalanceSubTree(node, side);
}

	template<typename value_type, typename Compare, typename Alloc> 
void RBT<value_type,Compare,Alloc>::delete_all(_NodeType *node)
{
		if (node == NULL)
				return;
		delete_all(node->_child[LEFT]);
		delete_all(node->_child[RIGHT]);
		this->_node_allocator.destroy(node);
		this->_node_allocator.deallocate(node, 1);
}

template<typename value_type, typename Compare, typename Alloc> 
Node<value_type, Alloc>* RBT<value_type,Compare,Alloc>::DeleteHelper(_NodeType *node, value_type *data, bool &isBalanced)
{
	_NodeType *child;
	bool dir;

	if (!node)
	{
		isBalanced = true;
		return node;
	}
	if (!this->compare_key(*(node->_p), *data) && !this->compare_key(*data, *(node->_p)))
	{
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
					this->_node_allocator.destroy(node);
					this->_node_allocator.deallocate(node, 1);
					return child;
			}
			if (isRednode(child))
			{
				child->_color = node->_color;  // preseving node color after replace (Keeping 0)
				isBalanced = true;
				this->_node_allocator.destroy(node);
				this->_node_allocator.deallocate(node, 1);
				return child;
			}
			else // node is black and has no children 
			{
				this->_node_allocator.destroy(node);
				this->_node_allocator.deallocate(node, 1);
				return NULL; // node is replaced with NULL (deleted)
			}
		}
		// node has tow children 
		else
		{
			// replace node whith max key in left sub tree
			_NodeType *max = getMax(node->_child[LEFT]);
			node->_allocator.destroy(node->_p);
			node->_allocator.deallocate(node->_p, 1);

			node->_p = node->_allocator.allocate(1);
			node->_allocator.construct(node->_p, *(max->_p));
			data = (max->_p); // delete max node by updating the value ; recurse on max_node
		}
	}
	dir = this->compare_key(*(node->_p), *(data)); 
	node->_child[dir] = DeleteHelper(node->_child[dir], data, isBalanced);
	if (isBalanced)
			return (node);
	return (BalanceDelete(node, dir, isBalanced));
}

template<typename value_type, typename Compare, typename Alloc> 
Node<value_type, Alloc>* RBT<value_type,Compare,Alloc>::BalanceDelete(_NodeType *node, bool dir, bool &isBalanced)
{
		_NodeType *parent;
		_NodeType *siblling;
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


// ==	==	==	==	==	==	 Protected Members ==	==	==	==	==	==	

	template<typename value_type, typename Compare, typename Alloc>
		template<typename key_type>
const Node<value_type, Alloc> *RBT<value_type, Compare, Alloc>::lower_bound(const key_type  &key) const
{
	_NodeType * curr = this->_root._child[LEFT];
	const _NodeType *lower_bound = &(this->_root);

	while (curr)
	{
		if (!this->compare_key(*(curr->_p), key) && !this->compare_key(key, *(curr->_p)))
		{
			lower_bound = curr;
			break ;
		}
		if (this->compare_key(key, *(curr->_p)) == true) 
		{
			lower_bound = curr;
			curr = curr->_child[LEFT];
		}
		else
			curr = curr->_child[RIGHT];
	}
	return (lower_bound);
}

	template<typename value_type, typename Compare, typename Alloc>
		template<typename key_type>
const Node<value_type, Alloc> *RBT<value_type, Compare, Alloc>::upper_bound(const key_type  &key) const
{
	_NodeType * curr = this->_root._child[LEFT];
	const _NodeType *upper_bound = &(this->_root);

	while (curr)
	{
		if (this->compare_key(key, *(curr->_p)) == true)
		{
			upper_bound = curr;
			curr = curr->_child[LEFT];
		}
		else
			curr = curr->_child[RIGHT];
	}
	return (upper_bound);
}

	template<typename value_type, typename Compare, typename Alloc>
		template<typename key_type>
Node<value_type, Alloc> *RBT<value_type, Compare, Alloc>::lower_bound(const key_type  &key)
{
	_NodeType * curr = this->_root._child[LEFT];
	_NodeType *lower_bound = &(this->_root);

	while (curr)
	{
		if (!this->compare_key(*(curr->_p), key) && !this->compare_key(key, *(curr->_p)))
		{
			lower_bound = curr;
			break ;
		}
		if (this->compare_key(key, *(curr->_p)) == true) 
		{
			lower_bound = curr;
			curr = curr->_child[LEFT];
		}
		else
			curr = curr->_child[RIGHT];
	}
	return (lower_bound);
}

	template<typename value_type, typename Compare, typename Alloc>
		template<typename key_type>
Node<value_type, Alloc> *RBT<value_type, Compare, Alloc>::upper_bound(const key_type  &key)
{
	_NodeType * curr = this->_root._child[LEFT];
	_NodeType *upper_bound = &(this->_root);

	while (curr)
	{
		if (this->compare_key(key, *(curr->_p)) == true)
		{
			upper_bound = curr;
			curr = curr->_child[LEFT];
		}
		else
			curr = curr->_child[RIGHT];
	}
	return (upper_bound);
}

// ==	==	==	==	==	==	Global template functions  ==	==	==	==	==	==	

template<typename value_type, typename Alloc> 
Node<value_type, Alloc> *getMin(Node<value_type, Alloc> *node)
{	
	typedef Node<value_type, Alloc> _NodeType;
	_NodeType* tmp_node;

	tmp_node = node;
	while (tmp_node && tmp_node->_child[LEFT])
			tmp_node = tmp_node->_child[LEFT];
	return (tmp_node);
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>* getMax(Node<value_type, Alloc>* node)
{
	if (!(node->_child[RIGHT]))
			return (node);
	return (getMax(node->_child[RIGHT]));
}


template<typename value_type, typename Alloc> 
Node<value_type, Alloc> * decrement(Node<value_type, Alloc> *node)
{

	typedef Node<value_type, Alloc> _NodeType;
	_NodeType *curr_node;
	_NodeType *parent;

	curr_node = node;
	if (curr_node && curr_node->_child[LEFT])
			curr_node = getMax(curr_node->_child[LEFT]);
	else if (curr_node)
	{
		parent = curr_node->_parent;
		while (parent && curr_node == parent->_child[LEFT])
		{
			curr_node = parent;
			parent = parent->_parent;
		}
		curr_node = parent;
	}
	return (curr_node);
}

template <typename value_type, typename Alloc>
Node<value_type, Alloc> *increment(Node<value_type, Alloc> *node)
{
	typedef Node<value_type, Alloc> _NodeType;
	_NodeType *parent;
	_NodeType *curr_node;

	curr_node = node;
	if (curr_node && curr_node->_child[RIGHT])
			curr_node = getMin(curr_node->_child[RIGHT]);
	else if (curr_node)
	{
		parent = curr_node->_parent;
		while (parent != NULL && curr_node == parent->_child[RIGHT] 
					&& curr_node != parent->_child[LEFT])
		{
			curr_node = parent;
			parent = parent->_parent;
		}
		curr_node = parent;
	}
	return (curr_node);
}

#endif /* RBT_HPP */
