#include "../inc/ft_vector.hpp"

template <class type, class Alloc > 
ft_vector<type, Alloc>::ft_vector(const allocator_type &alloc)
	:_size(0), _capacity(0), allocator(allocator_type())
{
		(void) alloc;
		this->_m_data = this->allocator.allocate(0);
		std::cout << "Empty container constructor :D" << std::endl;
}

template <class type, class Alloc > 
ft_vector<type, Alloc>::ft_vector(size_type n,  const value_type &val, const allocator_type &alloc)
	:_size(n), _capacity(n), allocator(allocator_type())
{
	(void) alloc;

	this->_m_data = (this->allocator).allocate(n); // throws excpetion
	(this->allocator).construct(this->_m_data, val);
	std::cout << "Fill constructor called :D" << std::endl;
}


template <class type, class Alloc > //= std::allocator<type> > // For enclosing class temmplate
template <class InputIterator>							// for member template 
ft_vector<type, Alloc>::ft_vector(InputIterator first,  InputIterator last,
		const allocator_type &alloc)
{
	(void ) first;
	(void ) last;
	(void) alloc;
	//   [first,last) !!
	std::cout << "ft_vector Range Constructor Called :D" << std::endl;

}
template <class type, class Alloc >
ft_vector<type, Alloc>::ft_vector(const ft_vector<type, Alloc>& x)
{
	(void) x;
	std::cout << "Copy Constructor called" << std::endl;
}
template <class type, class Alloc >
typename ft_vector<type, Alloc>::size_type ft_vector<type, Alloc>::size() const
{
	return (this->_size);
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::size_type ft_vector<type, Alloc>::capacity() const
{
	return (this->_capacity);
}
/*
*/
