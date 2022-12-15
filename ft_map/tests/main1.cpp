#include <iostream>
#include "../../RBT/RBT.hpp"
#include "../../ft_map/source/map.hpp"
#include "../../utils/pair.hpp"
#include <unistd.h>
#include <map>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

		template <typename value_type>
void check_parent(const Node<value_type> *node)
{
		if (!node)
				return ;
		if ((node->_child[LEFT]))
		{
				if ((node->_child[LEFT]->_parent) == node)
						std::cout << "parent ok" << std::endl;
				else
						std::cout << "!!!!!!!!" << std::endl;
		}
		if ((node->_child[RIGHT]))
		{
				if ((node->_child[RIGHT]->_parent) == node)
						std::cout << "parent ok" << std::endl;
				else
						std::cout << "!!!!!!!!" << std::endl;
		}
		check_parent(node->_child[LEFT]);
		check_parent(node->_child[RIGHT]);
}

int main(int ac,  char	**av)
{
		(void)ac;
		(void)av;

		{
				std::map<char, std::string> m;
				ft::map<char, std::string> ft_m;

				m['a'] = "an element";
				m['b'] = "another element";
				m['c'] = m['b'];
				m['a'] = "test";

				ft_m['a'] = "an element";
				std::cout << "ft_m['a'] " << ft_m['a'] << std::endl;
				return 1;
				ft_m['b'] = "another element";
				ft_m['c'] = ft_m['b'];
				ft_m['a'] = "test";
				std::cout << "std::map : " << m['a'] << m['b'] <<  m['c']<< std::endl;
				std::cout << "ft::map : " << ft_m['a'] << ft_m['b']<< ft_m['c']<< std::endl;

				EQUAL(m['a'] == ft_m['a'] && m['b'] == ft_m['b'] && m['c'] == ft_m['c'] && m.size() == ft_m.size());
				return 1;

				ft::map<int, std::string > my_map;
				for (size_t i = 0; i < 1e6; i++)
				{
						my_map[i] = "stack_overflow";	
				}
				return (1);

		}
		{
				ft::pair<int, std::string > arr[] = {
						ft::make_pair(1, "42"),
						ft::make_pair(2, "43"),
						ft::make_pair(3, "44"),
						ft::make_pair(4, "45"),
						ft::make_pair(5, "46"),
						ft::make_pair(6, "47"),
						ft::make_pair(7, "48")

				};
				ft::map<int, std::string > my_map(arr, arr+sizeof(arr)/ sizeof(arr[0]));
				ft::map<int, std::string> my_second_map = my_map;

				for (int i = 0; i < 10; i++)
						my_map[i] = "10e5";

				{
						std::cout << "my_map size :"<< my_map.size() << std::endl;
						std::cout << "my_map " << std::endl;
						//my_map.print();
						std::cout << "my_second_map size :"<< my_second_map.size() << std::endl;
						std::cout << "my_second_map " << std::endl;
						//						my_second_map.print();
				}

				my_second_map.swap(my_map);
				ft::map<int, std::string>::iterator tmp_end = my_second_map.end();
				std::cout << (--tmp_end)->first << std::endl;
				std::cout << (++tmp_end == my_second_map.end()) << std::endl;
				{
						std::cout << "my_map size :"<< my_map.size() << std::endl;
						std::cout << "my_map " << std::endl;
						my_map.print();
						std::cout << "my_second_map size :"<< my_second_map.size() << std::endl;
						std::cout << "my_second_map " << std::endl;
						//						my_second_map.print();
				}
				std::cout << "found value :" <<   my_map.find(7)->second << std::endl;
				my_second_map.clear();
				my_second_map.print();
				my_map.print();

				ft::map<int, std::string>::const_iterator it = my_map.begin();
				ft::map<int, std::string>::const_iterator end = my_map.end();

				const ft::map<int, std::string> const_map(my_map);				
				std::cout << "const_map found value :" <<   const_map.find(7)->second << std::endl;

				my_second_map.insert(ft::make_pair(1, "shiiit"));
				my_second_map.insert(my_second_map.begin(), ft::make_pair(1, "shiiit"));
				my_map.insert(ft::make_pair(1, "shiiit"));
				//				my_map.print();
				//				my_second_map.print();
				my_map[1] = "shiiiiit";
				my_map[0] = "zerooo";
				//				my_map.print();
				my_map.erase(1);
				my_map.erase(0);
				std::cout << "After erase call" << std::endl;
				//				my_map.print();
				typedef ft::map<int, std::string>::const_iterator c_iterator;
				for (c_iterator it = my_map.begin(); it != my_map.end(); )
				{
						std::cout << "key  : " << it->first ;
						std::cout << " associated value : " << it->second << std::endl;
						my_map.erase(it++);
				}
				std::cout << "After erasing all" << std::endl;
				//				my_map.print();
				std::cout << "my_map size : " << my_map.size() << std::endl;
				my_map.swap(my_second_map);
				std::cout << "my_map size : " << my_map.size() << std::endl;
				std::cout << my_second_map.count(1) << std::endl;
				{
						ft::map<char,int> mymap;
						ft::map<char,int>::iterator itlow,itup;

						mymap['a']=20;
						mymap['b']=40;
						mymap['c']=60;
						mymap['d']=80;
						mymap['e']=100;

						itlow=mymap.lower_bound ('b');  // itlow points to b
						itup=mymap.upper_bound ('d');   // itup points to e (not d!)
						std::cout << "lower bound " << itlow->first << std::endl;
						std::cout << "upper bound " << itup->first << std::endl;
				}
				{
						ft::map<char,int> mymap;

						mymap['a']=10;
						mymap['b']=20;
						mymap['c']=30;

						ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
						ret = mymap.equal_range('b');

						std::cout << "lower bound points to: ";
						std::cout << ret.first->first << " => " << ret.first->second << '\n';

						std::cout << "upper bound points to: ";
						std::cout << ret.second->first << " => " << ret.second->second << '\n';
				}
				{
						ft::map<char,int> foo,bar;
						foo['a']=100;
						foo['b']=200;
						bar['a']=10;
						bar['z']=1000;

						// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
						if (foo==bar) std::cout << "foo and bar are equal\n";
						if (foo!=bar) std::cout << "foo and bar are not equal\n";
						if (foo< bar) std::cout << "foo is less than bar\n";
						if (foo> bar) std::cout << "foo is greater than bar\n";
						if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
						if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		}
		{

				ft::map<char,int> mymap;

				mymap['x'] = 100;
				mymap['y'] = 200;
				mymap['z'] = 300;

				// show content:
				ft::map<char,int>::const_reverse_iterator rit;
				for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
						std::cout << rit->first << " => " << rit->second << '\n';
		}

		return (1);
}
{
		ft::pair<int, int> arr[] = {
				ft::make_pair(1, 42),
				ft::make_pair(2, 43),
				ft::make_pair(3, 44),
				ft::make_pair(4, 45),
				ft::make_pair(5, 46),
				ft::make_pair(6, 47),
				ft::make_pair(7, 48)
		};

		ft::map<int, int>  tree;
		tree.insert(arr[1]); //2
		tree.insert(arr[2]); //3
		tree.insert(arr[0]); // 1
		tree.erase(2); // 2
		tree.insert(arr[3]); // 4
		tree.insert(arr[6]); // 7
		tree.insert(arr[4]); //5
		tree.erase(3); 
		tree.insert(arr[5]); // 6
		tree.erase(3); 
		tree.insert(ft::make_pair(8, 33)); // 8
										   //		tree.print();
		ft::map<int, int>::iterator it = tree.begin();
		ft::map<int, int>::iterator end = tree.end();
		while (it != end)
		{
				//std::cout << "value.first :" << (*it).first << std::endl;
				std::cout << "value.first :" << it->first << std::endl;
				it++;
		}
		ft::map<int, int>::iterator begin = tree.begin();
		//--begin;	
		while (it != begin)
		{	
				it--;
				//std::cout << "end value.first :" << (*it).first << std::endl;
				std::cout << "end value.first :" << it->first << std::endl;
		}

		//tree.print();
		//tree.delete_(arr[2]);
		//tree.delete_(arr[1]);
		//tree.delete_(arr[4]);
		//tree.delete_(arr[3]);
		check_parent(tree.get_root()->get_root());
		//printBT(tree.get_root());
}
}
