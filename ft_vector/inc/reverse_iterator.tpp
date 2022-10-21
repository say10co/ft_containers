#include "iterator_traits.hpp" 
namespace ft
{
	template<typename Iterator>
	class reverse_iterator
	{

		public:
			typedef typename iterator_traites<Iterator>::value_type value_type;
			typedef typename iterator_traites<Iterator>::pointer pointer;
			typedef typename iterator_traites<Iterator>::reference reference;
			typedef typename iterator_traites<Iterator>::difference_type difference_type;
			typedef typename iterator_traites<Iterator>::iterator_category iterator_category;
			typedef Iterator iterator_type;
			typedef size_t size_type;

		private:
			iterator_type _base_it;
	
		public:
			reverse_iterator();
			template<typename Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it);
			reverse_iterator &operator=(const reverse_iterator &it);
			explicit reverse_iterator(iterator_type it);
			~reverse_iterator();
	
			reverse_iterator operator++(int);
			reverse_iterator &operator++(void);
			reverse_iterator operator--(int);
			reverse_iterator &operator--(void);
	
			template<class t_reverse_iterator>
			friend t_reverse_iterator operator+(int n, const t_reverse_iterator &it);
	
			int operator-(const reverse_iterator &it) const;  // return value as an int for the moment 
			reverse_iterator operator-(difference_type n) const;
			reverse_iterator operator+(difference_type n) const;
	
			bool operator==(const reverse_iterator &it) const;
			bool operator!=(const reverse_iterator &it) const;
			bool operator<=(const reverse_iterator &it) const;
			bool operator>=(const reverse_iterator &it) const;
			bool operator>(const reverse_iterator &it) const;
			bool operator<(const reverse_iterator &it) const;
	
			reverse_iterator &operator+=(int n);
			reverse_iterator &operator-=(int n);
	
			reference operator*();
			pointer operator->();
	
			reference operator[](difference_type n) const;
			iterator_type base() const
			{
				return (this->_base_it);
			}
	};
	
	template<typename type>
	reverse_iterator<type>::reverse_iterator()
		:_base_it()
	{
		std::cout << "reverse_iterator Constuctor called " << std::endl;
	}

	template<typename type>
	 reverse_iterator<type>::reverse_iterator(iterator_type it)
		:_base_it(it)
	{
		std::cout << "revers_iterator iterator constructor " << std::endl;
	}

	template<typename type>
	template<typename Iter>
	reverse_iterator<type>::reverse_iterator(const reverse_iterator<Iter>  &it)
	{
			this->_base_it = it.base();
			// *this->_base_it = it;
			//std::cout << "reverse_iterator Copy constructor called" << std::endl;
	}
	
	template<typename type>
	reverse_iterator<type>::~reverse_iterator()
	{
	//	std::cout << "reverse_iterator Distuctor called " << std::endl;
	}
	
	template<typename type>
	int reverse_iterator<type>::operator-(const reverse_iterator &it) const
	{
		return (this->_base_it - it.base());
	}
	
	template<typename type>
	typename reverse_iterator<type>::reference reverse_iterator<type>::operator[](difference_type n) const
	{
		return(_base_it[-n -1]) ;
	}

	template<typename type>
	bool reverse_iterator<type>::operator==(const reverse_iterator &it) const
	{
		return (this->_base_it == it.base());
	}

	template<typename type>
	bool reverse_iterator<type>::operator!=(const reverse_iterator &it) const
	{
		return (this->_base_it != it.base());
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator<(const reverse_iterator &it) const
	{
		return (this->_base_it < it._base());
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator>(const reverse_iterator &it) const
	{
		return (this->_base_it > it.base());
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator>=(const reverse_iterator &it) const
	{
		iterator_type base = it.base();
		return (this->_base_it > base() || this->_base_it == base());
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator<=(const reverse_iterator &it) const
	{
		iterator_type base = it.base();
		return (this->_base_it < base() || this->_base_it == base());
	}
	
	template<typename type>
	reverse_iterator<type> &reverse_iterator<type>::operator+=(int n) 
	{
		this->_base_it -= n;
		return(*this);
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
			//std::cout << "reverse_iterator Copy assignment operator called" << std::endl;
			return (*this);
	}
	
	template<typename type>
	typename reverse_iterator<type>::reference reverse_iterator<type>::operator*()
	{
		return (*(this->_base_it - 1));
	}
	
	template<typename type>
	typename reverse_iterator<type>::pointer reverse_iterator<type>::operator->()
	{
		return &(operator*());
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
