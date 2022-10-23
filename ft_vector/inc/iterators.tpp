#include "iterator_traits.hpp" 
namespace ft
{
	template<typename type>
	class iterator
	{
		public:
		/*
			typedef typename type::value_type value_type;
			typedef typename type::pointer pointer;
			typedef typename type::const_pointer const_pointer;
			typedef typename type::reference reference;
			typedef typename type::const_reference const_reference;
			*/
			typedef type value_type;
			typedef type* pointer;
			typedef const type* const_pointer;
			typedef type& reference;
			typedef const type& const_reference;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			typedef random_access_iterator_tag iterator_category;
		private:
			pointer _ptr;
	
			pointer advance_by(pointer ptr, size_type nb_bytes, bool decrease = false) const
			{
				const unsigned char *const_ptr = reinterpret_cast<const unsigned char *>(ptr);
				unsigned char *tmp_ptr = const_cast<unsigned char *>(const_ptr);
				if(decrease)
					tmp_ptr -= nb_bytes;
				else
					tmp_ptr += nb_bytes;
				return (reinterpret_cast<pointer>(tmp_ptr));
			}
	
		public:
			
			iterator();

			template<typename T>
			iterator(const T &it, typename ft::enable_if<!is_integral<T>::value, T>::type * = nullptr);
			iterator &operator=(const iterator &it);
			~iterator();
			iterator(pointer p);
	
			iterator operator++(int);
			iterator &operator++(void);
			iterator operator--(int);
			iterator &operator--(void);
	
			template<class t_iterator>
			friend iterator<t_iterator> operator+(int n, const iterator<t_iterator> &it);
	
			int operator-(const iterator &it) const;  // return pointer as an int for the moment 
			iterator operator-(int n) const;
			iterator operator+(int n) const;
	
			bool operator==(const iterator &it) const;
			bool operator!=(const iterator &it) const;
			bool operator<=(const iterator &it) const;
			bool operator>=(const iterator &it) const;
			bool operator>(const iterator &it) const;
			bool operator<(const iterator &it) const;
	
			iterator &operator+=(int n);
			iterator &operator-=(int n);
	
			reference operator*();
			pointer operator->();
	
			reference operator[](int n) const;
			pointer get_ptr() const
			{
				return (this->_ptr);
			}
	};
	
	template<typename type>
	iterator<type>::iterator()
		:_ptr(NULL)
	{
		//std::cout << "iterator Constuctor called " << std::endl;
	}
	
	template<typename type>
	int iterator<type>::operator-(const iterator &it) const
	{
		return (this->_ptr - it._ptr);
	}
	
	template<typename type>
	typename iterator<type>::reference iterator<type>::operator[](int n) const
	{
		return(* (this->_ptr + n)) ;
	}
	
	template<typename type>
	bool iterator<type>::operator==(const iterator &it) const
	{
		return (this->_ptr == it._ptr);
	}
	
	template<typename type>
	bool iterator<type>::operator!=(const iterator &it) const
	{
		return (this->_ptr != it._ptr);
	}
	
	template<typename type>
	bool iterator<type>::operator<(const iterator &it) const
	{
		return (this->_ptr < it._ptr);
	}
	
	template<typename type>
	bool iterator<type>::operator>(const iterator &it) const
	{
		return (this->_ptr > it._ptr);
	}
	
	template<typename type>
	bool iterator<type>::operator>=(const iterator &it) const
	{
		return (this->_ptr > it._ptr || this->_ptr == it._ptr);
	}
	
	template<typename type>
	bool iterator<type>::operator<=(const iterator &it) const
	{
	
		return (this->_ptr < it._ptr || this->_ptr == it._ptr);
	}
	
	template<typename type>
	iterator<type> &iterator<type>::operator+=(int n) 
	{
		this->_ptr = advance_by(this->_ptr, n *sizeof(value_type));
		return(*this);
	}

	template<typename t_iterator>  
	iterator<t_iterator> operator+(int n, const iterator<t_iterator> &it)
	{
		return (it + n);
	}
	
	template<typename type>
	iterator<type> &iterator<type>::operator-=(int n) 
	{
		this->_ptr = advance_by(this->_ptr, n *sizeof(value_type), true);
		return(*this);
	}
	
	template<typename type>
	iterator<type>::iterator(pointer p)
		:_ptr(p)
	{
	//	std::cout << "iterator Pointer Constuctor called " << std::endl;
	}
	template<typename type>
	template<typename T>
	iterator<type>::iterator(const T &it, typename ft::enable_if<!is_integral<T>::value, T>::type *)
	{
			this->_ptr = it.get_ptr();
			// *this->_ptr = it;
			//std::cout << "iterator Copy constructor called" << std::endl;
	}
	template<typename type>
	iterator<type>::~iterator()
	{
	//	std::cout << "iterator Distuctor called " << std::endl;
	}
	
	template<typename type>
	iterator<type> iterator<type>::operator++(int)
	{
		iterator tmp_r(*this);
		this->_ptr = advance_by(this->_ptr, sizeof(value_type));
		return (tmp_r);
	}
	
	template<typename type>
	iterator<type> &iterator<type>::operator++(void)
	{
		this->_ptr = advance_by(this->_ptr, sizeof(value_type));
		return (*this);
	}
	
	template<typename type>
	iterator<type> iterator<type>::operator--(int)
	{
		iterator tmp_r(*this);
		this->_ptr = advance_by(this->_ptr, sizeof(value_type), true);
		return (tmp_r);
	}
	
	template<typename type>
	iterator<type> & iterator<type>::operator--(void)
	{
		this->_ptr = advance_by(this->_ptr, sizeof(value_type), true);
		return (*this);
	}
	
	template<typename type>
	iterator<type> & iterator<type>::operator=(const iterator &it)
	{
			this->_ptr = it._ptr;
			//std::cout << "iterator Copy assignment operator called" << std::endl;
			return (*this);
	}
	
	template<typename type>
	typename iterator<type>::reference iterator<type>::operator*()
	{
		return (*(this->_ptr));
	}
	
	template<typename type>
	typename iterator<type>::pointer iterator<type>::operator->()
	{
		return (this->_ptr);
	}
	
	template<typename type>
	iterator<type> iterator<type>::operator+(int n) const
	{
		iterator	ret(advance_by(this->_ptr, n * sizeof(value_type)));
		return (ret);
	}
	
	template<typename type>
	iterator<type> iterator<type>::operator-(int n) const
	{
		iterator	ret(advance_by(this->_ptr, n * sizeof(value_type), true));
		return (ret);
	}
};
