template<class type, class Alloc>
class ft_vector<type, Alloc>::ft_vector_iterator
{
	private:
		value_type *_ptr;

	public:
		ft_vector_iterator();
		ft_vector_iterator(const iterator &it);
		iterator &operator=(const iterator &it);
		~ft_vector_iterator();

		iterator operator++(int);
		iterator &operator++(void);
		iterator operator--(int);
		iterator &operator--(void);

		template<class f_type, class f_Alloc>
		friend iterator operator+(int n, const iterator &it);
		iterator operator-(int n);
		iterator operator+(int n);

		ft_vector_iterator(value_type *p);
		value_type &operator*();
		value_type *operator->();
};

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator operator+(int n, const typename ft_vector<type, Alloc>::iterator &it)
{
	typedef typename ft_vector<type, Alloc>::value_type value_type; 
	typedef typename ft_vector<type, Alloc>::iterator iterator; 
	
	value_type *tmp_ptr = it._ptr;
	tmp_ptr += n * sizeof(value_type);
	iterator ret(tmp_ptr);
	return (ret);
}

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
ft_vector<type, Alloc>::ft_vector_iterator::ft_vector_iterator(const iterator &it)
{
		*this = it;
		//std::cout << "Iterator Copy constructor called" << std::endl;
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

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::ft_vector_iterator::operator++(int)
{
	iterator tmp_r(*this);
	this->_ptr +=  sizeof(value_type);
	return (tmp_r);
}

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator & ft_vector<type, Alloc>::ft_vector_iterator::operator++(void)
{

	this->_ptr +=  sizeof(value_type);
	return (*this);
}

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::ft_vector_iterator::operator--(int)
{
	iterator tmp_r(*this);
	this->_ptr -=  sizeof(value_type);
	return (tmp_r);
}

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator & ft_vector<type, Alloc>::ft_vector_iterator::operator--(void)
{
	this->_ptr -=  sizeof(value_type);
	return (*this);
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator & ft_vector<type, Alloc>::ft_vector_iterator::operator=(const iterator &it)
{
		this->_ptr = it._ptr;
		//std::cout << "Iterator Copy assignment operator called" << std::endl;
		return (*this);
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::value_type  & ft_vector<type, Alloc>::ft_vector_iterator::operator*()
{
	return (*(this->_ptr));
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::value_type  *ft_vector<type, Alloc>::ft_vector_iterator::operator->()
{
	return (this->_ptr);
}

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::ft_vector_iterator::operator+(int n)
{
	value_type *tmp_ptr;
	tmp_ptr = this->_ptr;
	tmp_ptr += n * sizeof(value_type);
	iterator	ret(tmp_ptr);
	return (ret);
}

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::ft_vector_iterator::operator-(int n)
{
	value_type *tmp_ptr;
	tmp_ptr = this->_ptr;
	tmp_ptr -= n * sizeof(value_type);
	iterator	ret(tmp_ptr);
	return (ret);
}
