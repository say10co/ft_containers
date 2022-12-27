
namespace ft
{
		template <class IteratorType>
			class rb_tree_reverse_iterator
			{
				public:
					typedef typename ft::iterator_traits<IteratorType>::value_type  value_type;
					typedef typename ft::iterator_traits<IteratorType>::pointer pointer;
					typedef typename ft::iterator_traits<IteratorType>::reference  reference;
					typedef typename ft::iterator_traits<IteratorType>::difference_type  difference_type;
					typedef typename ft::iterator_traits<IteratorType>::iterator_category iterator_category;

				private:
					IteratorType _m_iterator;

				public:	

					rb_tree_reverse_iterator();
					rb_tree_reverse_iterator(const rb_tree_reverse_iterator &rit);
					rb_tree_reverse_iterator &operator=(const rb_tree_reverse_iterator &rit);
					~rb_tree_reverse_iterator();
					rb_tree_reverse_iterator(const IteratorType &it);

					// constructor from ReverseIterator to ConstRreverseIterator
					template <typename ConstIteratorType>
					rb_tree_reverse_iterator(const rb_tree_reverse_iterator<ConstIteratorType> &rit);

					reference operator*() const;
					pointer operator->() const;
					rb_tree_reverse_iterator &operator++();
					rb_tree_reverse_iterator &operator--();
					rb_tree_reverse_iterator operator++(int);
					rb_tree_reverse_iterator operator--(int);
					bool operator!=(const rb_tree_reverse_iterator &rit);
					bool operator==(const rb_tree_reverse_iterator &rit);

					IteratorType base() const;
			};
			

		template<class IteratorType>
				template <typename ConstIteratorType>
				rb_tree_reverse_iterator<IteratorType>::rb_tree_reverse_iterator(const rb_tree_reverse_iterator<ConstIteratorType> &rit)
					:_m_iterator(rit.base())
				{

				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType>::rb_tree_reverse_iterator()
				:_m_iterator()
				{
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType>::~rb_tree_reverse_iterator()
				{
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType>::rb_tree_reverse_iterator(const rb_tree_reverse_iterator &rit)
				{
						*this = rit;
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType> &rb_tree_reverse_iterator<IteratorType>::operator=(const rb_tree_reverse_iterator &cit)
				{
						this->_m_iterator  = cit.base();	
						return (*this);
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType>::rb_tree_reverse_iterator(const IteratorType  &it)
				:_m_iterator(it)
				{
				}

		template<class IteratorType>
				typename rb_tree_reverse_iterator<IteratorType>::reference rb_tree_reverse_iterator<IteratorType>::operator*() const
				{
					IteratorType tmp(this->_m_iterator);
						
					return (*--tmp);
				}

		template<class IteratorType>
				typename rb_tree_reverse_iterator<IteratorType>::pointer rb_tree_reverse_iterator<IteratorType>::operator->() const
				{
					return &(this->operator*());
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType> &rb_tree_reverse_iterator<IteratorType>::operator++()
				{
					this->_m_iterator--;
					return (*this);
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType> &rb_tree_reverse_iterator<IteratorType>::operator--()
				{
					++this->_m_iterator;
					return (*this);
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType> rb_tree_reverse_iterator<IteratorType>::operator++(int)
				{
					return (this->_m_iterator--);
				}

		template<class IteratorType>
				rb_tree_reverse_iterator<IteratorType> rb_tree_reverse_iterator<IteratorType>::operator--(int)
				{
					return (this->_m_iterator++);
				}
		template<class IteratorType>
				bool rb_tree_reverse_iterator<IteratorType>::operator!=(const rb_tree_reverse_iterator &rit)
				{
					return (!(*this == rit.base()));
				}

		template<class IteratorType>
				bool rb_tree_reverse_iterator<IteratorType>::operator==(const rb_tree_reverse_iterator &rit)
				{
					return (this->_m_iterator == rit.base());
				}

		template<class IteratorType>
				IteratorType  rb_tree_reverse_iterator<IteratorType>::base() const
				{
					return (this->_m_iterator);
				}
};
