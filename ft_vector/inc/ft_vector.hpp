#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP 

#include <memory>

template <class type, class Alloc = std::allocator<type> >
class ft_vector
{
	private:
		typedef type							value_type;
		typedef Alloc							allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_reference	const_reference; 
		typedef typename allocator_type::const_pointer	const_pointer;  
		//typedef ft_vector_iterator 				iterator; 
		//typedef (...) const_iterator
		//typedef (...) reverse_iterator 
		//typedef (...) const_reverse_iterator
		//typedef (...) diffrerence_type

		typedef typename allocator_type::size_type size_type;	// Usually size_t

		type		*_m_data;
		size_type	_size;
		size_type 	_capacity;
		allocator_type allocator;


	public:

		template <class  InputIterator>
		ft_vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

		explicit ft_vector (const allocator_type& alloc = allocator_type());
		explicit ft_vector (size_type n, const value_type &val = value_type(),const allocator_type& alloc = allocator_type());
		ft_vector (const ft_vector& x);


		size_type	size()		const;	
		size_type	max_size()	const;
		size_type	capacity()	const;
		bool 		empty()		const;
		void 		reserve (size_type n);
		void 		shrink_to_fit();
		void 		resize (size_type n, value_type val = value_type());
		
		class 		ft_vector_iterator;

		// Getters 

	protected:


};

#endif /* FT_VECTOR_HPP */
