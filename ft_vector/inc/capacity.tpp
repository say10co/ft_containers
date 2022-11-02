namespace ft
{
	template <class type, class Alloc >
	typename vector<type, Alloc>::size_type vector<type, Alloc>::size() const
	{
		return (this->_size);
	}
	
	template <class type, class Alloc >
	typename vector<type, Alloc>::size_type vector<type, Alloc>::capacity() const
	{
		return (this->_capacity);
	}

	template <class type, class Alloc >
	void vector<type, Alloc>::resize (size_type n, value_type val)
	{
		if (n < this->_size)	
			ft_distroy(this->_m_data + n, this->_allocator, this->_size - n);
		else if (n > this->_size)
		{
			if (n > this->_capacity)
			{
				pointer old_ptr = this->_m_data;
				this->_m_data = (this->_allocator).allocate(n);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(this->_m_data + i, *(old_ptr + i));
				//std::memmove(this->_m_data, old_ptr, this->_size * sizeof(value_type));
				ft_distroy(old_ptr, this->_allocator, this->_size);
				if (this->_capacity)
					this->_allocator.deallocate(old_ptr, this->_size);
				this->_capacity = n;
			}
			for (size_type i = this->_size ; i < n; i++)
				(this->_allocator).construct(this->_m_data + i, val);
		}
		this->_size = n;
	}

	template <class type, class Alloc>
	typename vector<type, Alloc>::size_type vector<type, Alloc>::max_size() const 
	{
		return (this->_allocator.max_size());
	}
	
	template <class type, class Alloc>
	bool vector<type, Alloc>::empty() const
	{
		return (this->_size == 0);
	}
	
	template <class type, class Alloc>
	void vector<type, Alloc>::reserve(size_type n)
	{
		if (n > this->max_size())
			throw std::length_error("N is out of reservation bound");
		if (n > this->_capacity)
		{	
			iterator old_it = this->begin();
			size_type old_size = this->_size;
			pointer new_ptr = (this->_allocator).allocate(n);	
			for (size_type i = 0; i < old_size; i++)
				(this->_allocator).construct(new_ptr + i, *old_it++);
			ft_distroy(this->_m_data, this->_allocator, old_size);
			if (this->_capacity)
				(this->_allocator).deallocate(this->_m_data, this->_capacity);
			this->_capacity = n;
			this->_m_data = new_ptr;
		}
	}
};

