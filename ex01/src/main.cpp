/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:22:35 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/20 11:43:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: wrong number of arguments.\n"
                  << "Usage: " << argv[0] << " <expression>\n";
        return 1;
    }

	RPN rpn;
	
	auto value = rpn.calculate(std::string(argv[1]));
	if (!value.has_value())
		std::cout << "Error" << std::endl;
	else
		std::cout << value.value() << std::endl;
	return 0;
}