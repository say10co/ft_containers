#ifndef MAP_HPP
# define MAP_HPP 

#include <functional>
#include "../../utils/compare.hpp"
#include "../../utils/pair.hpp"
#include "../../utils/enable_if.hpp"
#include "../../utils/iterator_traits.hpp"
#include "../RBT.hpp"
#include "iterator.tpp"
#include "reverse_iterator.tpp"

namespace ft
{
		template < class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> > 
				class set
				{


						public:
								typedef	Key key_type;
								typedef	Key value_type;
								typedef Compare value_compare;
								typedef Compare key_compare;

								typedef RBT<value_type, Compare, Alloc> _Tree_type; 

								typedef Alloc allocator_type;
								typedef typename allocator_type::reference reference;
								typedef typename allocator_type::const_reference const_reference;
								typedef typename allocator_type::pointer pointer;
								typedef typename allocator_type::const_pointer const_pointer;

								typedef Node<value_type, allocator_type> _NodeType;

								typedef rb_tree_iterator<_NodeType, false> iterator;
								typedef rb_tree_iterator<_NodeType, true> const_iterator;
								typedef typename iterator_traits<iterator>::difference_type difference_type;
								typedef rb_tree_reverse_iterator<iterator> reverse_iterator;	
								typedef rb_tree_reverse_iterator<const_iterator> const_reverse_iterator;	
								typedef size_t size_type;

						public:

								//class value_compare : public std::binary_function<value_type,value_type,bool>
								//{
								//		friend class set;
								//		protected:
								//			Compare comp;
								//			value_compare (Compare c) : comp(c) {}
								//		public:
								//			typedef bool result_type;
								//			typedef value_type first_argument_type;
								//			typedef value_type second_argument_type;
								//			bool operator() (const value_type& x, const value_type& y) const
								//			{
								//					return comp(x, y);
								//			}
								//};

						private:
								typedef RBT<value_type, Compare, Alloc> RBT_type;

								allocator_type _allocator;
								key_compare _comp;
								size_type _size;
								RBT_type *_root;

								template <typename IteratorType>
										IteratorType get_bound(const key_type &key, bool bound) const;

						public:

								// Capacity
								bool empty() const;
								size_type size() const;
								size_type max_size() const;

								//value_type& operator[] (const key_type& k);
								void erase (iterator position);
								size_type erase (const key_type& key);
								void erase (iterator first, iterator last);
								void swap (set& x);
								void clear();

								key_compare key_comp() const;
								value_compare value_comp() const;

								iterator find (const key_type& k);
								const_iterator find (const key_type& k) const;
								size_type count (const key_type& k) const;
								iterator lower_bound (const key_type& k);
								const_iterator lower_bound (const key_type& k) const;
								iterator upper_bound (const key_type& k);
								const_iterator upper_bound (const key_type& k) const;

								ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
								ft::pair<iterator,iterator>             equal_range (const key_type& k);


								template <class InputIterator>
										set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

								set (const set& x);
								~set();
								explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
								set& operator= (const set& x);
								iterator begin();
								iterator end();
								const_iterator begin() const;
								const_iterator end() const;
								reverse_iterator rbegin();
								const_reverse_iterator rbegin() const;
								reverse_iterator rend();
								const_reverse_iterator rend() const;

								RBT_type *get_root() { return this->_root ;} 
								ft::pair<iterator, bool> insert (const value_type& val);
								iterator insert (iterator position, const value_type& val);
								template <class InputIterator>
										void insert (InputIterator first, InputIterator last);
								allocator_type get_allocator() const;


								_NodeType *base_insert(const value_type& val)
								{
										return ( this->_root->Insert(val));
								}
								void print()
								{
								}
				};
};

namespace ft
{
		template <class Key, class Compare, class Alloc>
				set<Key,Compare,Alloc>::set (const key_compare& comp, const allocator_type& alloc)
				:_allocator(alloc), _comp(comp), _size(0)
				{
						this->_root = new RBT_type();
				}

		template <class Key, class Compare, class Alloc>
				template <class InputIterator>
				set<Key,Compare,Alloc>::set (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
				:_allocator(alloc), _comp(comp), _size(0)
				{
						this->_root = new RBT_type();
						this->insert(first, last);
				}

		template <class Key, class Compare, class Alloc>
				set<Key,Compare,Alloc>::set (const set& x)
				:_allocator(x._allocator), _comp(x._comp), _size(x._size)
				{
						this->_root = NULL;
						*this = x;
				}

		template <class Key, class Compare, class Alloc>
				set<Key,Compare,Alloc> &set<Key,Compare,Alloc>::operator=(const set& x)
				{

						const_iterator begin = x.begin();
						const_iterator end = x.end();
						delete (this->_root);
						this->_root = new RBT_type();
						while (begin != end)
								this->insert(*begin++);
						this->_size = x._size;
						this->_comp = x._comp;
						this->_allocator = x._allocator;
						return (*this);
				}

		template <class Key, class Compare, class Alloc>
				set<Key,Compare,Alloc>::~set()
				{
						delete (this->_root);
				}

		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::iterator  set<Key,Compare,Alloc>::begin()
				{
						return (iterator(this->_root->begin()));
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_iterator  set<Key,Compare,Alloc>::begin() const
				{
						return (const_iterator(this->_root->begin()));
				}

		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::iterator  set<Key,Compare,Alloc>::end()
				{
						return (iterator(this->_root->end()));
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_iterator  set<Key,Compare,Alloc>::end() const
				{
						return (const_iterator(this->_root->end()));
				}
		template <class Key, class Compare, class Alloc>
				bool set<Key, Compare, Alloc>::empty() const
				{
						return (this->_size == 0);
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key, Compare, Alloc>::size_type set<Key, Compare, Alloc>::size() const
				{
						return (this->_size);
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key, Compare, Alloc>::size_type set<Key, Compare, Alloc>::max_size() const
				{
						return (this->_allocator.max_size());
				}

		template <class Key, class Compare, class Alloc>
				ft::pair<typename set<Key, Compare, Alloc>::iterator, bool> set<Key, Compare, Alloc>::insert(const value_type &val)
				{
						size_type tmp_size = this->_size;

						iterator it = iterator(base_insert(val));
						this->_size = this->_root->GetTreesize();

						return (ft::make_pair(it, (this->_size != tmp_size)));
				}
		template <class Key, class Compare, class Alloc>
				template <class InputIterator>
				void  set<Key, Compare, Alloc>::insert (InputIterator first, InputIterator last)
				{
						while(first != last)
								this->insert(*first++);
				}


		template <class Key, class Compare, class Alloc>
				typename set<Key, Compare, Alloc>::iterator set<Key, Compare, Alloc>::insert(iterator position, const value_type &val)
				{
						(void) position;
						_NodeType *ret = base_insert(val);
						this->_size = this->_root->GetTreesize();
						return (iterator(ret));
				}

		//template <class Key, class Compare, class Alloc>
		//		typename set<Key, Compare, Alloc>::value_type& set<Key, Compare, Alloc>::operator[] (const key_type& k)
		//		{
		//				_NodeType *node;
		//				size_type tmp_size;

		//				tmp_size = this->_size;
		//				node = base_insert(k);
		//				this->_size = this->_root->GetTreesize();

		//				if (this->_size == tmp_size && 0) // No insertion
		//						node->_p->second = value_type();
		//				return (node->_p->second);
		//		}

		template <class Key, class Compare, class Alloc>
				void set<Key,Compare,Alloc>::erase(iterator position)
				{
						this->_root->delete_(*position);
						this->_size = this->_root->GetTreesize();
				}

		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::size_type set<Key,Compare,Alloc>::erase(const key_type &key)
				{
						size_type tmp_size;

						tmp_size = this->_size;
						this->_root->delete_(key);
						this->_size = this->_root->GetTreesize();
						return (this->_size != tmp_size);
				}
		template <class Key, class Compare, class Alloc>
				void set<Key,Compare,Alloc>::erase(iterator first, iterator last)
				{
						while (first != last)
								this->_root->delete_(*first++);

						this->_size = this->_root->GetTreesize();
				}
		template <class Key, class Compare, class Alloc>
				void set<Key,Compare,Alloc>::swap(set &x)
				{
						std::swap(this->_size, x._size);
						std::swap(this->_root, x._root);
						std::swap(this->_comp, x._comp);
						std::swap(this->_allocator, x._allocator);
				}
		template <class Key, class Compare, class Alloc>
				void set<Key,Compare,Alloc>::clear()
				{
						this->_root->deleteRBT(this->_root->get_root()->_child[LEFT]);
						this->_size = 0;
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::key_compare set<Key,Compare,Alloc>::key_comp() const
				{
						return (this->_comp);
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::value_compare  set<Key,Compare,Alloc>::value_comp() const
				{
						return (value_compare(this->_comp));
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::allocator_type  set<Key,Compare,Alloc>::set<Key,Compare,Alloc>::get_allocator() const
				{
						return (this->_allocator);
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::iterator set<Key,Compare,Alloc>::find(const key_type &key)
				{
						_NodeType * n = this->_root->find_node(key);

						if (!n)
								return (end());
						return (iterator(n));
				}

		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_iterator set<Key,Compare,Alloc>::find(const key_type &key) const
				{
						_NodeType *const n = this->_root->find_node(key);

						if (!n)
								return (this->end());
						return (const_iterator(n));
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::size_type  set<Key,Compare,Alloc>::count(const key_type &key) const
				{
						return (this->find(key) != this->end());
				}
		template <class Key, class Compare, class Alloc>
				template <typename IteratorType>
				IteratorType set<Key,Compare,Alloc>::get_bound(const key_type &key, bool bound) const
				{
						bool upper_bound(1);
						bool lower_bound(0);

						IteratorType begin = this->begin();
						IteratorType end = this->end();
						while (begin != end)
						{
								if (bound == upper_bound && this->_comp(key, *begin))
										return (begin);
								if (bound == lower_bound && !this->_comp(*begin, key))
										return (begin);
								begin++;
						}	
						return (end);

				}

		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::iterator set<Key,Compare,Alloc>::lower_bound(const key_type &key)
				{
						return (this->get_bound<iterator>(key, 0));
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_iterator set<Key,Compare,Alloc>::lower_bound(const key_type &key) const
				{
						return (this->get_bound<const_iterator>(key, 0));

				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::iterator set<Key,Compare,Alloc>::upper_bound(const key_type &key)
				{
						return (this->get_bound<iterator>(key, 1));
				}

		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_iterator set<Key,Compare,Alloc>::upper_bound(const key_type &key) const
				{
						return (this->get_bound<const_iterator>(key, 1));
						_NodeType * const n = this->_root->get_bound(key, 1); // One(1) for upper
						if (!n)
								return (this->end());

						return (const_iterator(n));

				}
		template <class Key, class Compare, class Alloc>
				ft::pair<typename set<Key,Compare,Alloc>::const_iterator,typename set<Key,Compare,Alloc>::const_iterator> 
				set<Key,Compare,Alloc>::equal_range (const key_type& k) const
				{
						return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}
		template <class Key, class Compare, class Alloc>
				ft::pair<typename set<Key,Compare,Alloc>::iterator,typename set<Key,Compare,Alloc>::iterator> 
				set<Key,Compare,Alloc>::equal_range (const key_type& k)
				{
						return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::reverse_iterator set<Key,Compare,Alloc>::rbegin()
				{
						return (this->end());
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_reverse_iterator set<Key,Compare,Alloc>::rbegin() const
				{
						return (this->end());
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::reverse_iterator set<Key,Compare,Alloc>::rend()
				{
						return (this->begin());
				}
		template <class Key, class Compare, class Alloc>
				typename set<Key,Compare,Alloc>::const_reverse_iterator set<Key,Compare,Alloc>::rend() const
				{
						return (this->begin());
				}

		template <class Key, class Compare, class Alloc>
				bool operator== ( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
				{
						if (lhs.size() != rhs.size())
								return (false);
						return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
				}
		template <class Key, class Compare, class Alloc>  
				bool operator!= ( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
				{
						return (! (lhs == rhs) );

				}
		template <class Key, class Compare, class Alloc>  
				bool operator<  ( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
				{
						return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
				}
		template <class Key, class Compare, class Alloc>  
				bool operator<= ( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
				{
						return (!(rhs < lhs));
				}
		template <class Key, class Compare, class Alloc>  
				bool operator>  ( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
				{
						return (rhs < lhs);
				}
		template <class Key, class Compare, class Alloc>  
				bool operator>= ( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
				{
						return (!(lhs < rhs));
				}
		template <class Key, class Compare, class Alloc>
				void swap (set<Key,Compare,Alloc>& x, set<Key,Compare,Alloc>& y)
				{
						x.swap(y);
				}
};

#endif /* MAP_HPP */
