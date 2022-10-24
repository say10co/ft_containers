#include "iterator_traits.hpp" 
namespace ft
{
	template <bool is_const, typename const_type, typename non_const_type>
	struct deduce;

	template <typename const_type, typename non_const_type>
	struct deduce<true, const_type, non_const_type>
	{
		typedef const_type type;
	};

	template <typename const_type, typename non_const_type>
	struct deduce<false, const_type, non_const_type>
	{
		typedef non_const_type type;
	};
	template <class type, bool is_const>
	class iterator
	{
		public:

			typedef type value_type;
			typedef typename deduce<is_const, const type*, type*>::type pointer;
			typedef typename deduce<is_const, const type&, type&>::type reference;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			typedef random_access_iterator_tag iterator_category;
		private:
			type * _ptr;

		public:
			
			iterator();

			template<typename T, bool is_const_type>
			iterator(const iterator<T, is_const_type>  &it);
			iterator &operator=(const iterator &it);
			~iterator();
			iterator(type *p);
	
			iterator operator++(int);
			iterator &operator++(void);
			iterator operator--(int);
			iterator &operator--(void);
	
			template<typename t_iterator, bool is_const_type_>
			friend iterator<t_iterator, is_const_type_> operator+(int n, const iterator<t_iterator, is_const_type_> &it);
	
			template<typename T, bool is_const_type>
			difference_type operator-(const iterator<T, is_const_type> &it) const;  // return pointer as an int for the moment 
			iterator operator-(int n) const;
			iterator operator+(int n) const;
	
			template<typename T, bool is_const_type>
			bool operator==(const iterator<T, is_const_type> &it) const;

			template<typename T, bool is_const_type>
			bool operator!=(const iterator<T, is_const_type> &it) const;

			template<typename T, bool is_const_type>
			bool operator<=(const iterator<T, is_const_type> &it) const;

			template<typename T, bool is_const_type>
			bool operator>=(const iterator<T, is_const_type> &it) const;

			template<typename T, bool is_const_type>
			bool operator>(const iterator<T, is_const_type> &it) const;

			template<typename T, bool is_const_type>
			bool operator<(const iterator<T, is_const_type> &it) const;
	
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

	template<class type, bool is_const>
	template<typename T, bool is_const_type>
	iterator<type, is_const>::iterator(const iterator<T, is_const_type> &it)
		:_ptr(it.get_ptr())
	{
	}
	
	template<class type, bool is_const>
	iterator<type, is_const>::iterator()
		:_ptr(NULL)
	{
		//std::cout << "iterator Constuctor called " << std::endl;
	}
	
	template<class type, bool is_const>
	template<typename T, bool is_const_type>
	typename iterator<type,is_const>::difference_type iterator<type, is_const>::operator-(const iterator<T, is_const_type> &it) const
	{
		//std::cout << "this->_ptr < it._ptr : "  << (this->_ptr < it._ptr) << std::endl;
		return (this->_ptr - it.get_ptr());
	}
	
	template<class type, bool is_const>
	typename iterator<type, is_const>::reference iterator<type, is_const>::operator[](int n) const
	{
		return(* (this->_ptr + n)) ;
	}
	
	template<class type, bool is_const>
	template<typename T, bool is_const_type>
	bool iterator<type, is_const>::operator==(const iterator<T, is_const_type> &it) const
	{
		return (this->_ptr == it.get_ptr());
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
	
	template<class type, bool is_const>
	iterator<type, is_const> &iterator<type, is_const>::operator+=(int n) 
	{
		this->_ptr += n; //advance_by(this->_ptr, n *sizeof(value_type));
		return(*this);
	}

	template<typename t_iterator, bool is_const_type_>  
	iterator<t_iterator, is_const_type_> operator+(int n, const iterator<t_iterator, is_const_type_> &it)
	{
		return (it + n);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> &iterator<type, is_const>::operator-=(int n) 
	{
		this->_ptr -= n; // advance_by(this->_ptr, n *sizeof(value_type), true);
		return(*this);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const>::iterator(type * p)
		:_ptr(p)
	{
	//	std::cout << "iterator Pointer Constuctor called " << std::endl;
	}


	template<class type, bool is_const>
	iterator<type, is_const>::~iterator()
	{
	//	std::cout << "iterator Distuctor called " << std::endl;
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator++(int)
	{
		iterator tmp_r(*this);
		this->_ptr++; // = advance_by(this->_ptr, sizeof(value_type));
		return (tmp_r);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> &iterator<type, is_const>::operator++(void)
	{
		this->_ptr++;// = advance_by(this->_ptr, sizeof(value_type));
		return (*this);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator--(int)
	{
		iterator tmp_r(*this);
		this->_ptr--;//= advance_by(this->_ptr, sizeof(value_type), true);
		return (tmp_r);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> & iterator<type, is_const>::operator--(void)
	{
		this->_ptr--;//= advance_by(this->_ptr, sizeof(value_type), true);
		return (*this);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> & iterator<type, is_const>::operator=(const iterator &it)
	{
			this->_ptr = it._ptr;
			//std::cout << "iterator Copy assignment operator called" << std::endl;
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
		//iterator	ret(advance_by(this->_ptr, n * sizeof(value_type)));
		iterator	ret(this->_ptr +  n);
		return (ret);
	}
	
	template<class type, bool is_const>
	iterator<type, is_const> iterator<type, is_const>::operator-(int n) const
	{
		//iterator	ret(advance_by(this->_ptr, n * sizeof(value_type), true));
		iterator	ret(this->_ptr -  n);
		return (ret);
	}
};
