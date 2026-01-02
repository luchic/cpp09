/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:22:35 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/26 12:43:08 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.h"
#include <iostream>
#include <string>
#include <optional>

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     std::cout << "Error: wrong number of arguments.\n"
    //               << "Usage: " << argv[0] << " [values]\n";
    //     return 0;
    // }

	(void) argc;
	(void) argv;
	
	std::vector<int> values = {2, 3, 18, 19, 8, 14, 6, 9, 21, 16, 5, 10, 23, 15, 1, 11, 17, 20, 12, 22, 13, 7, 4};
	// std::vector<int> values = {4, 3, 2, 1};
	
	PmergeMe pm(values);

	pm.printVector();

	pm.runSorting();

	pm.printVector();	
}
