
namespace ft
{
	template <class type, class Alloc > 
	vector<type, Alloc>::vector(const allocator_type &alloc)
			:_m_data(NULL), _size(0), _capacity(0), _allocator(alloc)
	{}
	
	template <class type, class Alloc > 
	vector<type, Alloc>::vector(size_type n,  const value_type &val, const allocator_type &alloc)
			:_size(n), _capacity(n), _allocator(alloc)
	{
			value_type *tmp_ptr;
	
			//if (n)
			//	this->_m_data = (this->_allocator).allocate(n); // throws excpetion
			this->_m_data = ft_allocate(this->_allocator, n);
			tmp_ptr = _m_data;
			for (size_type i = 0; i < n; i++)
					(this->_allocator).construct(tmp_ptr++, val);
			//std::cout << "Fill constructor called :D" << std::endl;
	}
	
	template <class type, class Alloc>
	template <class InputIterator>
	vector<type, Alloc>::vector(InputIterator first,  InputIterator last,const allocator_type &alloc,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type *)
			:_size(0), _capacity(0), _allocator(alloc)
	{
			size_type size;

			if (std::is_same<typename ft::iterator_traits<InputIterator>::iterator_category, 
						typename std::input_iterator_tag>::value) 
			{
				for (;first != last; first++)
				this->push_back(*first);
				return ;
			}
			//size = last - first;
			size = 0;
			for (InputIterator tmp = first; tmp != last; tmp++, size++)
				;
			this->_m_data = ft_allocate(this->_allocator, size);
			this->_capacity = size;
			this->_size = size;
			for (size_type i = 0; i < size; i++)
					(this->_allocator).construct(this->_m_data + i, *first++);
			//std::cout << "vector Range Constructor Called :D" << std::endl;
	}
	
	template <class type, class Alloc >
	vector<type, Alloc>::vector(const vector<type, Alloc>& x)
			:_size(0), _capacity(0)
	{
			*this = x;
	}
	
	template <class type, class Alloc >
	vector<type, Alloc>& vector<type, Alloc>::operator=(const vector & obj)
	{

			const_iterator cit = obj.begin();
			ft_distroy(this->_m_data, this->_allocator, this->_size);

			ft_deallocate(this->_m_data, this->_allocator, this->_capacity);
			this->_allocator  = obj._allocator; // new allocator 	
			this->_m_data = ft_allocate(this->_allocator, obj._capacity);
			this->_size = obj._size;
			this->_capacity = obj._capacity;
			for (size_type i = 0; i < obj._size; i++)
				(this->_allocator).construct(this->_m_data + i, *cit++);
			return (*this);
	}
	
	template <class type, class Alloc >
	vector<type, Alloc>::~vector()
	{
			ft_distroy(this->_m_data, this->_allocator, this->_size);
			ft_deallocate(this->_m_data, this->_allocator, this->_capacity);
	}
	
	template <class type, class Alloc >
	void vector<type, Alloc>::ft_distroy(value_type *p, allocator_type &alloc, size_type size)
	{
			value_type *tmp_ptr = p;
	
			for (size_type i = 0; i < size; i++)
				alloc.destroy(tmp_ptr++);
	}
	
	template <class type, class Alloc >
	typename vector<type,  Alloc>::allocator_type vector<type,  Alloc>::get_allocator() const
	{	
			return (this->_allocator);
	}
	
	template <class type, class Alloc >
	typename vector<type, Alloc>::iterator vector<type, Alloc>::begin()
	{
			return (iterator(this->_m_data));
	}
	
	template <class type, class Alloc >
	typename vector<type, Alloc>::const_iterator vector<type, Alloc>::begin() const
	{
			return (iterator(this->_m_data));
	}

	template <class type, class Alloc >
	typename vector<type, Alloc>::reverse_iterator vector<type, Alloc>::rbegin()
	{
		return (reverse_iterator(this->_m_data + this->_size));
	}

	template <class type, class Alloc>
	typename vector<type, Alloc>::const_reverse_iterator vector<type, Alloc>::rbegin() const
	{
		return (reverse_iterator(this->_m_data + this->_size));
	}

	template <class type, class Alloc >
	typename vector<type, Alloc>::reverse_iterator vector<type, Alloc>::rend()
	{
		return (reverse_iterator(this->_m_data));
	}

	template <class type, class Alloc>
	typename vector<type, Alloc>::const_reverse_iterator vector<type, Alloc>::rend() const
	{
		return (reverse_iterator(this->_m_data));
	}



	template <class type, class Alloc >
	typename vector<type, Alloc>::iterator vector<type, Alloc>::end()
	{
			iterator tmp_it = this->_m_data;
	
			//if (this->_m_data != NULL)
					return (iterator(this->_m_data + this->_size));
			//return (tmp_it);
	}
	
	template <class type, class Alloc >
	typename vector<type, Alloc>::const_iterator vector<type, Alloc>::end() const
	{
			unsigned char *byte_ptr = reinterpret_cast<unsigned char *>(this->_m_data);
			byte_ptr += this->_size;
			if (this->_m_data == NULL)
					return (iterator(NULL));
			return (iterator(this->_m_data +this->_size));
	}

	template <class type, class Alloc >
	bool operator== (const vector<type,Alloc>& lhs, const vector<type,Alloc>& rhs)
	{
		typedef typename vector<type, Alloc>::size_type size_type;

		if (lhs.size() == rhs.size())
		{
			for (size_type i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return (false);
			}
			return (true);
		}
		return (false);

	}

	template <class type, class Alloc >
	bool operator>(const vector<type,Alloc>& lhs, const vector<type,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class type, class Alloc >
	bool operator!= (const vector<type,Alloc>& lhs, const vector<type,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class type, class Alloc >
	bool operator>= (const vector<type,Alloc>& lhs, const vector<type,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
	template <class type, class Alloc >
	bool operator<= (const vector<type,Alloc>& lhs, const vector<type,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class type, class Alloc >
	bool operator< (const vector<type,Alloc>& lhs, const vector<type,Alloc>& rhs)
	{
		typedef typename vector<type, Alloc>::size_type size_type;

		size_type min_size = std::min(lhs.size(), rhs.size());
		for (size_type i = 0; i < min_size; i++)
		{		
			if (lhs[i] > rhs[i])
				return (false);
			else if ( rhs[i] > lhs[i])
				return (true);
		}
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	}

	template<class type, class Alloc>
	void vector<type, Alloc>::ft_deallocate(value_type *p, allocator_type &alloc, size_type size)
	{
		if (size)
			alloc.deallocate(p, size);
	}

	template<class type, class Alloc>
	typename vector<type, Alloc>::value_type *vector<type, Alloc>::ft_allocate(allocator_type &alloc, size_type size)
	{
		if (size)
			return (alloc.allocate(size));
		return (NULL);
	}

}
