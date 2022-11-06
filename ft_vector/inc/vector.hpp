#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP 

#include <memory>
#include <algorithm>

#include "enable_if.tpp"
#include "iterators.tpp"
#include "reverse_iterator.tpp"
namespace ft
{
	template <class type, class Alloc = std::allocator<type> >
	class vector
	{
		/* Public Typedefs: */
		public:
			typedef Alloc										allocator_type;
			typedef type										value_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference; 
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;  
			typedef typename allocator_type::size_type 			size_type;	// Usually size_t
			typedef ft::iterator<value_type, true> 				const_iterator;  
			typedef ft::iterator<value_type, false> 			iterator;  
			typedef ft::reverse_iterator<iterator>  			reverse_iterator; 
			typedef ft::reverse_iterator<const_iterator>  		const_reverse_iterator; 
			typedef ptrdiff_t 									difference_type; 
	
		private:
	
			value_type		*_m_data;
			size_type		_size;
			size_type 		_capacity;
			allocator_type	_allocator;

			void 		ft_distroy(value_type *p, allocator_type &alloc, size_type size);
			void 		ft_deallocate(value_type *p, allocator_type &alloc, size_type size);
			value_type* ft_allocate(allocator_type &alloc, size_type size);

			template <class InputIterator>
			void range_construct(InputIterator first, InputIterator last, std::input_iterator_tag);
			template <class InputIterator>
			void range_construct(InputIterator first, InputIterator last, std::forward_iterator_tag);
			template <class IteratorType>
			void assign_aux(IteratorType first, IteratorType last, std::input_iterator_tag);
			template <class IteratorType>
			void assign_aux(IteratorType first, IteratorType last, std::forward_iterator_tag);

			template <class InputIterator>
			void insert_aux(iterator position, InputIterator first, InputIterator  last, std::input_iterator_tag);
			template <class InputIterator>
			void insert_aux(iterator position, InputIterator first, InputIterator  last, std::forward_iterator_tag);
			void make_space(const size_type index, const size_type nb_elements);
		public:
	
			template <class  InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(), 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type * = nullptr);
	
			vector (const vector& x);
			explicit vector (const allocator_type& alloc = allocator_type());
			explicit vector (size_type n, const value_type &val = value_type(),
											 const allocator_type& alloc = allocator_type());
											 vector  &operator=(const  vector &obj);
			~vector();
	
			/* Iterators : */
			const_iterator			begin()  const;
			const_reverse_iterator  rbegin() const;
			const_iterator 			end() 	 const;	
			const_reverse_iterator  rend() 	 const;
			iterator 				begin();
			reverse_iterator 		rbegin();
			iterator 				end();
			reverse_iterator 		rend();

				
			/* Allocator : */	
			allocator_type get_allocator() const;	
	
			/* Capacity :  */	
			size_type	size()		const;	
			size_type	max_size()	const;
			size_type	capacity()	const;
			bool 		empty()		const;
			void 		reserve (size_type n);
			void 		resize (size_type n, value_type val = value_type());
			
				
			/* Accessors :  */	
			reference			operator[] (size_type n);
			reference 			at (size_type n);
			reference			front();
			reference			back();
			const_reference 	at (size_type n)			const;
			const_reference 	operator[] (size_type n)	const;
			const_reference 	front()						const;
			const_reference 	back() 						const;
			value_type* 		data() 						throw();
			const value_type* 	data() 						const throw();
				
			/* Modifiers : */ 
	
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type * = nullptr);
	
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type * = nullptr);
	
	
			void 		insert(iterator position, size_type n,  const value_type& val);
			void 		assign (size_type n, const value_type& val);
			void 		push_back (const value_type& val);
			void 		swap (vector& x);
			void 		pop_back();
			void 		clear();
			iterator 	insert (iterator position, const value_type& val);
			iterator 	erase (iterator first, iterator last);
			iterator 	erase (iterator position);
	
	};
};
	#include "modifiers.tpp"
	#include "constructors.tpp"
	#include "capacity.tpp"
	#include "accessors.tpp"	

#endif /* FT_VECTOR_HPP */
