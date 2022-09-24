#include  <iostream>
#include "src/ft_vector.tpp"

int main(int ac,  char	**av)
{
	(void)ac;
	(void)av;
	ft_vector<int> vec_int;
	ft_vector<int> vec_char(13, 42); // calling Range constructor instrad of fill constructo 

	return (0);
}

