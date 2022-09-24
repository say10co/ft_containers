#include "../inc/ft_vector.hpp"

template <class type, class Alloc > 
ft_vector<type, Alloc>::ft_vector(const allocator_type &alloc)
{
		(void) alloc;
		std::cout << "Empty container constructor :D" << std::endl;
}

template <class type, class Alloc > 
ft_vector<type, Alloc>::ft_vector(size_type n,  const value_type &val, const allocator_type &alloc)
{
	(void) n;
	(void) val;
	(void) alloc;
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
	std::cout << "ft_vector Range Constructor Called :D" << std::endl;

}

