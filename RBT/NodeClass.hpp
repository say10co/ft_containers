#ifndef NODECLASS_HPP
# define NODECLASS_HPP 

#define LEFT 0
#define RIGHT 1

template<typename value_type, typename Alloc> 
struct Node
{
		typedef typename Alloc::template rebind<Node*>::other	_NodePtr_allocator;
		typedef 												value_type val_type;

		struct Node 											**_child;
		value_type												*_p;
		struct Node 											*_parent;
		int														_color;
		Alloc													_allocator;
		_NodePtr_allocator 										_nodeptr_alloc;
		
		Node();
		Node(const Node& node);
		Node(const value_type &value, Node *parent);
		Node &operator=(const Node &node);
		~Node();
};

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::Node()
	: _p(NULL), _parent(NULL), _allocator(), _nodeptr_alloc()
{
	this->_child = this->_nodeptr_alloc.allocate(2);
	this->_child[LEFT] = NULL;
	this->_child[RIGHT] = NULL;
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::Node(const Node& node)
	:_p(NULL), _parent(NULL), _allocator(), _nodeptr_alloc()
{
	*this = node;
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::Node(const value_type &value, Node *parent)
	:_allocator(), _nodeptr_alloc()
{
	this->_color = 1;
	this->_p = _allocator.allocate(1);
	this->_allocator.construct(this->_p, value);
	this->_child = this->_nodeptr_alloc.allocate(2);
	this->_child[LEFT] = NULL;
	this->_child[RIGHT] = NULL;
	this->_parent = parent;
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc> &Node<value_type, Alloc>::operator=(const Node &node)
{
	if (this->_p)
	{
		this->_allocator.destroy(this->_p);
		this->_allocator.deallocate(this->_p, 1);
		this->_p = NULL;
	}
	if (this->_child)
	{
		this->_nodeptr_alloc.deallocate(this->_child, 2);
		this->_child = NULL;
	}
	if (node._p)
	{
		this->_p = _allocator.allocate(1) ;
		this->_allocator.construct(this->_p, *(node._p));
	}
	this->_child = this->_nodeptr_alloc.allocate(2);
	this->_child[LEFT] = node._child[LEFT];
	this->_child[RIGHT] = node._child[RIGHT];
	this->_color = node._color;
	this->_parent = node._parent;

	return (*this);
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::~Node()
{
	if (this->_p)
	{
		this->_allocator.destroy(this->_p);
		this->_allocator.deallocate(this->_p, 1);
		this->_p = NULL;
	}
	this->_nodeptr_alloc.deallocate(this->_child, 2);
	this->_child = NULL;
}

#endif /* NODECLASS_HPP */
