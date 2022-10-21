#include "reverse_iterator_traits.hpp" 
namespace ft
{
	template<typename Iterator>
	class reverse_iterator
	{
		public:
			typedef iterator_traits<Iterator>::value_type value_type;
			typedef iterator_traits<Iterator>::pointer pointer;
			typedef iterator_traits<Iterator>::reference reference;
			typedef iterator_traits<Iterator>::difference_type difference_type;
			typedef iterator_traits<Iterator>::iterator_category iterator_category;
			typedef Iterator iterator_type;
			typedef size_t size_type;
		private:
			pointer _base_it;
	
			pointer advance_by(pointer ptr, size_type nb_bytes, bool decrease = false) const
			{
				const unsigned char *const_base_it = reinterpret_cast<const unsigned char *>(ptr);
				unsigned char *tmp_base_it = const_cast<unsigned char *>(const_base_it);
				if(decrease)
					tmp_base_it -= nb_bytes;
				else
					tmp_base_it += nb_bytes;
				return (reinterpret_cast<pointer>(tmp_base_it));
			}
	
		public:
			
			reverse_iterator();
			template<typename T>
			reverse_iterator(const T &it);
			reverse_iterator &operator=(const reverse_iterator &it);
			~reverse_iterator();
			reverse_iterator(pointer p);
	
			reverse_iterator operator++(int);
			reverse_iterator &operator++(void);
			reverse_iterator operator--(int);
			reverse_iterator &operator--(void);
	
			template<class t_reverse_iterator>
			friend t_reverse_iterator operator+(int n, const t_reverse_iterator &it);
	
			int operator-(const reverse_iterator &it) const;  // return pointer as an int for the moment 
			reverse_iterator operator-(int n) const;
			reverse_iterator operator+(int n) const;
	
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
	
			reference operator[](int n) const;
			pointer get_base_it() const
			{
				return (this->_base_it);
			}
	};
	
	template<typename type>
	reverse_iterator<type>::reverse_iterator()
		:_base_it(NULL)
	{
		std::cout << "reverse_iterator Constuctor called " << std::endl;
	}
	
	template<typename type>
	int reverse_iterator<type>::operator-(const reverse_iterator &it) const
	{
		return (this->_base_it - it._base_it);
	}
	
	template<typename type>
	typename reverse_iterator<type>::reference reverse_iterator<type>::operator[](int n) const
	{
		return(* (this->_base_it + n)) ;
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator==(const reverse_iterator &it) const
	{
		return (this->_base_it == it._base_it);
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator!=(const reverse_iterator &it) const
	{
		return (this->_base_it != it._base_it);
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator<(const reverse_iterator &it) const
	{
		return (this->_base_it < it._base_it);
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator>(const reverse_iterator &it) const
	{
		return (this->_base_it > it._base_it);
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator>=(const reverse_iterator &it) const
	{
		return (this->_base_it > it._base_it || this->_base_it == it._base_it);
	}
	
	template<typename type>
	bool reverse_iterator<type>::operator<=(const reverse_iterator &it) const
	{
	
		return (this->_base_it < it._base_it || this->_base_it == it._base_it);
	}
	
	template<typename type>
	reverse_iterator<type> &reverse_iterator<type>::operator+=(int n) 
	{
		this->_base_it = advance_by(this->_base_it, n *sizeof(value_type));
		return(*this);
	}
	
	template<typename type>
	reverse_iterator<type> &reverse_iterator<type>::operator-=(int n) 
	{
		this->_base_it = advance_by(this->_base_it, n *sizeof(value_type), true);
		return(*this);
	}
	
	template<typename type>
	reverse_iterator<type>::reverse_iterator(pointer p)
		:_base_it(p)
	{
	//	std::cout << "reverse_iterator Pointer Constuctor called " << std::endl;
	}
	template<typename type>
	template<typename T>
	reverse_iterator<type>::reverse_iterator(const T &it)
	{
			this->_base_it = it.get_base_it();
			// *this->_base_it = it;
			//std::cout << "reverse_iterator Copy constructor called" << std::endl;
	}
	
	template<typename type>
	reverse_iterator<type>::~reverse_iterator()
	{
	//	std::cout << "reverse_iterator Distuctor called " << std::endl;
	}
	
	template<typename type>
	reverse_iterator<type> reverse_iterator<type>::operator++(int)
	{
		reverse_iterator tmp_r(*this);
		this->_base_it = advance_by(this->_base_it, sizeof(value_type));
		return (tmp_r);
	}
	
	template<typename type>
	reverse_iterator<type> &reverse_iterator<type>::operator++(void)
	{
		this->_base_it = advance_by(this->_base_it, sizeof(value_type));
		return (*this);
	}
	
	template<typename type>
	reverse_iterator<type> reverse_iterator<type>::operator--(int)
	{
		reverse_iterator tmp_r(*this);
		this->_base_it = advance_by(this->_base_it, sizeof(value_type), true);
		return (tmp_r);
	}
	
	template<typename type>
	reverse_iterator<type> & reverse_iterator<type>::operator--(void)
	{
		this->_base_it = advance_by(this->_base_it, sizeof(value_type), true);
		return (*this);
	}
	
	template<typename type>
	reverse_iterator<type> & reverse_iterator<type>::operator=(const reverse_iterator &it)
	{
			this->_base_it = it._base_it;
			//std::cout << "reverse_iterator Copy assignment operator called" << std::endl;
			return (*this);
	}
	
	template<typename type>
	typename reverse_iterator<type>::reference reverse_iterator<type>::operator*()
	{
		return (*(this->_base_it));
	}
	
	template<typename type>
	typename reverse_iterator<type>::pointer reverse_iterator<type>::operator->()
	{
		return (this->_base_it);
	}
	
	template<typename type>
	reverse_iterator<type> reverse_iterator<type>::operator+(int n) const
	{
		reverse_iterator	ret(advance_by(this->_base_it, n * sizeof(value_type)));
		return (ret);
	}
	
	template<typename type>
	reverse_iterator<type> reverse_iterator<type>::operator-(int n) const
	{
		reverse_iterator	ret(advance_by(this->_base_it, n * sizeof(value_type), true));
		return (ret);
	}
};
