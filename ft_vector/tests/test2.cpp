#include <iostream>
#include <utility>
template < class F, class S >
    struct pair
    {
        public :
            F first;
            S second;

        public :
            pair() : first(), second() {} // Default constructor
            pair ( const F &a, const S &b ) // Parameterized constructor
            {
                first = a;
                second = b;
            }
            template < class T1, class T2 >
            pair ( const pair < T1, T2 > &rhs ) // Copy constructor 
            {
				std::cout << "Hello from copy constructor" << std::endl;
				//this->operator=<T1, T2>(rhs);
				first = rhs.first;
				second = rhs.second;
            }
            //template < class T1, class T2 >
            pair &operator=( const pair<F, S> &rhs ) // Copy assignment operator overload
            {
				std::cout << "Hello from operator constructor" << std::endl;
                if (this != &rhs)
                {
                    first = rhs.first;
                    second = rhs.second;
                }
                return *this;
            }
            ~pair() {} // Destructor
    };


template < class T1, class T2 >
pair< T1, T2 > make_pair( T1 a, T2 b )
{
	return pair< T1, T2 >(a, b);
}
class test
{
	public :
		int n;
		test() {}
		test(int nb) {n = nb;}
		test(const test &rhs) {}
		~test() {}
};

/*void test(std::string const &s)
{
	std::cout << s << std::endl;
}*/
int main( void )
{
	//test("hello");
//	std::pair<std::string, int> m_pair1("bob", 10);

	pair<std::string, int> m_pair2(make_pair("hello", 100));

//	m_pair2 = m_pair1;
	
//	std::pair<std::string, int> m_pair(std::pair<std::string, float>("hello", 100.0f));
//	pair<std::string, int> m_pair(pair<std::string, float>("hello", 100.0f));
//	std::cout << m_pair.first << " " << m_pair.second << std::endl;
//	pair<std::string, unsigned int> 
	//pair<std::string,  unsigned int> m_pair1("hello1", 20);
	//::pair<std::string, int> m_pair(m_pair1);
	//std::pair<std::string, unsigned int> m_pair(std::pair<std::string, int>);
	return 0;
}
