/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:22:35 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/19 16:16:45 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: wrong number of arguments.\n"
                  << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

	try
	{
		BitcoinExchange exchanger;
		exchanger.convert(std::string(argv[1]));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}