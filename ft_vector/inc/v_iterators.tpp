template<class type, class Alloc>
class ft_vector<type, Alloc>::ft_vector_iterator
{
	private:
		value_type *_ptr;

	public:
		ft_vector_iterator();
		~ft_vector_iterator();
		ft_vector_iterator(value_type *p);
		iterator &operator=(const iterator &it);
		value_type &operator*();
};


template<class type, class Alloc>
ft_vector<type, Alloc>::ft_vector_iterator::ft_vector_iterator()
	:_ptr(NULL)
{
	std::cout << "Iterator Constuctor called " << std::endl;
}

template<class type, class Alloc>
ft_vector<type, Alloc>::ft_vector_iterator::ft_vector_iterator(value_type *p)
	:_ptr(p)
{
	std::cout << "Iterator Constuctor called " << std::endl;
}

template<class type, class Alloc>
ft_vector<type, Alloc>::ft_vector_iterator::~ft_vector_iterator()
{
	std::cout << "Iterator Distuctor called " << std::endl;
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::begin() 
{
	return (ft_vector_iterator(this->_m_data));
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator & ft_vector<type, Alloc>::ft_vector_iterator::operator=(const iterator &it)
{
		this->_ptr = it._ptr;
		std::cout << "Copy assignment operator called" << std::endl;
		return (*this);
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::value_type  & ft_vector<type, Alloc>::ft_vector_iterator::operator*()
{
	return (*(this->_ptr));
}

