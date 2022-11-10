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
				explicit reverse_iterator(iterator_type it);
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
		}

	template<typename type>
		reverse_iterator<type>::~reverse_iterator()
		{
			//	std::cout << "reverse_iterator Distuctor called " << std::endl;
		}

	template<typename Iter, typename Iter1>
		typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter> &it, 
				const reverse_iterator<Iter1> &it1) 
		{
			return (it1.base() - it.base());
			//The function returns the same as subtracting lhs's base iterator from rhs's base iterator. 
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
};
