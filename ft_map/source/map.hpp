#ifndef MAP_HPP
# define MAP_HPP 

#include <functional>
#include "../../utils/compare.hpp"
#include "../../utils/pair.hpp"
#include "../../utils/enable_if.hpp"
#include "../../utils/iterator_traits.hpp"
#include "../../RBT/RBT.hpp"
#include "iterator.tpp"
#include "reverse_iterator.tpp"

namespace ft
{
		template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
				class map
				{

						
						public:
								typedef	Key key_type;
								typedef	T mapped_type;
								typedef	pair<const key_type, mapped_type> value_type;
								typedef Compare key_compare;

								typedef Alloc allocator_type;
								typedef typename allocator_type::reference reference;
								typedef typename allocator_type::const_reference const_reference;
								typedef typename allocator_type::pointer pointer;
								typedef typename allocator_type::const_pointer const_pointer;

								typedef rb_tree_iterator<value_type, false> iterator;
								typedef rb_tree_iterator<value_type, true> const_iterator;
								typedef typename iterator_traits<iterator>::difference_type difference_type;
								typedef rb_tree_reverse_iterator<iterator> reverse_iterator;	
								typedef rb_tree_reverse_iterator<const_iterator> const_reverse_iterator;	
								//typedef iterator_traits<iterator>::difference_type difference_type;
								typedef size_t size_type;

						public:

							class value_compare
							{
									friend class map;
								protected:
									Compare comp;
								 	value_compare (Compare c) : comp(c) {}
								public:
								 	typedef bool result_type;
								 	typedef value_type first_argument_type;
								 	typedef value_type second_argument_type;
								 	bool operator() (const value_type& x, const value_type& y) const
								 	{
										return comp(x.first, y.first);
									}
							};

						private:
								typedef RBT<value_type, Compare, Alloc> RBT_type;
								//RBT<value_type, Compare, Alloc> *_root;

								allocator_type _allocator;
								key_compare _comp;
								size_type _size;
								RBT_type *_root;

								template <typename IteratorType>
								IteratorType get_bound(const key_type &key, bool bound) const;



								//template <class Iterator>
								//		void map_construct_range(Iterator first, Iterator last, std::input_iterator_tag);
								//template <class Iterator>
								//		void map_construct_range(Iterator first, Iterator last, std::forward_iterator_tag);


						public:
						
								//value_compare value_comp;

								// Capacity
								bool empty() const;
								size_type size() const;
								size_type max_size() const;

								mapped_type& operator[] (const key_type& k);
								void erase (iterator position);
								size_type erase (const key_type& key);
								void erase (iterator first, iterator last);
								void swap (map& x);
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
										map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

								map (const map& x);
								~map();
								explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
								map& operator= (const map& x);
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


								Node<value_type> *base_insert(const value_type& val)
								{
										//std::cout << "insert : " << val.first << std::endl;
										return ( this->_root->Insert(val));
								}
								void print()
								{
										//if (this->_root)
										//printBT(this->_root->get_root()->_child[LEFT]);
								}
				};
};

namespace ft
{
		template < class Key, class T, class Compare, class Alloc>
				map<Key,T,Compare,Alloc>::map (const key_compare& comp, const allocator_type& alloc)
					:_allocator(alloc), _comp(comp), _size(0)//, value_comp(comp)
				{
						this->_root = new RBT_type();
				}

		template < class Key, class T, class Compare, class Alloc>
				template <class InputIterator>
				map<Key,T,Compare,Alloc>::map (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
					:_allocator(alloc), _comp(comp), _size(0)//, value_comp(comp)
				{
						this->_root = new RBT_type();
						this->insert(first, last);
						//while (first != last)
						//{
						//		this->insert(*first);
						//		first++;
						//		//this->_size++;
						//}
						//this->_size = this->_root->GetTreesize();
				}

		template < class Key, class T, class Compare, class Alloc>
				map<Key,T,Compare,Alloc>::map (const map& x)
					:_allocator(x._allocator), _comp(x._comp), _size(x._size)//, value_comp(x.value_comp)
				{
						this->_root = NULL;
						*this = x;
				}

		template < class Key, class T, class Compare, class Alloc>
				map<Key,T,Compare,Alloc> &map<Key,T,Compare,Alloc>::operator=(const map& x)
				{
						const_iterator begin = x.begin();
						const_iterator end = x.end();

						delete (this->_root);
						this->_root = new RBT_type();
						while (begin != end)
								this->insert(*begin++);
						this->_size = x._size;
						this->_comp = x._comp;
						//this->value_comp = x.value_comp;
						assert(this->_size ==  this->_root->GetTreesize());
						//allocator
						return (*this);
				}

		template < class Key, class T, class Compare, class Alloc>
				map<Key,T,Compare,Alloc>::~map()
				{
						//std::cout << "~map() called" << std::endl;
						delete (this->_root);
				}

		//template < class Key, class T, class Compare, class Alloc>
		//		template <class Iterator>
		//		void map<Key,T,Compare,Alloc>::map_construct_range(Iterator first, Iterator last, std::input_iterator_tag)
		//		{
		//				(void)first;
		//				(void)last;
		//		}

		//template < class Key, class T, class Compare, class Alloc>
		//		template <class Iterator>

		//		void map<Key,T,Compare,Alloc>::map_construct_range(Iterator first, Iterator last, std::forward_iterator_tag)
		//		{
		//				(void)first;
		//				(void)last;
		//		}

		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::iterator  map<Key,T,Compare,Alloc>::begin()
				{
						iterator it;

						if (!this->_size)
								return (this->_root->get_root());

						it = this->_root->get_root();
						return (it.get_begin());
						//return (this->_root.begin());
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::const_iterator  map<Key,T,Compare,Alloc>::begin() const
				{
						const_iterator cit;

						if (!this->_size)
								return (this->_root->get_root());
						cit = this->_root->get_root();
						return (cit.get_begin());
						//return (this->_root.begin());
				}

		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::iterator  map<Key,T,Compare,Alloc>::end()
				{
						return (this->_root->end());
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::const_iterator  map<Key,T,Compare,Alloc>::end() const
				{
						return (this->_root->end());
				}
		template < class Key, class T, class Compare, class Alloc>
				bool map<Key, T, Compare, Alloc>::empty() const
				{
						return (this->_size == 0);
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::size() const
				{
						return (this->_size);
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::max_size() const
				{
						return (this->_allocator.max_size());
				}

		template < class Key, class T, class Compare, class Alloc>
				ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool> map<Key, T, Compare, Alloc>::insert(const value_type &val)
				{
						size_type tmp_size = this->_size;

						iterator it = base_insert(val);
						this->_size = this->_root->GetTreesize();

						return (ft::make_pair(it, (this->_size != tmp_size)));
				}
		template < class Key, class T, class Compare, class Alloc>
			template <class InputIterator>
				void  map<Key, T, Compare, Alloc>::insert (InputIterator first, InputIterator last)
				{
					while(first != last)
						this->insert(*first++);
				}


		template < class Key, class T, class Compare, class Alloc>
				typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::insert(iterator position, const value_type &val)
				{
						(void) position;
						Node<value_type> *ret = base_insert(val);
						this->_size = this->_root->GetTreesize();
						return (ret);
				}

		template < class Key, class T, class Compare, class Alloc>
				typename map<Key, T, Compare, Alloc>::mapped_type& map<Key, T, Compare, Alloc>::operator[] (const key_type& k)
				{
						Node<value_type> *node;
						size_type tmp_size;

						tmp_size = this->_size;
						node = base_insert(ft::make_pair(k, mapped_type()));
						this->_size = this->_root->GetTreesize();

						if (this->_size == tmp_size && 0) // No insertion
								node->_p->second = mapped_type();
						return (node->_p->second);
				}

		template < class Key, class T, class Compare, class Alloc>
				void map<Key,T,Compare,Alloc>::erase(iterator position)
				{
						this->_root->delete_(*position);
						this->_size = this->_root->GetTreesize();
				}

		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::size_type map<Key,T,Compare,Alloc>::erase(const key_type &key)
				{
						size_type tmp_size;

						tmp_size = this->_size;
						this->_root->delete_(ft::make_pair(key, mapped_type()));
						this->_size = this->_root->GetTreesize();
						return (this->_size != tmp_size);
				}
		template < class Key, class T, class Compare, class Alloc>
				void map<Key,T,Compare,Alloc>::erase(iterator first, iterator last)
				{
						while (first != last)
								this->_root->delete_(*first++);

						this->_size = this->_root->GetTreesize();
				}
		template < class Key, class T, class Compare, class Alloc>
				void map<Key,T,Compare,Alloc>::swap(map &x)
				{
						std::swap(this->_size, x._size);
						std::swap(this->_root, x._root);
						std::swap(this->_comp, x._comp);
						std::swap(this->_allocator, x._allocator);
				}
		template < class Key, class T, class Compare, class Alloc>
				void map<Key,T,Compare,Alloc>::clear()
				{
						this->_root->deleteRBT(this->_root->get_root()->_child[LEFT]);
						this->_size = 0;
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::key_compare map<Key,T,Compare,Alloc>::key_comp() const
				{
						return (this->_comp);
				}
			template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::value_compare  map<Key,T,Compare,Alloc>::value_comp() const
				{
					return (value_compare(this->_comp));
				}
			template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::allocator_type  map<Key,T,Compare,Alloc>::map<Key,T,Compare,Alloc>::get_allocator() const
				{
					return (this->_allocator);
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::iterator map<Key,T,Compare,Alloc>::find(const key_type &key)
				{
						Node<value_type> * n = this->_root->find_node(key);

						if (!n)
								return (end());
						return (n);
				}

		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::const_iterator map<Key,T,Compare,Alloc>::find(const key_type &key) const
				{
						Node<value_type> *const n = this->_root->find_node(key);

						if (!n)
								return (this->end());
						return (n);
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::size_type  map<Key,T,Compare,Alloc>::count(const key_type &key) const
				{
						return (this->find(key) != this->end());
				}
		template < class Key, class T, class Compare, class Alloc>
			template <typename IteratorType>
			IteratorType map<Key,T,Compare,Alloc>::get_bound(const key_type &key, bool bound) const
			{
				bool upper_bound(1);
				bool lower_bound(0);

				IteratorType begin = this->begin();
				IteratorType end = this->end();
				while (begin != end)
				{
					if (bound == upper_bound && this->_comp(key, begin->first))
						return (begin);
					if (bound == lower_bound && !this->_comp(begin->first, key))
						return (begin);
					begin++;
				}	
				return (end);

			}
		
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::iterator map<Key,T,Compare,Alloc>::lower_bound(const key_type &key)
				{
						return (this->get_bound<iterator>(key, 0));
						//Node<vanue_type> *n;

						//n = this->_root->get_bound(key, 0); // Zero(0) for lower
						//if (!n)
						//		return (this->end());
						//return (n);
				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::const_iterator map<Key,T,Compare,Alloc>::lower_bound(const key_type &key) const
				{
						return (this->get_bound<const_iterator>(key, 0));
						//Node<value_type> * const n = this->_root->get_bound(key, 0); // Zero(0) for lower

						//if (!n)
						//		return (end());
						//return (n);

				}
		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::iterator map<Key,T,Compare,Alloc>::upper_bound(const key_type &key)
				{

						return (this->get_bound<iterator>(key, 1));
						Node<value_type> *n;

						n = this->_root->get_bound(key, 1); // One(0) for upper
						if (!n)
								return (end());
						return (n);

				}

		template < class Key, class T, class Compare, class Alloc>
				typename map<Key,T,Compare,Alloc>::const_iterator map<Key,T,Compare,Alloc>::upper_bound(const key_type &key) const
				{
						return (this->get_bound<const_iterator>(key, 1));
						Node<value_type> * const n = this->_root->get_bound(key, 1); // One(1) for upper
						if (!n)
								return (end());
						return (n);

				}
		template < class Key, class T, class Compare, class Alloc>
				ft::pair<typename map<Key,T,Compare,Alloc>::const_iterator,typename map<Key,T,Compare,Alloc>::const_iterator> 
				map<Key,T,Compare,Alloc>::equal_range (const key_type& k) const
				{
						return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}
		template < class Key, class T, class Compare, class Alloc>
				ft::pair<typename map<Key,T,Compare,Alloc>::iterator,typename map<Key,T,Compare,Alloc>::iterator> 
				map<Key,T,Compare,Alloc>::equal_range (const key_type& k)
				{
						return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}
		template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::reverse_iterator map<Key,T,Compare,Alloc>::rbegin()
			{
				return (this->end());
			}
		template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::const_reverse_iterator map<Key,T,Compare,Alloc>::rbegin() const
			{
				return (this->end());
			}
		template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::reverse_iterator map<Key,T,Compare,Alloc>::rend()
			{
				return (this->begin());
			}
		template < class Key, class T, class Compare, class Alloc>
			typename map<Key,T,Compare,Alloc>::const_reverse_iterator map<Key,T,Compare,Alloc>::rend() const
			{
				return (this->begin());
			}

		template < class Key, class T, class Compare, class Alloc>
				bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
						if (lhs.size() != rhs.size())
								return (false);
						return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
				}
		template <class Key, class T, class Compare, class Alloc>  
				bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
						return (! (lhs == rhs) );

				}
		template <class Key, class T, class Compare, class Alloc>  
				bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
						return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
				}
		template <class Key, class T, class Compare, class Alloc>  
				bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
						return (!(rhs < lhs));
				}
		template <class Key, class T, class Compare, class Alloc>  
				bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
						return (rhs < lhs);
				}
		template <class Key, class T, class Compare, class Alloc>  
				bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
						return (!(lhs < rhs));
				}
		template <class Key, class T, class Compare, class Alloc>
		void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
		{
			x.swap(y);
		}
};

#endif /* MAP_HPP */
