#ifndef RBT_SET1_HPP
# define RBT_SET1_HPP 

#include "RBT.hpp"

template<typename value_type, typename Compare, typename Alloc> 
class RBT_set : public RBT<value_type, Compare, Alloc>
{
	protected:
		typedef typename RBT<value_type, Compare, Alloc>::_NodeType  _NodeType;
		typedef typename RBT<value_type, Compare, Alloc>::size_type  size_type;

		bool compare_key(const value_type &lhs, const value_type &rhs) const
		{
			return (this->_comp_obj(lhs, rhs));
		}

	public:
		_NodeType *find_node(const value_type &key) const;
		_NodeType *get_bound(const value_type &key, bool bound) const;

};

template<typename value_type, typename Compare, typename Alloc> 
typename RBT_set<value_type,Compare,Alloc>::_NodeType *RBT_set<value_type,Compare,Alloc>::find_node(const value_type &key) const
{
		bool side;
		_NodeType *node = this->_root._child[RIGHT];

		while (node)
		{
				if (!this->compare_key(*(node->_p), key) && !this->compare_key(key, *(node->_p)))
						return (node);
				side = this->compare_key(*(node->_p), key);
				node = node->_child[side];
		}
		return (NULL);
}

template<typename value_type, typename Compare, typename Alloc> 
typename RBT_set<value_type,Compare,Alloc>::_NodeType *RBT_set<value_type,Compare,Alloc>::get_bound(const value_type &key, bool bound) const
{
		bool side;
		bool upper(1);
		bool cond;

		_NodeType *node = this->_root._child[RIGHT];

		while (node)
		{
				cond = this->compare_key(key, *(node->_p));
				if (bound == upper && cond)
						return (node);
				else if (bound == 0 && !cond)
						return (node);

				side = !bound;
				node = node->_child[side];
		}
		return (NULL);
}

#endif /* RBT_SET1_HPP */
