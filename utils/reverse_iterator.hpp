#ifndef REVERSE_ITERATOR_HPP
#define  REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp" 

namespace ft
{
	template<typename Iterator>
		class reverse_iterator
		{

			public:
				typedef typename iterator_traits<Iterator>::value_type value_type;
				typedef typename iterator_traits<Iterator>::pointer pointer;
				typedef typename iterator_traits<Iterator>::reference reference;
				typedef typename iterator_traits<Iterator>::difference_type difference_type;
				typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
				typedef Iterator iterator_type;
				typedef size_t size_type;

			private:
				iterator_type _base_it;

			public:

				template<typename Iter>
					reverse_iterator(const reverse_iterator<Iter> &rev_it);
				reverse_iterator(const iterator_type &it);
				reverse_iterator &operator=(const reverse_iterator &it);
				reverse_iterator(); 
				~reverse_iterator();

				reverse_iterator operator++(int);
				reverse_iterator &operator++(void);
				reverse_iterator operator--(int);
				reverse_iterator &operator--(void);

				reverse_iterator operator-(difference_type n) const;
				reverse_iterator operator+(difference_type n) const;

				reverse_iterator &operator+=(int n);
				reverse_iterator &operator-=(int n);

				pointer operator->();
				reference operator*();
				reference operator[](difference_type n) const;

				iterator_type base() const;

				template <typename Iter> bool operator==(const reverse_iterator<Iter>& rhs) const ;
				template <typename Iter> bool operator!=(const reverse_iterator<Iter>& rhs) const ;
				template <typename Iter> bool operator>=(const reverse_iterator<Iter>& rhs) const ;
				template <typename Iter> bool operator<=(const reverse_iterator<Iter>& rhs) const ;
				template <typename Iter> bool operator >(const reverse_iterator<Iter>& rhs) const  ; 
				template <typename Iter> bool operator <(const reverse_iterator<Iter>& rhs) const  ; 


		};

	template<typename type>
		typename reverse_iterator<type>::iterator_type reverse_iterator<type>::base() const
		{
			return (this->_base_it);
		}

	template<typename type>
		reverse_iterator<type>::reverse_iterator()
		:_base_it()
		{
		}

	template<typename type>
		reverse_iterator<type>::reverse_iterator(const iterator_type &it)
		:_base_it(it)
		{
		}

	template<typename type>
		template<typename Iter>
		reverse_iterator<type>::reverse_iterator(const reverse_iterator<Iter>  &it)
		{
			this->_base_it = it.base();
		}

	template<typename type>
		reverse_iterator<type>::~reverse_iterator()
		{
		}

	template<typename Iter, typename Iter1>
		typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter> &it, 
				const reverse_iterator<Iter1> &it1) 
		{
			//The function returns the same as subtracting lhs's base iterator from rhs's base iterator. 
			return (it1.base() - it.base());
		}

	template<typename type>
		typename reverse_iterator<type>::reference reverse_iterator<type>::operator[](difference_type n) const
		{
			return(_base_it[-n -1]) ;
		}

	template <typename type>
		template <class Iter>
		bool reverse_iterator<type>::operator==(const reverse_iterator<Iter>& rhs) const
		{
			return (this->base() == rhs.base());
		}

	template <typename type>
		template<typename Iter>
		bool reverse_iterator<type>::operator!=(const reverse_iterator<Iter>& rhs) const
		{
			return (this->_base_it != rhs.base());
		}

	template <typename type>
		template<typename Iter>
		bool reverse_iterator<type>::operator<(const reverse_iterator<Iter>& rhs) const
		{
			return (this->_base_it > rhs.base());
		}

	template <typename type>
		template<typename Iter>
		bool reverse_iterator<type>::operator>(const reverse_iterator<Iter>& rhs) const
		{
			return (this->_base_it < rhs.base());
		}

	template <typename type>
		template<typename Iter>
		bool reverse_iterator<type>::operator<=(const reverse_iterator<Iter>& rhs) const
		{
			return (this->_base_it > rhs.base() || this->_base_it  == rhs.base());
		}

	template <typename type>
		template<typename Iter>
		bool reverse_iterator<type>::operator>=(const reverse_iterator<Iter>& rhs) const
		{
			return (this->_base_it < rhs.base() || this->_base_it  == rhs.base());
		}

	template<typename type>
		reverse_iterator<type> &reverse_iterator<type>::operator+=(int n) 
		{
			this->_base_it -= n;
			return(*this);
		}

	template<class r_iterator>
		reverse_iterator<r_iterator>  operator+(typename reverse_iterator<r_iterator>::difference_type n,
				const reverse_iterator<r_iterator> &it)
		{
			return (reverse_iterator<r_iterator>(it.base() - n));
		}

	template<typename type>
		reverse_iterator<type> &reverse_iterator<type>::operator-=(int n) 
		{
			this->_base_it += n;
			return(*this);
		}

	template<typename type>
		reverse_iterator<type> reverse_iterator<type>::operator++(int)
		{
			reverse_iterator tmp_r(*this);
			this->_base_it--;
			return (tmp_r);
		}

	template<typename type>
		reverse_iterator<type> &reverse_iterator<type>::operator++(void)
		{
			this->_base_it--;
			return (*this);
		}

	template<typename type>
		reverse_iterator<type> reverse_iterator<type>::operator--(int)
		{
			reverse_iterator tmp_r(*this);
			this->_base_it++;
			return (tmp_r);
		}

	template<typename type>
		reverse_iterator<type> & reverse_iterator<type>::operator--(void)
		{
			this->_base_it++;
			return (*this);
		}

	template<typename type>
		reverse_iterator<type>& reverse_iterator<type>::operator=(const reverse_iterator &it)
		{
			this->_base_it = it.base();
			return (*this);
		}

	template<typename type>
		typename reverse_iterator<type>::reference reverse_iterator<type>::operator*()
		{
			iterator_type it(this->_base_it);
			it--;
			return (*it);
		}

	template<typename type>
		typename reverse_iterator<type>::pointer reverse_iterator<type>::operator->()
		{
			return &(this->operator*());
		}

	template<typename type>
		reverse_iterator<type> reverse_iterator<type>::operator+(difference_type n) const
		{
			reverse_iterator	ret(this->_base_it - n);
			return (ret);
		}

	template<typename type>
		reverse_iterator<type> reverse_iterator<type>::operator-(difference_type n) const
		{
			reverse_iterator	ret(this->_base_it + n);
			return (ret);
		}
};

#endif /* REVERSE_ITERATOR_HPP */
