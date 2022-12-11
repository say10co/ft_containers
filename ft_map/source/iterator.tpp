
namespace ft
{
		template <class Type, bool is_const>
				class rb_tree_iterator
				{
						public:
								typedef Type value_type;
								typedef typename deduce<is_const, const Type*, Type*>::type pointer;
								typedef typename deduce<is_const, const Type&, Type&>::type reference;

								typedef ptrdiff_t difference_type;
								typedef std::bidirectional_iterator_tag iterator_category;

						private:

								typedef Node<Type> _NodeType;
								_NodeType *_m_node;
								void increment();
								void decrement();
								_NodeType*  getMin(_NodeType* node);
								_NodeType*  getMax(_NodeType* node);

						public:	

								rb_tree_iterator();
								rb_tree_iterator(const rb_tree_iterator& it);
								rb_tree_iterator &operator=(const rb_tree_iterator &it);
								~rb_tree_iterator();
								rb_tree_iterator(_NodeType*  node);
								rb_tree_iterator(const _NodeType*  node);

								reference operator*() const;
								pointer operator->()const ;
								rb_tree_iterator &operator++();
								rb_tree_iterator &operator--();
								rb_tree_iterator operator++(int);
								rb_tree_iterator operator--(int);
								bool operator!=(const rb_tree_iterator &it);
								bool operator==(const rb_tree_iterator &it);
								
						public:
								_NodeType *get_node() const
								{
									return (this->_m_node);
								}
								template <class C_Type, bool _const>
								rb_tree_iterator(const rb_tree_iterator<C_Type, _const> &c_iterator)
									:_m_node(c_iterator.get_node()) // converst from _NodeType to const _NodeType
								{
			
								}
							 	rb_tree_iterator &get_begin()
								{
									this->_m_node = getMin(this->_m_node);
									return *this;
								}

				};

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const>::rb_tree_iterator()
				:_m_node(NULL)
				{
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const>::~rb_tree_iterator()
				{
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const>::rb_tree_iterator(const rb_tree_iterator &it)
				{
						*this = it;
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> &rb_tree_iterator<Type, is_const>::operator=(const rb_tree_iterator &it)
				{
						this->_m_node  = it._m_node;	
						return (*this);
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const>::rb_tree_iterator(_NodeType*  node )
				:_m_node(node)
				{
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const>::rb_tree_iterator(const _NodeType*  node )
				:_m_node(const_cast<_NodeType *>(node))
				{
				}

		template<typename Type, bool is_const>
				typename rb_tree_iterator<Type, is_const>::reference rb_tree_iterator<Type, is_const>::operator*() const
				{
						return (*(this->_m_node->_p));
				}

		template<typename Type, bool is_const>
				typename rb_tree_iterator<Type, is_const>::pointer rb_tree_iterator<Type, is_const>::operator->() const
				{
						return (this->_m_node->_p);
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> &rb_tree_iterator<Type, is_const>::operator++()
				{
						increment();
						return (*this);
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> &rb_tree_iterator<Type, is_const>::operator--()
				{
						decrement();
						return (*this);
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> rb_tree_iterator<Type, is_const>::operator++(int)
				{
						_NodeType *curr_node;
						curr_node = this->_m_node;
						increment();
						return (rb_tree_iterator(curr_node));
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> rb_tree_iterator<Type, is_const>::operator--(int)
				{
						_NodeType *curr_node;
						curr_node = this->_m_node;
						decrement();
						return (curr_node);
				}

		template<typename Type, bool is_const>
				void rb_tree_iterator<Type, is_const>::decrement()
				{
						_NodeType *curr_node;
						_NodeType *parent;

						curr_node = this->_m_node;
						if (curr_node && curr_node->_child[LEFT])
								curr_node = getMax(curr_node->_child[LEFT]);
						else
						{
								parent = curr_node->_parent;
								while (parent && curr_node == parent->_child[LEFT])
								{
										curr_node = parent;
										parent = parent->_parent;
								}
								curr_node = parent;
						}
						this->_m_node = curr_node;
				}

		template<typename Type, bool is_const>
				void rb_tree_iterator<Type, is_const>::increment()
				{
						_NodeType *parent;
						_NodeType *tmp_node;

						tmp_node = this->_m_node;
						if (this->_m_node && this->_m_node->_child[RIGHT])
								this->_m_node = getMin(this->_m_node->_child[RIGHT]);
						else
						{
								parent = this->_m_node->_parent;
								while (parent != NULL && this->_m_node == parent->_child[RIGHT] 
												&& this->_m_node != parent->_child[LEFT])
								{
										this->_m_node = parent;
										parent = parent->_parent;
								}
								this->_m_node = parent;
						}
				}

		template<typename Type, bool is_const>
				bool rb_tree_iterator<Type, is_const>::operator!=(const rb_tree_iterator &it)
				{
						return (!(*this == it));
				}

		template<typename Type, bool is_const>
				bool rb_tree_iterator<Type, is_const>::operator==(const rb_tree_iterator &it)
				{
						return (this->_m_node == it._m_node);
				}

		template<typename Type, bool is_const>
				typename rb_tree_iterator<Type, is_const>::_NodeType * rb_tree_iterator<Type, is_const>::getMin(_NodeType *node)
				{
						_NodeType *min_node;

						min_node = node;
						if (node && !node->_p)
							min_node = node->_child[LEFT]; // min_node is dummy_root;

						while (min_node && min_node->_child[LEFT])
								min_node = min_node->_child[LEFT];
						return (min_node);
				}

		template<typename Type, bool is_const>
				typename rb_tree_iterator<Type, is_const>::_NodeType *rb_tree_iterator<Type, is_const>::getMax(_NodeType *node)
				{
						_NodeType *max_node;

						max_node = node;
						if (max_node && !max_node->_p)
							max_node = max_node->_child[RIGHT];// max_node is dummy root

						while (max_node && max_node->_child[RIGHT])
								max_node = max_node->_child[RIGHT];
						return (max_node);
				}
};
