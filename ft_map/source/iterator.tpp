
namespace ft
{
	template <class Type>
		class rb_tree_iterator
		{
			public:
				typedef Type value_type;
				typedef Type* pointer;
				typedef Type& reference;
				typedef ptrdiff_t difference_type;
				typedef std::bidirectional_iterator_tag rb_tree_iterator_category;

			private:
				// this is a Node type for now
				typedef Node<Type> _NodeType;
				_NodeType *_m_node;
				void increment();
				void decrement();
				_NodeType * getMin(_NodeType *node);
				_NodeType * getMax(_NodeType *node);

			public:	
				value_type &operator*()
				{
					return (*(this->_m_node->_p));
				}

				rb_tree_iterator();
				rb_tree_iterator(_NodeType *node);
				~rb_tree_iterator();
				rb_tree_iterator(const rb_tree_iterator& it);
				rb_tree_iterator &operator=(const rb_tree_iterator &it);

				rb_tree_iterator &operator++();
				rb_tree_iterator &operator--();
				bool operator!=(const rb_tree_iterator &it);

		};

	template <class Type>
		rb_tree_iterator<Type>::rb_tree_iterator()
		:_m_node(NULL)
		{
		}

	template <class Type>
		rb_tree_iterator<Type>::~rb_tree_iterator()
		{
		}

	template <class Type>
		rb_tree_iterator<Type>::rb_tree_iterator(const rb_tree_iterator &it)
		{
			*this = it;
		}

	template <class Type>
		rb_tree_iterator<Type> &rb_tree_iterator<Type>::operator=(const rb_tree_iterator &it)
		{
			this->_m_node  = it._m_node;	
			return (*this);
		}

	template <class Type>
		rb_tree_iterator<Type>::rb_tree_iterator(_NodeType *node)
			:_m_node(node)
		{
		}
	template <class Type>
		rb_tree_iterator<Type> &rb_tree_iterator<Type>::operator++()
		{
			increment();
			return (*this);
		}
	template <class Type>
		rb_tree_iterator<Type> &rb_tree_iterator<Type>::operator--()
		{
			decrement();
			return (*this);
		}
	template <class Type>
		void rb_tree_iterator<Type>::decrement()
		{
			_NodeType *curr_node;

			curr_node = this->_m_node;
			if (curr_node && curr_node->_child[LEFT])
				curr_node = getMax(curr_node->_child[LEFT]);
			else
				curr_node = curr_node->_parent;
			this->_m_node = curr_node;
		}
	template <class Type>
		void rb_tree_iterator<Type>::increment()
		{
			_NodeType *parent;

			if (this->_m_node && this->_m_node->_child[RIGHT])
				this->_m_node = getMin(this->_m_node->_child[RIGHT]);
			else
			{
				parent = this->_m_node->_parent;
				while (parent != NULL && this->_m_node == parent->_child[RIGHT])
				{
					this->_m_node = parent;
					parent = parent->_parent;
				}
				this->_m_node = parent;
			}
		}
	template <class Type>
		bool rb_tree_iterator<Type>::operator!=(const rb_tree_iterator &it)
		{
			return (this->_m_node != it._m_node);
		}

	template <class Type>
		typename rb_tree_iterator<Type>::_NodeType *rb_tree_iterator<Type>::getMin(_NodeType *node)
		{
			_NodeType *min_node;

			min_node = this->_m_node;
			min_node = node;
			while (min_node && min_node->_child[LEFT])
				min_node = min_node->_child[LEFT];
			return (min_node);
		}

	template <class Type>
		typename rb_tree_iterator<Type>::_NodeType *rb_tree_iterator<Type>::getMax(_NodeType *node)
		{
			_NodeType *min_node;

			min_node = this->_m_node;
			min_node = node;
			while (min_node && min_node->_child[RIGHT])
				min_node = min_node->_child[RIGHT];
			return (min_node);
		}
};
