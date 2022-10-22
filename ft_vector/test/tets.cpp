/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rite2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:38:31 by adriouic          #+#    #+#             */
/*   Updated: 2022/10/22 22:51:18 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "../inc/vector.hpp"
#define TESTED_TYPE int
#define TESTTED_NAMESPACE ft

int		main(void)
{
	const int size = 5;
	TESTTED_NAMESPACE::vector<TESTED_TYPE> vct(size);

	//TESTTED_NAMESPACE::vector<tested_type>::reverse_iterator it = vct.rbegin();
	//TESTTED_NAMESPACE::vector<tested_type>::const_reverse_iterator ite = vct.rbegin();

	TESTTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	TESTTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator  ite = vct.rbegin();
	
	std::cout << *it <<  " " << *it << std::endl;
	return (1);
	(void) it;
	(void) ite;

	for (int i = 0; i < size; ++i)
		//it[i] = (size - i) * 5;
		std::cout << "v : " << it[i]  << std::endl;

	/*

	it = it + 5;
	it = 1 + it;
	it = it - 4;

	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
*/
	//printSize(vct, true);
	return (0);
}
