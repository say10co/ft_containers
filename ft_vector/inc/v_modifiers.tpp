template <class type, typename Alloc>
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

		//std::cout << "*first++ : " << *first++ << std::endl;
		//std::cout << "size of value_type :" << sizeof(value_type) << std::endl;
		//std::cout << "size of value_type * i : " <<  i * sizeof(value_type) << std::endl;
		//std::cout  << "tmp : 		:	" << tmp << std::endl;
		//std::cout  << "this->_m_data : " << (byte_ptr + i * sizeof(value_type)) << std::endl;

		(this->_allocator).construct(advance_by(this->_m_data, i *sizeof(value_type)), *first++);
	}
}

