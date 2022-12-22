#ifndef RBT_MAP_HPP
# define RBT_MAP_HPP 
#include "RBT.hpp"

template<typename value_type, typename Compare, typename Alloc> 
class RBT_map : public RBT<value_type, Compare, Alloc>
{
	protected:
		typedef typename RBT<value_type, Compare, Alloc>::_NodeType  _NodeType;
		typedef typename RBT<value_type, Compare, Alloc>::size_type  size_type;
		typedef const typename  value_type::first_type  key_type;

		bool compare_key(const value_type &lhs, const value_type &rhs) const
		{
			return (this->_comp_obj(lhs.first, rhs.first));
		}

	public:
		_NodeType *find_node(const typename value_type::first_type &key) const;
		_NodeType *get_bound(const typename  value_type::first_type &key, bool bound);
		const _NodeType *get_bound(const typename  value_type::first_type &key, bool bound) const;

};

template<typename value_type, typename Compare, typename Alloc> 
typename RBT_map<value_type,Compare,Alloc>::_NodeType *RBT_map<value_type,Compare,Alloc>::find_node(const typename  value_type::first_type &key) const
{
		bool side;
		_NodeType *node = this->_root._child[RIGHT];
		value_type p_key(key, typename value_type::second_type());

		while (node)
		{
				if (!this->compare_key(*(node->_p), p_key) && !this->compare_key(p_key, *(node->_p)))
						return (node);
				side = this->compare_key(*(node->_p), p_key);
				node = node->_child[side];
		}
		return (NULL);
}

template<typename value_type, typename Compare, typename Alloc> 
const typename RBT_map<value_type,Compare,Alloc>::_NodeType *RBT_map<value_type,Compare,Alloc>::get_bound(const typename  value_type::first_type &key, bool bound) const
{
			
		bool upper(1);
		typedef typename value_type::second_type mapped_type;

		if (bound == upper)
			return(this->upper_bound(ft::make_pair(key, mapped_type())));
		return (this->lower_bound(ft::make_pair(key, mapped_type())));
}

template<typename value_type, typename Compare, typename Alloc> 
typename RBT_map<value_type,Compare,Alloc>::_NodeType *RBT_map<value_type,Compare,Alloc>::get_bound(const typename  value_type::first_type &key, bool bound)
{
			
		bool upper(1);
		typedef typename value_type::second_type mapped_type;

		if (bound == upper)
			return(this->upper_bound(ft::make_pair(key, mapped_type())));
		return (this->lower_bound(ft::make_pair(key, mapped_type())));
}

#endif /* RBT_MAP_HPP */
