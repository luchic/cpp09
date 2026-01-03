/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:22:35 by nluchini          #+#    #+#             */
/*   Updated: 2026/01/03 17:32:29 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.h"
#include <iostream>
#include <string>
#include <optional>
#include <chrono>
#include <iomanip>


static double run_benchmark_vector(PmergeMe<std::vector<int>>& pm)
{
	const std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
	pm.runSorting();
	const std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	const double us = std::chrono::duration<double, std::micro>(t1 - t0).count();;
	return us;
}

static double run_benchmark_deque(PmergeMe<std::deque<int>>& pm)
{
	const std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
	pm.runSorting();
	const std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	if (!pm.isSorted())
		std::cout << "Error: vector result not sorted.\n";
	const double us = std::chrono::duration<double, std::micro>(t1 - t0).count();
	return us;
}

std::optional<int> getValue(char *value)
{
	try
	{
		std::size_t pos;
		int v = std::stoi(std::string(value), &pos);
		if (value[pos] != '\0')
			return std::nullopt;
		return v; 
	}
	catch(...)
	{
		return std::nullopt;
	}
}

std::pair<std::vector<int>, std::deque<int>> parseValues(char *argv[], int size)
{
	std::vector<int> tmpVector;
	std::deque<int> tmpDeque;
	tmpVector.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		auto value = getValue(argv[i]);
		if (!value.has_value())
		{
			std::cout << "Error." << std::endl;
			std::exit(0);
		}
		else if (value.value() < 0)
		{
			std::cout << "Error." << std::endl;
			std::exit(0);
		}
		tmpVector.push_back(value.value());
		tmpDeque.push_back(value.value());
	}
	return (std::make_pair(tmpVector, tmpDeque));
}

void run(std::pair<std::vector<int>, std::deque<int>>& pair)
{
	auto size = pair.first.size();
	PmergeMe pmVector(pair.first);
	PmergeMe pmDeque(pair.second);

	std::cout << std::endl;
	std::cout << "Befor: ";
	pmVector.printFirst();

	auto timeV = run_benchmark_vector(pmVector);
	auto timeD = run_benchmark_deque(pmDeque);

	std::cout << "After: ";
	pmVector.printFirst();

	std::cout << "Time to process a range of " << size
		<< " elements with std::vector : "
		<< std::fixed << std::setprecision(5) << timeV << " us\n";
	
	std::cout << "Time to process a range of " << size
			<< " elements with std::deque : "
			<< std::fixed << std::setprecision(5) << timeD << " us\n";
}

std::vector<int> get_tests_value(int n)
{
	std::vector<int> tmp;

	for(int i = n; i > 0; --i)
	{
		tmp.push_back(i);
	}
	return tmp;
}


void run_test()
{
	for (int i = 1; i < 1000; ++i)
	{
		try
		{
			PmergeMe pm(get_tests_value(i));
			pm.runSorting();
			if (!pm.isSorted())
			{
				std::cout << "Value not sorted i: " << i << std::endl;
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error i: []" << i << "] " << e.what() << '\n';
			
		}	
	}
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: wrong number of arguments.\n"
                  << "Usage: " << argv[0] << " [values]\n";
        return 0;
    }
	if (std::string(argv[1]) == "-t")
		run_test();
	else
	{
		auto values = parseValues(argv + 1, argc - 1);
		run(values);
	}
}
