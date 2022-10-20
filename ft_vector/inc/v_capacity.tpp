
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
				//(this->_allocator).construct(this->_m_data + (i * sizeof(value_type)), *old_it++);
				(this->_allocator).construct(this->_m_data + i, *old_it++);
			else
				//(this->_allocator).construct(this->_m_data + (i * sizeof(value_type)), val);
				(this->_allocator).construct(this->_m_data + i, val);
		}
		ft_distroy(old_ptr, this->_allocator, old_size);
		(this->_allocator).deallocate(old_ptr, old_cap);
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
		//pointer start = this->_m_data + (n * sizeof(value_type));
		pointer start = this->_m_data + n;
		ft_distroy(start, this->_allocator, (this->_size - n));
	}
	this->_size = n;
	this->_capacity = n;
}

template <class type, class Alloc>
typename ft_vector<type, Alloc>::size_type ft_vector<type, Alloc>::max_size() const 
{
	return (-1);
}

template <class type, class Alloc>
bool ft_vector<type, Alloc>::empty() const
{
	return (this->_size == 0);
}

template <class type, class Alloc>
void ft_vector<type, Alloc>::reserve(size_type n)
{
	if (n > this->max_size())
		throw std::length_error("N is out of reservation bound");
	if (n > this->_capacity)
	{	
		iterator old_it = this->begin();
		size_type old_size = this->_size;
		pointer new_ptr = (this->_allocator).allocate(n);	
		for (size_type i = 0; i < old_size; i++)
			(this->_allocator).construct(advance_by(new_ptr, i * sizeof(value_type)), *old_it++);
		ft_distroy(this->_m_data, this->_allocator, old_size);
		(this->_allocator).deallocate(this->_m_data, this->_capacity);
		this->_capacity = n;
		this->_m_data = new_ptr;
	}
}
/*
template <class type, class Alloc>
void ft_vector<type, Alloc>::shrink_to_fit()
{
	if (this->_capacity != this->_size)
	{
		iterator old_it = this->begin();
		size_type size = this->_size;
		pointer new_ptr = (this->_allocator).allocate(size);	
		for (size_type i = 0; i < size; i++)
			(this->_allocator).construct(advance_by(new_ptr, i * sizeof(value_type)), *old_it++);
		ft_distroy(this->_m_data, this->_allocator, size);
		(this->_allocator).deallocate(this->_m_data, this->_capacity);
		this->_capacity = size;
		this->_m_data = new_ptr;
	}
}
*/
