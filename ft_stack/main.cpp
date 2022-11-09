#include <stdio.h>
#include <unistd.h>
#include "inc/stack.hpp"
#include <stack>
#include <vector>


using namespace NAMESPACE;


int main(void)
{
	vector<int>  larg_vec(10e2, 42);
	stack<int, vector<int> > int_stack;
	int_stack.push(42);
	int_stack.pop();
	
	std::cout << "stack is empty : " << std::boolalpha << int_stack.empty() << std::endl;
	std::cout << "stack size : "  <<  int_stack.size() << std::endl;
	stack<int, vector<int> > larg_stack(larg_vec);
	const stack<int, vector<int> > larg_stack_ccp(larg_vec);
	stack<int, vector<int> > larg_stack_cp;

	std::cout << "larg_stack is empty : " << std::boolalpha << larg_stack.empty() << std::endl;
	std::cout << "larg_stack size : "  <<  larg_stack.size() << std::endl;

	std::cout << "larg_stack_cp is empty : " << std::boolalpha << larg_stack_cp.empty() << std::endl;
	std::cout << "larg_stack_cp size : "  <<  larg_stack_cp.size() << std::endl;
	
	while (!larg_stack.empty())
	{
		larg_stack_cp.push(larg_stack.top());
		larg_stack.pop();
	}

	std::cout << "larg_stack is empty : " << std::boolalpha << larg_stack.empty() << std::endl;
	std::cout << "larg_stack size : "  <<  larg_stack.size() << std::endl;

	std::cout << "larg_stack_cp is empty : " << std::boolalpha << larg_stack_cp.empty() << std::endl;
	std::cout << "larg_stack_cp size : "  <<  larg_stack_cp.size() << std::endl;

	std::cout <<  std::boolalpha  <<  (larg_stack_cp == larg_stack_ccp )<< std::endl;

	return (0);
}

