#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP 

#include <memory>
#include "v_iterators1.tpp"

template <class type, class Alloc = std::allocator<type> >
class ft_vector
{
	// Public Typedefs:
	public:
		typedef type							value_type;
		typedef Alloc							allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_reference	const_reference; 
		typedef typename allocator_type::const_pointer	const_pointer;  
		typedef v_iterator<ft_vector<value_type> > iterator;  
		typedef v_iterator<ft_vector<const value_type> > const_iterator;  
		typedef ptrdiff_t diffrerence_type; 
		typedef typename allocator_type::size_type size_type;	// Usually size_t

		//typedef (...) reverse_iterator 
		//typedef (...) const_reverse_iterator

	private:

		value_type		*_m_data;
		size_type	_size;
		size_type 	_capacity;
		allocator_type _allocator;
		void ft_distroy(value_type *p, allocator_type &alloc, size_type size);


	public:

		template <class  InputIterator>
		ft_vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

		explicit ft_vector (const allocator_type& alloc = allocator_type());
		explicit ft_vector (size_type n, const value_type &val = value_type(),const allocator_type& alloc = allocator_type());
		ft_vector (const ft_vector& x);
		~ft_vector();
		ft_vector  &operator=(const  ft_vector &obj);

		// iterators 
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;	
		// Allocator 		
		allocator_type get_allocator() const;	
		// Capacity
		size_type	size()		const;	
		size_type	max_size()	const;
		size_type	capacity()	const;
		bool 		empty()		const;
		void 		reserve (size_type n);
		void 		shrink_to_fit();
		void 		resize (size_type n, value_type val = value_type());
		
			
		// accessors 
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
		reference at (size_type n);
		const_reference at (size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		value_type* data() throw();
		const value_type* data() const throw();

	protected:


};
	#include "v_constructors.tpp"
	#include "v_capacity.tpp"
	#include "v_accessors.tpp"
//	#include "v_iterators.tpp"
#endif /* FT_VECTOR_HPP */
