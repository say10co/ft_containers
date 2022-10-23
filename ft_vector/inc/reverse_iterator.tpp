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

			/*
			template<typename T>
			reverse_iterator(const T  &rev_it, typename ft::enable_if<!is_integral<T>::value, T>::type * = nullptr);
			*/


			reverse_iterator &operator=(const reverse_iterator &it);
			explicit reverse_iterator(iterator_type it);
			~reverse_iterator();
	
			reverse_iterator operator++(int);
			reverse_iterator &operator++(void);
			reverse_iterator operator--(int);
			reverse_iterator &operator--(void);
	
			template<class r_iterator>
			friend reverse_iterator<r_iterator> operator+(int n, const reverse_iterator<r_iterator> &it);
	
			//difference_type operator-(const reverse_iterator &it) const;

			template<typename Iter, typename Iter_O>
			friend difference_type operator-(const reverse_iterator<Iter> &it, const reverse_iterator<Iter_O> &it1);
			reverse_iterator operator-(difference_type n) const;
			reverse_iterator operator+(difference_type n) const;
			reverse_iterator &operator+=(int n);
			reverse_iterator &operator-=(int n);

			template <typename Iter>
			bool operator==(const reverse_iterator<Iter>& rhs);
			template <typename Iter>
			bool operator!=(const reverse_iterator<Iter>& rhs);
			template <typename Iter>
			bool operator>(const reverse_iterator<Iter>& rhs);
			template <typename Iter>
			bool operator<(const reverse_iterator<Iter>& rhs);
			template <typename Iter>
			bool operator>=(const reverse_iterator<Iter>& rhs);
			template <typename Iter>
			bool operator<=(const reverse_iterator<Iter>& rhs);
	
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
		//std::cout << "reverse_iterator Constuctor called " << std::endl;
	}

	template<typename type>
	 reverse_iterator<type>::reverse_iterator(iterator_type it)
		:_base_it(it)
	{
		//std::cout << "revers_iterator iterator constructor " << std::endl;
	}

	template<typename type>
	template<typename Iter>
	reverse_iterator<type>::reverse_iterator(const reverse_iterator<Iter>  &it)
	{
			this->_base_it = it.base();
			//std::cout << "reverse_iterator Copy constructor called" << std::endl;
			// *this->_base_it = it;
	}

	template<typename type>
	reverse_iterator<type>::~reverse_iterator()
	{
	//	std::cout << "reverse_iterator Distuctor called " << std::endl;
	}
	
//	template<typename type>
	template<typename Iter, typename Iter_O>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter> &it, const reverse_iterator<Iter_O> &it1) 
	{
		std::cout << "here" << std::endl;
		return (it1.base() - it.base());
		return (it.base() - it1.base());

	}
	
	template<typename type>
	typename reverse_iterator<type>::reference reverse_iterator<type>::operator[](difference_type n) const
	{
		return(_base_it[-n -1]) ;
	}

	//bool reverse_iterator<type>::operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator1>& rhs)
	template <typename type>
	template <class Iter>
	bool reverse_iterator<type>::operator==(const reverse_iterator<Iter>& rhs)
	{
		return (this->base() == rhs.base());
		//return (this->_base_it == rhs.base());
	}

	template <typename type>
	template<typename Iter>
	bool reverse_iterator<type>::operator!=(const reverse_iterator<Iter>& rhs)
	{
		return (this->_base_it != rhs.base());
	}
	
	template <typename type>
	template<typename Iter>
	bool reverse_iterator<type>::operator<(const reverse_iterator<Iter>& rhs)
	{
		return (this->_base_it > rhs.base());
	}
	
	template <typename type>
	template<typename Iter>
	bool reverse_iterator<type>::operator>(const reverse_iterator<Iter>& rhs)
	{
		return (this->_base_it < rhs.base());
	}
	
	template <typename type>
	template<typename Iter>
	bool reverse_iterator<type>::operator<=(const reverse_iterator<Iter>& rhs)
	{
		return (this->_base_it > rhs.base() || this->_base_it  == rhs.base());
	}
	
	template <typename type>
	template<typename Iter>
	bool reverse_iterator<type>::operator>=(const reverse_iterator<Iter>& rhs)
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
	reverse_iterator<r_iterator>  operator+(int n, const reverse_iterator<r_iterator> &it)
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
			//std::cout << "reverse_iterator Copy assignment operator called" << std::endl;
			this->_base_it = it.base();
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
	/*
	template<typename type>
	template<typename T>
	reverse_iterator<type>::reverse_iterator(const T &rev_it, typename ft::enable_if<!is_integral<T>::value, T>::type *)
	{
		std::cout << "saver template" << std::endl;
		(void) rev_it;
		//this->_base_it = rev_it.base();
	}
	*/
};
