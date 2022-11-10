#include <iostream>
template <bool is_const,typename const_type, typename non_const_type>
struct choose;

template <typename const_type, typename non_const_type>
struct choose<true, const_type, non_const_type>
{
		typedef const_type type;
};

template <typename const_type, typename non_const_type>
struct choose<false, const_type, non_const_type>
{
		typedef non_const_type type;
};

template <typename type>
class iterator
{
	private:
		type *ptr;


	public:
		iterator (type *p): ptr(p) {};
		
		template <typename T>
		iterator(const iterator<T> &it)
		{	
			this->ptr = it.get_ptr();
		}

		type *get_ptr() const
		{
			return this->ptr;
		}
	
	template<typename T>
	bool operator==(const iterator<T> &it)
	{
		return (this->ptr == it.get_ptr());
	}
};

int main()
{
	int a = 42;
	char aa;

	iterator<int> it(&a);
	iterator<int> it1(&a);
	iterator<const int> cit(it);
	std::cout << (cit == it) << std::endl;	
}
