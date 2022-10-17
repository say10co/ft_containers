
template <class type, class Alloc>
template <class InputIterator>
void ft_vector<type, Alloc>::assign (InputIterator first, InputIterator last)
{
	size_type size = last - first;  
	std::cout << size << std::endl;
	ft_distroy(this->_m_data, this->_allocator, this->_size);

	if (size > this->_capacity)
	{
		(this->_allocator).deallocate(this->_m_data, this->_capacity);
		this->_m_data = (this->_allocator).allocate(size);
		this->_capacity = size;
	}
	this->_size = size;
	for (size_type i = 0; i < size ; i++)
	{
		(this->_allocator).construct(advance_by(this->_m_data, i *sizeof(value_type)), *first++);
	}
}
template<class type, class Alloc>
void ft_vector<type, Alloc>::push_back (const value_type& val)
{
		if (this->_size >= this->_capacity)	
		{
			size_type capacity = (this->_capacity) == 0 ? 1 : this->_capacity * 2 ;
			pointer new_ptr = (this->_allocator).allocate(capacity);
			int	i = 0;
			for (iterator it = this->begin(); it != this->end(); it++)
				(this->_allocator).construct(advance_by(new_ptr, i++ * sizeof(value_type)), *it);
			ft_distroy(this->_m_data, this->_allocator, this->_size);
			(this->_allocator).deallocate(this->_m_data, this->_capacity); // Old capacity  
			this->_m_data = new_ptr;
			this->_capacity = capacity;
		}
		(this->_allocator).construct(advance_by(this->_m_data, this->_size * sizeof(value_type)), val);
		this->_size += 1;
}
 
template<class type, class Alloc>
void ft_vector<type, Alloc>::pop_back()
{
	(this->_allocator).destroy(advance_by(this->_m_data, this->_size - 1));
	this->_size--;
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::insert (iterator position, const value_type& val)
{
	size_type distance = position - this->_m_data;
	this->insert(position, 1, val);
	return (iterator(this->_m_data + distance));
}

template<class type, class Alloc>
void ft_vector<type, Alloc>::insert (iterator position, size_type n, const value_type& val)
{
	iterator it;
	iterator tmp_it;
	bool inserted(false);

	if (this->_capacity < this->_size + n) // realocation 
	{
		size_type index = 0;
		it = this->begin();
		pointer  new_ptr = (this->_allocator).allocate(this->_size + n);	
		for (size_type i = 0; i <= this->_size ; i++)
		{
			if (it == position && !inserted)
			{
				inserted = true;
				for(size_type j = 0; j < n; j++)
					(this->_allocator).construct(advance_by(new_ptr, index++ * sizeof(value_type)), val);
			}
			else
				(this->_allocator).construct(advance_by(new_ptr, index++ * sizeof(value_type)), *it++);
		}
		ft_distroy(this->_m_data, this->_allocator, this->_size);
		(this->_allocator).deallocate(this->_m_data, this->_capacity);
		this->_m_data = new_ptr;
		this->_size += n;
		this->_capacity = this->_size;
		return ;
	}
	if (position == this->end())
	{
		for(size_type j = 0; j < n; j++)
			this->push_back(val);
		return ;
	}
	it = this->end() - 1;
	(this->_allocator).construct(advance_by(this->_m_data, this->_size * sizeof(value_type)), *it);
	tmp_it = it;
	while (it != position)
		*it-- = *--tmp_it;
	for(size_type j = 0; j < n; j++)
		*it-- = val;
	this->_size += n;
}

template<class type, class Alloc>
template <class InputIterator>
void ft_vector<type, Alloc>::insert (iterator position, InputIterator first, InputIterator last,
		typename  enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
{
	(void) position;
	(void) first;
	(void) last;
	(void) last;
	std::cout << "At write Place " << std::endl;	
}
