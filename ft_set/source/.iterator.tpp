#include "../../RBT/RBT.hpp"

namespace ft
{
		template <class Type, bool is_const>
				class rb_tree_iterator
				{
						public:
								typedef typename Type::val_type  value_type;
								typedef typename deduce<is_const, const value_type*, value_type*>::type pointer;
								typedef typename deduce<is_const, const value_type&, value_type&>::type reference;

								typedef ptrdiff_t difference_type;
								typedef std::bidirectional_iterator_tag iterator_category;

						private:

								typedef Type _NodeType;

								_NodeType *_m_node;
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
								_NodeType *base() const
								{
									return (this->_m_node);
								}
								template <bool _const>
								rb_tree_iterator(const rb_tree_iterator<Type, _const> &c_iterator)
									:_m_node(c_iterator.base()) 
								{
			
								}

				};

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const>::rb_tree_iterator()
				:/*_m_tree(NULL), */_m_node(NULL)
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
							this->_m_node = increment(this->_m_node);
						return (*this);
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> &rb_tree_iterator<Type, is_const>::operator--()
				{
							this->_m_node = decrement(this->_m_node);
						return (*this);
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> rb_tree_iterator<Type, is_const>::operator++(int)
				{
						_NodeType *curr_node;
						curr_node = this->_m_node;
							this->_m_node = increment(this->_m_node);
						return (rb_tree_iterator(curr_node));
				}

		template<typename Type, bool is_const>
				rb_tree_iterator<Type, is_const> rb_tree_iterator<Type, is_const>::operator--(int)
				{
						_NodeType *curr_node;
						curr_node = this->_m_node;
							this->_m_node = decrement(this->_m_node);
						return (rb_tree_iterator(curr_node));
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
