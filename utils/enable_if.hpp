#ifndef ENABLE_IF_HPP 
#define ENABLE_IF_HPP

namespace ft
{
	/*-------------Enable if -------------*/

	template <bool, typename T = void>
		struct enable_if
		{
		};

	template<typename T>
		struct enable_if<true, T>
		{
			typedef T type;
		};

	/*-------------Is integral -------------*/

	template <class T, T v>
		struct  integral_constant
		{
			static const T value = v;
			typedef T value_type;
			typedef integral_constant<T, v> type;
			operator T() { return v; }
		};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;


	template <typename T>
		struct is_integral : public false_type
	{
	};

	template <> struct is_integral<bool> 					: public true_type {};
	template <> struct is_integral<char> 					: public true_type {};
	template <> struct is_integral<wchar_t> 				: public true_type {};
	template <> struct is_integral<signed char> 			: public true_type {};
	template <> struct is_integral<short int> 				: public true_type {};
	template <> struct is_integral<int> 					: public true_type {};
	template <> struct is_integral<long int> 				: public true_type {};
	template <> struct is_integral<long long int> 			: public true_type {};
	template <> struct is_integral<unsigned char> 			: public true_type {};
	template <> struct is_integral<unsigned short int> 		: public true_type {};
	template <> struct is_integral<unsigned int> 			: public true_type {};
	template <> struct is_integral<unsigned long int> 		: public true_type {};
	template <> struct is_integral<unsigned long long int>  : public true_type {};

	template <typename T> struct is_integral<const T>				: public is_integral<T> {};
	template <typename T> struct is_integral<volatile T>			: public is_integral<T> {};
	template <typename T> struct is_integral<const volatile T>		: public is_integral<T> {};
};

#endif /*ENABLE_IF_HPP */ 
