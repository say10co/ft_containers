#include <iostream>	

namespace ft
{
	template <class type, class Alloc>
	void vector<type, Alloc>::assign (size_type n, const value_type& val)
	{
		size_type size = n;

		ft_distroy(this->_m_data, this->_allocator, this->_size);
		if (size > this->_capacity)
		{
			ft_deallocate(this->_m_data, this->_allocator, this->_capacity);
			this->_m_data = ft_allocate (this->_allocator, size);
			this->_capacity = size;
		}
		for (size_type i = 0; i < size; i++)
			(this->_allocator).construct(this->_m_data + i, val);
		this->_size = size;
	}
	
	template <class type, class Alloc>
	template <class IteratorType>
	void vector<type, Alloc>::assign_aux(IteratorType first, IteratorType last, std::input_iterator_tag)
	{
		for (;first != last; first++)
			this->push_back(*first);
		return ;
	}

	template <class type, class Alloc>
	template <class IteratorType>
	void vector<type, Alloc>::assign_aux(IteratorType first, IteratorType last, std::forward_iterator_tag)
	{
		size_type	size;
		value_type *m_data;
		
		size = std::distance(first, last);
		if (size > this->_capacity)
		{
			ft_deallocate(this->_m_data, this->_allocator, this->_capacity);
			this->_m_data = ft_allocate(this->_allocator, size);
			this->_capacity = size;
		}
		this->_size = size;
		m_data = this->_m_data;
		while (first < last)
			(this->_allocator).construct(m_data++, *first++);
	}

	template <class type, class Alloc>
	template <class InputIterator>
	void vector<type, Alloc>::assign (InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type *)
	{
		typedef typename ft::iterator_traits<InputIterator>::iterator_category iterator_category;

		ft_distroy(this->_m_data, this->_allocator, this->_size);
		assign_aux(first, last, iterator_category());

	}
	
	template<class type, class Alloc>
	void vector<type, Alloc>::push_back (const value_type& val)
	{
			size_type capacity;
			size_type size;
			pointer new_ptr;
	
			if (this->_size == this->_capacity)	
			{
				capacity = (this->_capacity) == 0 ? 1 : this->_capacity * 2 ;
				new_ptr = (this->_allocator).allocate(capacity);
				size = this->_size;
				for (size_type i = 0; i < size; i++)
					(this->_allocator).construct(new_ptr + i, *(this->_m_data + i));
				ft_distroy(this->_m_data, this->_allocator, size);
				ft_deallocate(this->_m_data, this->_allocator, this->_capacity);
				this->_m_data = new_ptr;
				this->_capacity = capacity;
			}
			this->_allocator.construct(this->_m_data + this->_size, val);
			this->_size += 1;
	}
	 
	template<class type, class Alloc>
	void vector<type, Alloc>::pop_back()
	{
		(this->_allocator).destroy(this->_m_data + this->_size - 1);
		this->_size--;
	}
	
	template<class type, class Alloc>
	typename vector<type, Alloc>::iterator vector<type, Alloc>::insert (iterator position, const value_type& val)
	{
		size_type distance = position.get_ptr() - this->_m_data;
		this->insert(position, 1, val);
		return (iterator(this->_m_data + distance));
	}
	
	template<class type, class Alloc>
	void vector<type, Alloc>::insert (iterator position, size_type n, const value_type& val)
	{
		vector tmp(n, val);
		this->insert(position, tmp.begin(), tmp.end());
	}
	template<class type, class Alloc>
	template <class InputIterator>
	void vector<type, Alloc>::insert (iterator position, InputIterator first, InputIterator last,
			typename  enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
	{
		pointer new_ptr;
		vector new_elements(first, last);	
		size_type nb_elements = new_elements.size();
		size_type total_size  = this->_size + nb_elements;
		size_type index = 0;
		size_type new_cap = this->_capacity  * 2 > total_size ?  this->_capacity  * 2 : total_size;
	
		iterator it = this->begin();
		iterator ite = this->end();

		//if (this->_size + nb_elements > this->_capacity) // reallocation needed 
		if (total_size > this->_capacity) // reallocation needed 
		{
			if (total_size)
				//new_ptr = (this->_allocator).allocate(total_size);
				new_ptr = (this->_allocator).allocate(new_cap);

			for (;it != position; it++, index++) 
				(this->_allocator).construct(new_ptr + index, *it);

			for (iterator tmp = new_elements.begin(); tmp != new_elements.end(); tmp++, index++)
				(this->_allocator).construct(new_ptr + index, *tmp);

			for (;it != ite; it++, index++)
				(this->_allocator).construct(new_ptr + index, *it);

			ft_distroy(this->_m_data, this->_allocator, this->_size);

			if (this->_capacity)
				this->_allocator.deallocate(this->_m_data, this->_capacity);
				//this->_allocator.deallocate(this->_m_data, this->_size);

			this->_m_data = new_ptr;
			//this->_capacity = total_size;
			this->_capacity = new_cap;
		}
		else
		{
			vector copy(position, this->end());
			iterator start = position;

			for(iterator i = new_elements.begin(); i != new_elements.end(); i++)
			{
				if (start < this->end())
					(this->_allocator).destroy(start.get_ptr());
				(this->_allocator).construct(start.get_ptr(), *i);
				start++;
			}
			for (iterator it = copy.begin(); it != copy.end(); it++)	
			{
				if (start < this->end())
					(this->_allocator).destroy(start.get_ptr());
				(this->_allocator).construct(start.get_ptr(), *it);
				start++;
			}
		}
		this->_size += nb_elements;
	}
	
	template <class type,class Alloc>
	typename vector<type, Alloc>::iterator vector<type, Alloc>::erase (iterator position)
	{
		return (this->erase(position, position + 1));
	}

	template <class type,class Alloc>
	typename vector<type, Alloc>::iterator vector<type, Alloc>::erase (iterator first, iterator last)
	{
		iterator end = this->end();
		pointer  dest_ptr = first.get_ptr();
		pointer  last_ptr = last.get_ptr();
		size_type size= last_ptr - dest_ptr;

		if (first == last)
			return (first);
		while (dest_ptr < last_ptr)
				this->_allocator.destroy(dest_ptr++);

		dest_ptr = first.get_ptr();
		for (iterator it = last ;it < end; it++, dest_ptr++)	
		{
			this->_allocator.construct(dest_ptr, *it);
			this->_allocator.destroy(it.get_ptr());
		}
		this->_size -= size;
		return (first);
	}

	template <class type, class Alloc>
	void vector<type, Alloc>::swap(vector<type, Alloc> &x)
	{
		std::swap(this->_allocator, x._allocator);
		std::swap(this->_m_data, x._m_data);
		std::swap(this->_size, x._size);
		std::swap(this->_capacity, x._capacity);
		//
		//Exception safety 
		//https://cplusplus.com/reference/vector/vector/swap/
	}

	template <class type, class Alloc>
	void vector<type, Alloc>::clear()
	{
		ft_distroy(this->_m_data, this->_allocator, this->_size);
		this->_size =  0;
	}

	template <class type, class Alloc>
	void swap (vector<type, Alloc>& x, vector<type, Alloc>& y)
	{	
		x.swap(y);
	}
}
