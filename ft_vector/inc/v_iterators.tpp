template<class type, class Alloc>
class ft_vector<type, Alloc>::ft_vector_iterator
{
	typedef typename ft_vector<type, Alloc>::value_type value_type;
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

		template<class t_iterator>
		friend t_iterator operator+(int n, const t_iterator &it);

		int operator-(const iterator &it) const;  // return type as an int for the moment 
		iterator operator-(int n) const;
		iterator operator+(int n) const;

		bool operator==(const iterator &it) const;
		bool operator<=(const iterator &it) const;
		bool operator>=(const iterator &it) const;
		bool operator>(const iterator &it) const;
		bool operator<(const iterator &it) const;

		iterator &operator+=(int n);
		iterator &operator-=(int n);

		ft_vector_iterator(value_type *p);
		value_type &operator*();
		value_type *operator->();

		value_type &operator[](int n) const;
};

template<class t_iterator>
t_iterator operator+(int n, const t_iterator &it)
{
	typedef typename t_iterator::value_type value_type; 
	
	value_type *tmp_ptr = it._ptr;
	tmp_ptr += n * sizeof(value_type);
	t_iterator ret(tmp_ptr);
	return (ret);
}

template<class type, class Alloc>
ft_vector<type, Alloc>::ft_vector_iterator::ft_vector_iterator()
	:_ptr(NULL)
{
	std::cout << "Iterator Constuctor called " << std::endl;
}

template<class type, class Alloc>
int ft_vector<type, Alloc>::ft_vector_iterator::operator-(const iterator &it) const
{
	return (this->_ptr - it._ptr);
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::value_type &ft_vector<type, Alloc>::ft_vector_iterator::operator[](int n) const
{
	return(* (this->operator+(n) ));
}

template<class type, class Alloc>
bool ft_vector<type, Alloc>::ft_vector_iterator::operator==(const iterator &it) const
{
	return (this->_ptr == it._ptr);
}

template<class type, class Alloc>
bool ft_vector<type, Alloc>::ft_vector_iterator::operator<(const iterator &it) const
{
	return (this->_ptr < it._ptr);
}

template<class type, class Alloc>
bool ft_vector<type, Alloc>::ft_vector_iterator::operator>(const iterator &it) const
{
	return (this->_ptr > it._ptr);
}

template<class type, class Alloc>
bool ft_vector<type, Alloc>::ft_vector_iterator::operator>=(const iterator &it) const
{
	return (this->_ptr > it._ptr || this->_ptr == it._ptr);
}

template<class type, class Alloc>
bool ft_vector<type, Alloc>::ft_vector_iterator::operator<=(const iterator &it) const
{

	return (this->_ptr < it._ptr || this->_ptr == it._ptr);
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator &ft_vector<type, Alloc>::ft_vector_iterator::operator+=(int n) 
{
	this->_ptr += n * sizeof(value_type);
	return(*this);
}

template<class type, class Alloc>
typename ft_vector<type, Alloc>::iterator &ft_vector<type, Alloc>::ft_vector_iterator::operator-=(int n) 
{
	this->_ptr -= n * sizeof(value_type);
	return(*this);
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
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::ft_vector_iterator::operator+(int n) const
{
	value_type *tmp_ptr;
	tmp_ptr = this->_ptr;
	tmp_ptr += n * sizeof(value_type);
	iterator	ret(tmp_ptr);
	return (ret);
}

template <class type , class Alloc>
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::ft_vector_iterator::operator-(int n) const
{
std::cout << "operator - called !!!!!!!!!!!" << std::endl;
	value_type *tmp_ptr;
	tmp_ptr = this->_ptr;
	tmp_ptr -= n * sizeof(value_type);
	iterator	ret(tmp_ptr);
	return (ret);
}
