
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
