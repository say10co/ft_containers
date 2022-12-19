#ifndef NODECLASS_HPP
# define NODECLASS_HPP 

#define LEFT 0
#define RIGHT 1

template<typename value_type, typename Alloc> 
struct Node
{
		typedef value_type val_type;

		value_type	*_p;
		struct Node *_parent;
		struct Node **_child;
		int			_color;
		Alloc		_allocator;
		
		Node();
		Node(const value_type &value, Node *parent);
		~Node();
};

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::Node() : _p(NULL), _parent(NULL), _allocator()
{
	_child = new Node* [2];
	this->_child[LEFT] = NULL;
	this->_child[RIGHT] = NULL;
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::Node(const value_type &value, Node *parent)
	:_allocator()
{
	this->_p = _allocator.allocate(sizeof(value_type)) ;
	this->_allocator.construct(this->_p, value);
	this->_color = 1;

	_child = new Node* [2];
	this->_child[LEFT] = NULL;
	this->_child[RIGHT] = NULL;
	this->_parent = parent;
}

template<typename value_type, typename Alloc> 
Node<value_type, Alloc>::~Node()
{
	if (this->_p)
	{
		this->_allocator.destroy(this->_p);
		this->_allocator.deallocate(this->_p, sizeof(value_type));
		this->_p = NULL;
	}
	delete [](this->_child);
	this->_child = NULL;
}

#endif /* NODECLASS_HPP */
