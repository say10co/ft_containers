
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

			this->_m_data = ft_allocate(this->_allocator, n);
			tmp_ptr = _m_data;
			for (size_type i = 0; i < n; i++)
				(this->_allocator).construct(tmp_ptr++, val);
			//std::cout << "Fill constructor called :D" << std::endl;
		}

	template <class type, class Alloc>
		template <class InputIterator>
		void vector<type, Alloc>::range_construct(InputIterator first,  InputIterator last, std::input_iterator_tag)
		{
			for (;first != last; first++)
				this->push_back(*first);
			return ;
		}
	template <class type, class Alloc>
		template <class InputIterator>
		void vector<type, Alloc>::range_construct(InputIterator first,  InputIterator last, std::forward_iterator_tag)
		{
			size_type size;

			size = std::distance(first, last);

			this->_m_data = ft_allocate(this->_allocator, size);
			this->_capacity = size;
			this->_size = size;
			for (size_type i = 0; i < size; i++)
				(this->_allocator).construct(this->_m_data + i, *first++);
		}

	template <class type, class Alloc>
		template <class InputIterator>
		vector<type, Alloc>::vector(InputIterator first,  InputIterator last,const allocator_type &alloc,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type *)
		:_size(0), _capacity(0), _allocator(alloc)
		{
			typedef typename ft::iterator_traits<InputIterator>::iterator_category category;
			range_construct(first, last, category());
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
			const_iterator cit_end = obj.end();
			value_type *m_data;

			ft_distroy(this->_m_data, this->_allocator, this->_size);
			ft_deallocate(this->_m_data, this->_allocator, this->_capacity);

			this->_allocator  = obj._allocator; // new allocator 	
			this->_m_data = ft_allocate(this->_allocator, obj._capacity);
			this->_size = obj._size;
			this->_capacity = obj._capacity;
			m_data = this->_m_data;
			while (cit != cit_end)
				(this->_allocator).construct(m_data++, *cit++);
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

	template <class InputIterator1, class InputIterator2>
		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (first1!=last1) {
				if (!(*first1 == *first2)) 
					return false;
				++first1; ++first2;
			}
			return true;
		}
	template <class InputIterator1, class InputIterator2, class BinaryPredicate> 
		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
		{
			while (first1!=last1)
			{
				if (!pred(*first1, *first2)) 
					return false;
				++first1; ++first2;
			}
			return true;
		}

	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return false;
				if (*first1 < *first2)
					return true;
				first1++;
				first2++;
			}
			return (first2 != last2);
		}

	template <class InputIterator1, class InputIterator2, class Compare>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1))
					return false;
				if (comp(*first1,  *first2))
					return true;
				first1++;
				first2++;
			}
			return (first2 != last2);
		}


}
