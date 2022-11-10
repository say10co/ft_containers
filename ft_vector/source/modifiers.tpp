#include <iostream>	

namespace ft
{
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
		void vector<type, Alloc>::make_space(const size_type index, const size_type nb_elements)
		{
			const size_type vec_size = this->_size;
			pointer new_mdata;
			size_type new_cap; 

			if (!nb_elements)
				return ;
			if (this->_capacity - vec_size >= nb_elements)
			{
				for (long i = vec_size - 1; i >= (long)index; i--)
				{
					this->_allocator.construct(this->_m_data + nb_elements + i, *(this->_m_data + i));
					this->_allocator.destroy(this->_m_data + i);
				}
			}
			else // Reasllocation needed
			{
				new_cap = this->_capacity  * 2 > (vec_size + nb_elements) ?  this->_capacity  * 2 : (vec_size + nb_elements);
				new_mdata = ft_allocate(this->_allocator, new_cap);	

				for (size_type i = 0; i < index; i++)
				{
					this->_allocator.construct(new_mdata + i, *(this->_m_data + i));
					this->_allocator.destroy(this->_m_data + i);
				}
				for (size_type i = index; i < vec_size; i++)
				{
					this->_allocator.construct(new_mdata + i + nb_elements, *(this->_m_data + i));
					this->_allocator.destroy(this->_m_data + i);
				}
				ft_deallocate(this->_m_data, this->_allocator , this->_capacity);
				this->_m_data = new_mdata;
				this->_capacity = new_cap;
			}
		}

	template<class type, class Alloc>
		template <class InputIterator>
		void vector<type, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
		{
			pointer start = this->begin().get_ptr();
			pointer tmp_mdata = this->_m_data;
			pointer end =   this->end().get_ptr();
			pointer pos =   position.get_ptr();
			size_type cap = this->_capacity;

			this->_m_data = ft_allocate(this->_allocator , cap);
			this->_size = 0;

			for (; start != pos; start++)	
			{
				this->push_back(*start);
				this->_allocator.destroy(start);
			}
			for (;first != last; first++)
				this->push_back(*first);
			for (; start != end; start++)	
			{
				this->push_back(*start);
				this->_allocator.destroy(start);
			}
			ft_deallocate(tmp_mdata, this->_allocator, cap);
		}

	template<class type, class Alloc>
		template <class InputIterator>
		void vector<type, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag)
		{
			const size_type index = position.get_ptr() - this->_m_data;
			const size_type range_size = std::distance(first, last);
			this->make_space(index, range_size);
			for (size_type i = index; i < index + range_size ; i++)
				this->_allocator.construct(this->_m_data + i, *first++);
			this->_size += range_size;
		}

	template<class type, class Alloc>
		typename vector<type, Alloc>::iterator vector<type, Alloc>::insert (iterator position, const value_type& val)
		{
			const size_type distance = position.get_ptr() - this->_m_data;
			this->make_space(distance, 1);
			this->_allocator.construct(this->_m_data + distance, val);
			this->_size++;
			return (this->_m_data + distance);
		}

	template<class type, class Alloc>
		void vector<type, Alloc>::insert (iterator position, size_type n, const value_type& val)
		{
			const size_type index = position.get_ptr() - this->_m_data;
			this->make_space(index, n);
			for (size_type i = index; i < index + n; i++)
				this->_allocator.construct(this->_m_data + i, val);
			this->_size += n;
		}

	template<class type, class Alloc>
		template <class InputIterator>
		void vector<type, Alloc>::insert (iterator position, InputIterator first, InputIterator last,
				typename  enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
		{
			typedef typename ft::iterator_traits<InputIterator>::iterator_category iterator_category;
			insert_aux(position, first, last, iterator_category());
		}

	template <class type,class Alloc>
		typename vector<type, Alloc>::iterator vector<type, Alloc>::erase (iterator position)
		{
			return (this->erase(position, position+1));

			pointer start =  position.get_ptr();
			pointer end   = this->end().get_ptr();
			pointer tmp_start = start + 1;

			this->_allocator.destroy(start);
			this->_size -= 1;
			for (;tmp_start !=  end; start++, tmp_start++)
			{
				this->_allocator.construct(start, *(tmp_start));
				this->_allocator.destroy(tmp_start);
			}
			return (position);
		}

	template <class type,class Alloc>
		typename vector<type, Alloc>::iterator vector<type, Alloc>::erase (iterator first, iterator last)
		{
			pointer end = this->end().get_ptr();
			pointer  dest_ptr = first.get_ptr();
			pointer  last_ptr = last.get_ptr();
			size_type size= last_ptr - dest_ptr;

			if (first == last)
				return (first);
			while (dest_ptr < last_ptr)
				this->_allocator.destroy(dest_ptr++);
			dest_ptr = first.get_ptr();
			for (;last_ptr != end;) 
			{
				this->_allocator.construct(dest_ptr++, *last_ptr);
				this->_allocator.destroy(last_ptr++);
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
