#include "iterator_traits.hpp" 
namespace ft
{
	template <class type, bool is_const>
	class iterator
	{
		public:
			typedef typename deduce<is_const, const type*, type*>::type pointer;
			typedef typename deduce<is_const, const type&, type&>::type reference;
			typedef ptrdiff_t											difference_type;
			typedef size_t 												size_type;
			typedef random_access_iterator_tag 							iterator_category;
			typedef type 												value_type;

		private:
			type * _ptr;

		public:
			template<typename T, bool is_const_type>
			iterator(const iterator<T, is_const_type>  &it);

			iterator &operator=(const iterator &it);
			iterator();
			~iterator();
			iterator(type *p);

			iterator operator++(int);
			iterator &operator++(void);
			iterator operator--(int);
			iterator &operator--(void);
			iterator operator-(int n) const;
			iterator operator+(int n) const;

			iterator &operator+=(int n);
			iterator &operator-=(int n);
			pointer get_ptr() const;

			reference operator*();
			pointer operator->();
			reference operator[](int n) const;
	
			template<typename T, bool is_const_type> bool operator==(const iterator<T, is_const_type> &it) const;
			template<typename T, bool is_const_type> bool operator!=(const iterator<T, is_const_type> &it) const;
			template<typename T, bool is_const_type> bool operator<=(const iterator<T, is_const_type> &it) const;
			template<typename T, bool is_const_type> bool operator>=(const iterator<T, is_const_type> &it) const;
			template<typename T, bool is_const_type> bool operator >(const iterator<T, is_const_type> &it) const;
			template<typename T, bool is_const_type> bool operator <(const iterator<T, is_const_type> &it) const;
			template<typename T, bool is_const_type> difference_type operator-(const iterator<T, is_const_type> &it) const;  

	};
	
	template <class type, bool is_const>
	typename iterator<type, is_const>::pointer iterator<type, is_const>::get_ptr() const
	{
		return (this->_ptr);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const>::iterator()
		:_ptr(NULL)
	{
		//std::cout << "iterator Constuctor called " << std::endl;
	}

	template<class type, bool is_const>
	iterator<type, is_const>::iterator(type * p)
		:_ptr(p)
	{
		//	std::cout << "iterator Pointer Constuctor called " << std::endl;
	}

	template<class type, bool is_const>
	iterator<type, is_const> & iterator<type, is_const>::operator=(const iterator &it)
	{
			//std::cout << "iterator Copy assignment operator called" << std::endl;
			this->_ptr = it._ptr;
			return (*this);
	}


	template<class type, bool is_const>
	iterator<type, is_const>::~iterator()
	{
		//	std::cout << "iterator Distuctor called " << std::endl;
	}
	
	template<class type, bool is_const>
	typename iterator<type, is_const>::reference iterator<type, is_const>::operator[](int n) const
	{
		return(* (this->_ptr + n)) ;
	}
		
	template<class type, bool is_const>
	iterator<type, is_const> &iterator<type, is_const>::operator+=(int n) 
	{
		this->_ptr += n;
		return(*this);
	}

	template<typename t_iterator, bool is_const_type>  
	iterator<t_iterator, is_const_type> operator+(typename iterator<t_iterator, is_const_type>::difference_type n,
			const iterator<t_iterator, is_const_type> &it)
	{
		return (it + n);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> &iterator<type, is_const>::operator-=(int n) 
	{
		this->_ptr -= n;
		return(*this);
	}
		
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator++(int)
	{
		iterator tmp_r(*this);
		this->_ptr++; 
		return (tmp_r);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> &iterator<type, is_const>::operator++(void)
	{
		this->_ptr++;
		return (*this);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator--(int)
	{
		iterator tmp_r(*this);
		this->_ptr--;
		return (tmp_r);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> & iterator<type, is_const>::operator--(void)
	{
		this->_ptr--;
		return (*this);
	}
	
	template<class type, bool is_const>
	typename iterator<type, is_const>::reference iterator<type, is_const>::operator*()
	{
		return (*(this->_ptr));
	}
	
	template<class type, bool is_const>
	typename iterator<type, is_const>::pointer iterator<type, is_const>::operator->()
	{
		return (this->_ptr);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator+(int n) const
	{
		iterator	ret(this->_ptr +  n);
		return (ret);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator-(int n) const
	{
		iterator	ret(this->_ptr -  n);
		return (ret);
	}

	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator==(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr == it.get_ptr());
	}

	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	typename iterator<type,is_const>::difference_type iterator<type, is_const>::operator-(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr - it.get_ptr());
	}

	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	iterator<type, is_const>::iterator(const iterator<T, is_const_type> &it)
		:_ptr(it.get_ptr())
	{
	}
	
	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator!=(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr != it.get_ptr());
	}
	
	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator<(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr < it.get_ptr());
	}
	
	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator>(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr > it.get_ptr());
	}
	
	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator>=(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr > it.get_ptr() || this->_ptr == it.get_ptr());
	}
	
	template<class type, bool is_const>
		template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator<=(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr < it.get_ptr() || this->_ptr == it.get_ptr());
	}

};
