#include "iterator_traits.hpp" 

template<typename type>
class v_iterator
{
	private:
		typedef typename type::value_type value_type;
		typedef typename type::pointer pointer;
		typedef typename type::const_pointer const_pointer;
		typedef typename type::reference reference;
		typedef typename type::const_reference const_reference;
		pointer _ptr;


	public:
		
		v_iterator();
		template<typename T>
		v_iterator(const T &it);
		v_iterator &operator=(const v_iterator &it);
		~v_iterator();
		v_iterator(pointer p);

		v_iterator operator++(int);
		v_iterator &operator++(void);
		v_iterator operator--(int);
		v_iterator &operator--(void);

		template<class t_v_iterator>
		friend t_v_iterator operator+(int n, const t_v_iterator &it);

		int operator-(const v_iterator &it) const;  // return pointer as an int for the moment 
		v_iterator operator-(int n) const;
		v_iterator operator+(int n) const;

		bool operator==(const v_iterator &it) const;
		bool operator!=(const v_iterator &it) const;
		bool operator<=(const v_iterator &it) const;
		bool operator>=(const v_iterator &it) const;
		bool operator>(const v_iterator &it) const;
		bool operator<(const v_iterator &it) const;

		v_iterator &operator+=(int n);
		v_iterator &operator-=(int n);

		reference operator*();
		pointer operator->();

		reference operator[](int n) const;
		pointer get_ptr() const
		{
			return (this->_ptr);
		}
};

template<typename type>
v_iterator<type>::v_iterator()
	:_ptr(NULL)
{
	std::cout << "v_iterator Constuctor called " << std::endl;
}

template<typename type>
int v_iterator<type>::operator-(const v_iterator &it) const
{
	return (this->_ptr - it._ptr);
}

template<typename type>
typename v_iterator<type>::reference v_iterator<type>::operator[](int n) const
{
	return(* (this->_ptr + n)) ;
}

template<typename type>
bool v_iterator<type>::operator==(const v_iterator &it) const
{
	return (this->_ptr == it._ptr);
}

template<typename type>
bool v_iterator<type>::operator!=(const v_iterator &it) const
{
	return (this->_ptr != it._ptr);
}

template<typename type>
bool v_iterator<type>::operator<(const v_iterator &it) const
{
	return (this->_ptr < it._ptr);
}

template<typename type>
bool v_iterator<type>::operator>(const v_iterator &it) const
{
	return (this->_ptr > it._ptr);
}

template<typename type>
bool v_iterator<type>::operator>=(const v_iterator &it) const
{
	return (this->_ptr > it._ptr || this->_ptr == it._ptr);
}

template<typename type>
bool v_iterator<type>::operator<=(const v_iterator &it) const
{

	return (this->_ptr < it._ptr || this->_ptr == it._ptr);
}

template<typename type>
v_iterator<type> &v_iterator<type>::operator+=(int n) 
{
	this->_ptr += n * sizeof(value_type);
	return(*this);
}

template<typename type>
v_iterator<type> &v_iterator<type>::operator-=(int n) 
{
	this->_ptr -= n * sizeof(value_type);
	return(*this);
}

template<typename type>
v_iterator<type>::v_iterator(pointer p)
	:_ptr(p)
{
//	std::cout << "v_iterator Pointer Constuctor called " << std::endl;
}
template<typename type>
template<typename T>
v_iterator<type>::v_iterator(const T &it)
{
		this->_ptr = it.get_ptr();
		// *this = it;
		//std::cout << "v_iterator Copy constructor called" << std::endl;
}

template<typename type>
v_iterator<type>::~v_iterator()
{
//	std::cout << "v_iterator Distuctor called " << std::endl;
}

template<typename type>
v_iterator<type> v_iterator<type>::operator++(int)
{
	v_iterator tmp_r(*this);
	this->_ptr +=  sizeof(value_type);
	return (tmp_r);
}

template<typename type>
v_iterator<type> &v_iterator<type>::operator++(void)
{
	this->_ptr +=  sizeof(value_type);
	return (*this);
}

template<typename type>
v_iterator<type> v_iterator<type>::operator--(int)
{
	v_iterator tmp_r(*this);
	this->_ptr -=  sizeof(value_type);
	return (tmp_r);
}

template<typename type>
v_iterator<type> & v_iterator<type>::operator--(void)
{
	this->_ptr -=  sizeof(value_type);
	return (*this);
}

template<typename type>
v_iterator<type> & v_iterator<type>::operator=(const v_iterator &it)
{
		this->_ptr = it._ptr;
		//std::cout << "v_iterator Copy assignment operator called" << std::endl;
		return (*this);
}

template<typename type>
typename v_iterator<type>::reference v_iterator<type>::operator*()
{
	return (*(this->_ptr));
}

template<typename type>
typename v_iterator<type>::pointer v_iterator<type>::operator->()
{
	return (this->_ptr);
}

template<typename type>
v_iterator<type> v_iterator<type>::operator+(int n) const
{
	pointer tmp_ptr;
	tmp_ptr = this->_ptr;
	tmp_ptr += n * sizeof(value_type);
	v_iterator	ret(tmp_ptr);
	return (ret);
}

template<typename type>
v_iterator<type> v_iterator<type>::operator-(int n) const
{
	std::cout << "operator - called !!!!!!!!!!!" << std::endl;
	pointer tmp_ptr;
	tmp_ptr = this->_ptr;
	tmp_ptr -= n * sizeof(value_type);
	v_iterator	ret(tmp_ptr);
	return (ret);
}
