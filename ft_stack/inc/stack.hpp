#ifndef STACK_HPP
# define STACK_HPP 

#include "../../ft_vector/inc/vector.hpp"

namespace ft
{
	template <class Type, class Container = ft::vector<Type> >
		class stack
		{
			public:
				typedef  Container container_type;
				typedef  typename Container::value_type value_type;
				typedef  typename Container::size_type size_type;
				typedef  typename Container::reference reference;
				typedef  typename Container::const_reference const_reference;
	
			private:
				template <class T, class Cont>
				friend bool operator<(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs);
				template <class T, class Cont>
				friend bool operator==(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs);

			protected:
				container_type C;

			public:
				explicit stack(const container_type &ctnr = container_type()) : C(ctnr) {}
				bool empty() const { return C.empty(); }
				size_type size() const { return C.size(); }
				value_type& top() { return C.back() ;}
				const value_type& top() const { return C.back(); }
				void push (const value_type& val) { C.push_back(val); }
				void pop() {C.pop_back(); }


		};
	template <class T, class Cont>
		bool operator== (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs)
		{
			return (lhs.C == rhs.C); 
		}
	template <class T, class Cont>
		bool operator!= (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs)
		{
			return (!(lhs == rhs));
		}
	template <class T, class Cont>
		bool operator<  (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs)
		{
			return (lhs.C < rhs.C);
		}
	template <class T, class Cont>
		bool operator<= (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs)
		{
			return (!(rhs < lhs));
		}
	template <class T, class Cont>
		bool operator>  (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs)
		{
			return (rhs < lhs);
		}
	template <class T, class Cont>
		bool operator>= (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs)
		{
			return(!(lhs < rhs));
		}
};

#endif /* STACK_HPP */
