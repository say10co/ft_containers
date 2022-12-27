#ifndef ACCESSORS_HPP
#define ACCESSORS_HPP

namespace ft
{
	template <class type, class Alloc>
		typename vector<type, Alloc>::reference vector<type, Alloc>::operator[](size_type n)
		{	
			return (*(this->_m_data + n));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::const_reference vector<type, Alloc>::operator[](size_type n) const
		{	
			return (*(this->_m_data + n));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::reference vector<type, Alloc>::at(size_type n)
		{	
			if (n >= this->_size)
				throw (std::out_of_range("Index n out of range"));
			return (*(this->_m_data + n));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::const_reference vector<type, Alloc>::at(size_type n) const
		{	
			if (n >= this->_size)
				throw (std::out_of_range("Index n out of range"));
			return (*(this->_m_data + n));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::reference vector<type, Alloc>::front()
		{	
			return (*(this->_m_data));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::const_reference vector<type, Alloc>::front() const 
		{	
			return (*(this->_m_data));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::reference vector<type, Alloc>::back()
		{	
			return (*(this->_m_data + this->_size - 1));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::const_reference vector<type, Alloc>::back() const 
		{	
			return (*(this->_m_data + this->_size - 1));
		}

	template <class type, class Alloc>
		typename vector<type, Alloc>::value_type *vector<type, Alloc>::data() throw() 
		{	
			return (this->_m_data);
		}

	template <class type, class Alloc>
		const typename vector<type, Alloc>::value_type *vector<type, Alloc>::data() const throw()
		{	
			return (this->_m_data);
		}
};
#endif  /* ACCESSORS_HPP */
