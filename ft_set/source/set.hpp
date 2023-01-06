#ifndef MAP_HPP
# define MAP_HPP 

#include <functional>
#include "../../utils/compare.hpp"
#include "../../utils/pair.hpp"
#include "../../utils/enable_if.hpp"
#include "../../utils/iterator_traits.hpp"
#include "../../utils/reverse_iterator.hpp"
#include "../../RBT/RBT_set.hpp"
#include "../../ft_map/source/iterator.hpp"

namespace ft
{
	template < class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
		class set
		{
			public:
				typedef	Key														key_type;
				typedef Compare 												key_compare;
				typedef Compare		 											value_compare;
				typedef	Key														value_type;
				typedef Alloc 													allocator_type;
				typedef typename allocator_type::reference 						reference;
				typedef typename allocator_type::const_reference 				const_reference;
				typedef typename allocator_type::pointer 						pointer;
				typedef typename allocator_type::const_pointer					const_pointer;

			private:
				typedef Node<value_type, allocator_type>							_NodeType;

			public:
				typedef size_t 													size_type;
				typedef rb_tree_iterator<_NodeType, true>						const_iterator;
				typedef rb_tree_iterator<_NodeType, false>						iterator;
				typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
				typedef typename iterator_traits<iterator>::difference_type 	difference_type;
			
			private:
				typedef RBT_set<value_type, value_compare, allocator_type>		_Tree_type; 
				typedef typename Alloc::template rebind<_Tree_type>::other		_Tree_alloc_t;

				allocator_type		_allocator;
				_Tree_alloc_t		_tree_allocator;
				key_compare			_comp;
				size_type			_size;
				_Tree_type			*_root;

			private:
				_NodeType *base_insert(const value_type& val);

			public:

				//Constructors:
				template <class InputIterator>
						set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

				explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
				set (const set& x);
				set& operator=(const set& x);
				~set();

				//Iterators 
				iterator begin();
				iterator end();
				reverse_iterator rbegin();
				reverse_iterator rend();

				//Const Iterators
				const_iterator begin() const;
				const_iterator end() const;
				const_reverse_iterator rbegin() const;
				const_reverse_iterator rend() const;

				// Capacity
				bool empty() const;
				size_type size() const;
				size_type max_size() const;

	
				//Modifiers:
					template <class InputIterator>
						void							insert (InputIterator first, InputIterator last);
				ft::pair<iterator, bool>				insert (const value_type& val);
				iterator insert 						(iterator position, const value_type& val);

				size_type								erase (const value_type& key);
				void 									erase (iterator position);
				void 									erase (iterator first, iterator last);
				void 									swap (set& x);
				void 									clear();
				
				//Observers:
				key_compare								key_comp()		const;
				value_compare							value_comp()	const;

				//Operations:
				iterator								find (const value_type& k);
				iterator 								lower_bound (const value_type& k);
				iterator 								upper_bound (const value_type& k);
				ft::pair<iterator,iterator>             equal_range (const value_type& k);
				const_iterator							find (const value_type& k)		const;
				size_type								count (const value_type& k) 		const;
				const_iterator 							lower_bound (const value_type& k) const;
				const_iterator 							upper_bound (const value_type& k) const;
				ft::pair<const_iterator,const_iterator> equal_range (const value_type& k) const;
		
				//Allocator:	
				allocator_type get_allocator() const;
				
		};
};

namespace ft
{
	template < class Key, class Compare, class Alloc>
			set<Key,Compare,Alloc>::set (const key_compare& comp, const allocator_type& alloc)
			:_allocator(alloc), _tree_allocator(), _comp(comp), _size(0)
			{
				this->_root = this->_tree_allocator.allocate(1);
				this->_tree_allocator.construct(this->_root, _Tree_type());
			}

	template < class Key, class Compare, class Alloc>
			template <class InputIterator>
			set<Key,Compare,Alloc>::set (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
			:_allocator(alloc), _tree_allocator(), _comp(comp), _size(0)
			{
				this->_root = this->_tree_allocator.allocate(1);
				this->_tree_allocator.construct(this->_root, _Tree_type());
				this->insert(first, last);
			}

	template < class Key, class Compare, class Alloc>
			set<Key,Compare,Alloc>::set (const set& x)
			:_allocator(x._allocator), _tree_allocator(x._tree_allocator), _comp(x._comp), _size(x._size)
			{
				this->_root = NULL;
				*this = x;
			}

	template < class Key, class Compare, class Alloc>
			set<Key,Compare,Alloc> &set<Key,Compare,Alloc>::operator=(const set& x)
			{
				if (this->_root != NULL)
				{
					this->_tree_allocator.destroy(this->_root);
					this->_tree_allocator.deallocate(this->_root, 1);
				}
				this->_root = this->_tree_allocator.allocate(1);
				this->_tree_allocator.construct(this->_root, _Tree_type());
				if (x._size)
					this->_root->copy_tree(*(x._root));
				this->_size = x._size;
				this->_comp = x._comp;
				this->_allocator = x._allocator;
				return (*this);
			}

	template < class Key, class Compare, class Alloc>
			set<Key,Compare,Alloc>::~set()
			{
				if (this->_root)
				{
					this->_tree_allocator.destroy(this->_root);
					this->_tree_allocator.deallocate(this->_root, 1);
				}
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::iterator  set<Key,Compare,Alloc>::begin()
			{
				return (iterator(this->_root->begin()));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_iterator  set<Key,Compare,Alloc>::begin() const
			{
				return (const_iterator(this->_root->begin()));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::iterator  set<Key,Compare,Alloc>::end()
			{
				return (iterator(this->_root->end()));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_iterator  set<Key,Compare,Alloc>::end() const
			{
				return (const_iterator(this->_root->end()));
			}

	template < class Key, class Compare, class Alloc>
			bool set<Key, Compare, Alloc>::empty() const
			{
				return (this->_size == 0);
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key, Compare, Alloc>::size_type set<Key, Compare, Alloc>::size() const
			{
				return (this->_size);
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key, Compare, Alloc>::size_type set<Key, Compare, Alloc>::max_size() const
			{
				return (this->_allocator.max_size());
			}

	template < class Key, class Compare, class Alloc>
			ft::pair<typename set<Key, Compare, Alloc>::iterator, bool> set<Key, Compare, Alloc>::insert(const value_type &val)
			{
				size_type tmp_size = this->_size;

				iterator it = iterator(this->base_insert(val));
				this->_size = this->_root->GetTreesize();

				return (ft::make_pair(it, (this->_size != tmp_size)));
			}

	template < class Key, class Compare, class Alloc>
			template <class InputIterator>
			void  set<Key, Compare, Alloc>::insert (InputIterator first, InputIterator last)
			{
				while(first != last)
					this->insert(*first++);
			}


	template < class Key, class Compare, class Alloc>
			typename set<Key, Compare, Alloc>::iterator set<Key, Compare, Alloc>::insert(iterator position, const value_type &val)
			{
				(void) position; // :(

				_NodeType *ret = this->base_insert(val);
				this->_size = this->_root->GetTreesize();
				return (iterator(ret));
			}

	template < class Key, class Compare, class Alloc>
			void set<Key,Compare,Alloc>::erase(iterator position)
			{
				this->_root->delete_(*position);
				this->_size = this->_root->GetTreesize();
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::size_type set<Key,Compare,Alloc>::erase(const value_type &key)
			{
				size_type tmp_size;

				tmp_size = this->_size;
				this->_root->delete_(key);
				this->_size = this->_root->GetTreesize();
				return (this->_size != tmp_size);
			}

	template < class Key, class Compare, class Alloc>
			void set<Key,Compare,Alloc>::erase(iterator first, iterator last)
			{
				while (first != last)
					this->_root->delete_(*first++);
				this->_size = this->_root->GetTreesize();
			}

	template < class Key, class Compare, class Alloc>
			void set<Key,Compare,Alloc>::swap(set &x)
			{
				std::swap(this->_size, x._size);
				std::swap(this->_root, x._root);
				std::swap(this->_comp, x._comp);
				std::swap(this->_allocator, x._allocator);
			}

	template < class Key, class Compare, class Alloc>
			void set<Key,Compare,Alloc>::clear()
			{
				this->_root->deleteRBT();
				this->_size = 0;
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::key_compare set<Key,Compare,Alloc>::key_comp() const
			{
				return (this->_comp);
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::value_compare  set<Key,Compare,Alloc>::value_comp() const
			{
				return (value_compare(this->_comp));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::allocator_type  set<Key,Compare,Alloc>::set<Key,Compare,Alloc>::get_allocator() const
			{
				return (this->_allocator);
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::iterator set<Key,Compare,Alloc>::find(const value_type &key)
			{
				_NodeType * n = this->_root->find_node(key);

				if (!n)
					return (end());
				return (iterator(n));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_iterator set<Key,Compare,Alloc>::find(const value_type &key) const
			{
				_NodeType *const n = this->_root->find_node(key);

				if (!n)
						return (this->end());
				return (const_iterator(n));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::size_type  set<Key,Compare,Alloc>::count(const value_type &key) const
			{
				return (this->find(key) != this->end());
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::iterator set<Key,Compare,Alloc>::lower_bound(const value_type &key)
			{
				return (this->_root->get_bound(key, 0));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_iterator set<Key,Compare,Alloc>::lower_bound(const value_type &key) const
			{
				return (this->_root->get_bound(key, 0));

			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::iterator set<Key,Compare,Alloc>::upper_bound(const value_type &key)
			{
				return (this->_root->get_bound(key, 1));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_iterator set<Key,Compare,Alloc>::upper_bound(const value_type &key) const
			{
				return (this->_root->get_bound(key, 1));

			}

	template < class Key, class Compare, class Alloc>
			ft::pair<typename set<Key,Compare,Alloc>::const_iterator,typename set<Key,Compare,Alloc>::const_iterator> 
			set<Key,Compare,Alloc>::equal_range (const value_type& k) const
			{
				return (ft::make_pair(const_iterator(this->_root->get_bound(k, 0)), const_iterator( this->_root->get_bound(k, 1))));
			}

	template < class Key, class Compare, class Alloc>
			ft::pair<typename set<Key,Compare,Alloc>::iterator,typename set<Key,Compare,Alloc>::iterator> 
			set<Key,Compare,Alloc>::equal_range (const value_type& k)
			{
				return (ft::make_pair(iterator(this->_root->get_bound(k, 0)), iterator( this->_root->get_bound(k, 1))));
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::reverse_iterator set<Key,Compare,Alloc>::rbegin()
			{
				return (this->end());
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_reverse_iterator set<Key,Compare,Alloc>::rbegin() const
			{
				return (this->end());
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::reverse_iterator set<Key,Compare,Alloc>::rend()
			{
				return (this->begin());
			}

	template < class Key, class Compare, class Alloc>
			typename set<Key,Compare,Alloc>::const_reverse_iterator set<Key,Compare,Alloc>::rend() const
			{
				return (this->begin());
			}

	template < class Key, class Compare, class Alloc>
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

	template < class Key, class Compare, class Alloc>
	typename set<Key,Compare,Alloc>::_NodeType *set<Key,Compare,Alloc>::base_insert(const value_type& val)
			{
				return ( this->_root->Insert(val));
			}
};

#endif /* MAP_HPP */
