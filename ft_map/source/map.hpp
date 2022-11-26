#ifndef MAP_HPP
# define MAP_HPP 
#include <functional>
#include "../../ft_vector/source/vector.hpp"
#include "../../RBT/RBT.hpp"
#include "iterator.tpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
		class map
		{
			public:
				typedef	Key key_type;
				typedef	T mapped_type;
				typedef	pair< key_type, mapped_type> value_type;
				//typedef	pair<const key_type, mapped_type> value_type;
				typedef Compare key_compare;

				typedef Alloc allocator_type;
				typedef typename allocator_type::reference reference;
				typedef typename allocator_type::const_reference const_reference;
				typedef typename allocator_type::pointer pointer;
				typedef typename allocator_type::const_pointer const_pointer;

				typedef rb_tree_iterator<value_type> iterator;
				typedef rb_tree_iterator<const value_type> const_iterator;
				//typedef reverse_iterator;	
				//typedef const_reverse_iterator;	
				//typedef iterator_traits<iterator>::difference_type difference_type;
				typedef size_t size_type;


			private:
				typedef RBT<value_type, Compare, Alloc> RBT_type;
				//RBT<value_type, Compare, Alloc> *_root;
				RBT_type *_root;
				allocator_type _allocator;
				key_compare _comp;
				size_type size;

				template <class Iterator>
					void map_construct_range(Iterator first, Iterator last, std::input_iterator_tag);
				template <class Iterator>
					void map_construct_range(Iterator first, Iterator last, std::forward_iterator_tag);

			public:
				template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

				map (const map& x);
				~map();
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
				iterator begin();
				iterator end();
				const_iterator end() const;

				const_iterator begin() const;

				RBT_type *get_root() { return this->_root ;} 

				void insert (const value_type& val)	
				{
					if (!this->_root)
					{
						this->_root = new RBT_type(val);
						this->_root->get_root()->_color = BLACK;
					}
					else
						this->_root->Insert(val);
					//std::cout << "insert called" << std::endl;
				}
				void print()
				{
					if (this->_root)
						printBT(this->_root->get_root());
				}
		};
};

namespace ft
{
	template < class Key, class T, class Compare, class Alloc>
		map<Key,T,Compare,Alloc>::map (const key_compare& comp, const allocator_type& alloc)
		:_root(NULL), _allocator(alloc), _comp(comp), size(0)
		{
		}

	template < class Key, class T, class Compare, class Alloc>
		template <class InputIterator>
		map<Key,T,Compare,Alloc>::map (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
		:_root(NULL), _allocator(alloc), _comp(comp)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
			//map_construct_range(first, last);
		}

	template < class Key, class T, class Compare, class Alloc>
		map<Key,T,Compare,Alloc>::map (const map& x)
		{
			(void)x;
		}

	template < class Key, class T, class Compare, class Alloc>
		map<Key,T,Compare,Alloc>::~map()
		{
			if (this->_root)
				delete (this->_root);
			//this->_root = NULL;
			std::cout << "~map() called" << std::endl;
		}

	template < class Key, class T, class Compare, class Alloc>
		template <class Iterator>
		void map<Key,T,Compare,Alloc>::map_construct_range(Iterator first, Iterator last, std::input_iterator_tag)
		{
			(void)first;
			(void)last;
		}

	template < class Key, class T, class Compare, class Alloc>
		template <class Iterator>
		void map<Key,T,Compare,Alloc>::map_construct_range(Iterator first, Iterator last, std::forward_iterator_tag)
		{
			(void)first;
			(void)last;
		}

	template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::iterator  map<Key,T,Compare,Alloc>::begin()
		{
			return (this->_root->getMin());
		}
	template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::const_iterator  map<Key,T,Compare,Alloc>::begin() const
		{
			return (this->_root->getMin());
		}

	template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::iterator  map<Key,T,Compare,Alloc>::end()
		{
			return (NULL);
		}
	template < class Key, class T, class Compare, class Alloc>
		typename map<Key,T,Compare,Alloc>::const_iterator  map<Key,T,Compare,Alloc>::end() const
		{
			return (NULL);
		}
};
#endif /* MAP_HPP */
