
template <class type, class Alloc > 
ft_vector<type, Alloc>::ft_vector(const allocator_type &alloc)
	:_size(0), _capacity(0), _allocator(alloc)
{
		this->_m_data = this->_allocator.allocate(0);
		std::cout << "Empty container constructor :D" << std::endl;
}

template <class type, class Alloc > 
ft_vector<type, Alloc>::ft_vector(size_type n,  const value_type &val, const allocator_type &alloc)
	:_size(n), _capacity(n), _allocator(alloc)
{
	(void) alloc;
	value_type *tmp_ptr;

	this->_m_data = (this->_allocator).allocate(n); // throws excpetion
	tmp_ptr = _m_data;
	for (size_type i = 0; i < n; i++)
	{
		(this->_allocator).construct(tmp_ptr, val);
		tmp_ptr += sizeof(value_type);
	}
	//std::cout << "Fill constructor called :D" << std::endl;
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
	*this = x; // calling operator=()
	//std::cout << "Copy Constructor called" << std::endl;
}

template <class type, class Alloc >
ft_vector<type, Alloc>& ft_vector<type, Alloc>::operator=(const ft_vector & obj)
{
	value_type *tmp_ptr;
	value_type *tmp_ptr_obj;
	bool		construct(1);

	allocator_type old_allcoator= this->get_allocator();

	if (this->_size != obj._size) // reallocation  needed 
	{
		ft_delete(this->_m_data,  this->_allocator); //using original allocator 
		this->_m_data = old_allcoator.allocate(obj._size);	
		construct = 0;
	}
	tmp_ptr = this->_m_data;
	tmp_ptr_obj = obj._m_data;
	
	this->_allocator = obj._allocator;
	this->_size = obj._size;
	this->_capacity = obj._capacity;

	for (size_type i = 0; i < obj._size; i++)
	{
		if (!construct)
			*tmp_ptr = *tmp_ptr_obj;	
		else
			this->_allocator.construct(tmp_ptr, *tmp_ptr_obj);
		tmp_ptr += sizeof(value_type);
		tmp_ptr_obj += sizeof(value_type);
	}
	return (*this);
}

template <class type, class Alloc >
ft_vector<type, Alloc>::~ft_vector()
{
		ft_delete(this->_m_data, this->_allocator);	
}

template <class type, class Alloc >
void ft_vector<type, Alloc>::ft_delete(value_type *p, allocator_type alloc)
{
	value_type *tmp_ptr;
	
	tmp_ptr = p;
	for (size_type i = 0; i < this->_size; i++)
	{
		alloc.destroy(tmp_ptr);
		tmp_ptr += sizeof(value_type);
	}
	(alloc).deallocate(this->_m_data, this->_capacity);
}

template <class type, class Alloc >
typename ft_vector<type,  Alloc>::allocator_type ft_vector<type,  Alloc>::get_allocator() const
{	
	return (this->_allocator);
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::begin()
{
	std::cout << *(this->_m_data) << std::endl;
	return (iterator(this->_m_data));
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::const_iterator ft_vector<type, Alloc>::begin() const
{
	return (iterator(this->_m_data));
}
