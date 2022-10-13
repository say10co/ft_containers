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
		ft_delete(this->_m_data,  this->_allocator,  this->_size, this->_capacity);
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
		ft_delete(this->_m_data, this->_allocator, this->_size, this->_capacity);	
}

template <class type, class Alloc >
void ft_vector<type, Alloc>::ft_delete(value_type *p, allocator_type &alloc, size_type size, size_type cap )
{
	value_type *tmp_ptr;
	
	tmp_ptr = p;
	for (size_type i = 0; i < size; i++)
	{
		alloc.destroy(tmp_ptr);
		tmp_ptr += sizeof(value_type);
	}
	(alloc).deallocate(p, cap);
}

template <class type, class Alloc >
typename ft_vector<type,  Alloc>::allocator_type ft_vector<type,  Alloc>::get_allocator() const
{	
	return (this->_allocator);
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::begin()
{
	return (iterator(this->_m_data));
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::const_iterator ft_vector<type, Alloc>::begin() const
{
	return (iterator(this->_m_data));
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::end()
{
	iterator tmp_it = this->_m_data;

	if (this->_m_data != NULL)
		tmp_it = iterator(this->_m_data + this->_size);
	return (tmp_it);
}

template <class type, class Alloc >
typename ft_vector<type, Alloc>::const_iterator ft_vector<type, Alloc>::end() const
{
	if (this->_m_data == NULL)
		return (iterator(NULL));
	return (iterator(this->_m_data + this->_size));
}

template <class type, class Alloc >
void ft_vector<type, Alloc>::resize (size_type n, value_type val)
{
		
	if (this->_capacity < n)
	{
		size_type old_size = this->_size;
		size_type old_cap = this->_capacity;
		pointer old_ptr = this->_m_data;
		iterator old_it(this->_m_data);
		this->_m_data = (this->_allocator).allocate(n);

		for (size_type i = 0; i < n; i++)
		{
			if (i < old_size)
				(this->_allocator).construct(this->_m_data + (i * sizeof(value_type)), *old_it++);
			else
				(this->_allocator).construct(this->_m_data + (i * sizeof(value_type)), val);
		}
		ft_delete(old_ptr, this->_allocator, old_size, old_cap);
	}
	else if (this->_size < n)
	{
		pointer start = this->_m_data + this->_size;
		for (size_type i = n; i < n; i++)
		{
			(this->_allocator).construct(start, val);
			start += sizeof(value_type);
		}
	}
	else if (this->_size > n) 
	{
		pointer start = this->_m_data + (n * sizeof(value_type));
		ft_delete(start, this->_allocator, (this->_size - n), (this->_size - j));
	}
	this->_size = n;
	this->_capacity = n;
}
