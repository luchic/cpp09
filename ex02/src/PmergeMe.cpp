/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:02:28 by nluchini          #+#    #+#             */
/*   Updated: 2026/01/03 15:40:04 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.h"
#include <cmath>
#include <iostream>
#include <algorithm>



std::size_t PmergeMe::_jacobsthalNumber(std::size_t n)
{

	if (n == 0) return 0;
	if (n == 1) return 1;
	std::size_t j0 = 0, j1 = 1;
	for (std::size_t i = 2; i <= n; ++i)
	{
		std::size_t j = j1 + 2 * j0;
		j0 = j1;
		j1 = j;
	}
	return j1;
}

std::vector<std::size_t> PmergeMe::_jacobInsertionOrder(std::size_t pairCount)
{
	std::vector<std::size_t> order;
	if (pairCount == 0)
		return order;

	for(std::size_t k = 3;;k++)
	{
		std::size_t prev = _jacobsthalNumber(k - 1); 
		std::size_t cur = _jacobsthalNumber(k);
		// 1 3 5 11 22
		// b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13 b14 b15 b16 b17 b18 b19
		//  0  1  2  3  4  5  6  7  8   9   10
		if (cur > pairCount)
		{
			std::size_t orderSize = order.size();
			for (std::size_t i = pairCount; i > orderSize; i--)
				order.push_back(i - 1);
			break;
		}
		for (std::size_t i = 0; i < cur - prev; i++)
		{
			std::size_t tmp = cur - i - 2;
			order.push_back(tmp);
		}
	}
	return order;
}

void PmergeMe::_insertJacobBlock(
	std::vector<std::vector<int>>& mainFlat,
	std::vector<int> value,
	std::size_t index)
{
	auto insertValue = *(value.rbegin());
	auto pos = std::upper_bound(mainFlat.begin(),
			mainFlat.begin() + index + 2, 
			insertValue,
			[](int v, const std::vector<int>& block) {
				return v < block.back();
			});
	mainFlat.insert(pos, value);
}


bool PmergeMe::isSorted() const
{
	return std::is_sorted(_originVector.begin(), _originVector.end());
}

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other) :
	_originVector(other._originVector),
	_originQueue(other._originQueue)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_originQueue = other._originQueue;
		_originVector = other._originVector;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(std::vector<int> values)
{
	for (int element : values)
	{
		_originQueue.push(element);
		_originVector.push_back(element);
	}
}

void PmergeMe::printVector()
{
	if (_originVector.size() == 0)
	{
		std::cout << "Empty." << std::endl;
		return;
	}
	std::cout << "Vector: " << _originVector[0];
	for(std::size_t i = 1; i < _originVector.size(); ++i)
	{
		std::cout << " " << _originVector[i];
	}
	std::cout << std::endl;
}

void PmergeMe::_swapPair(std::vector<int> &small, std::vector<int> &big)
{
	auto tmp = small;
	small = big;
	big = tmp;
}

void PmergeMe::_merging(int level)
{
	const std::size_t blockSize = (1u << (level - 1));
	const std::size_t chunkSize = blockSize << 1u;

	if (blockSize == 0 || _originVector.size() < chunkSize)
		return;

	Pairs pairs;
	pairs.reserve(_originVector.size() / chunkSize);

	std::size_t i = 0;
	for (; i + chunkSize <= _originVector.size(); i += chunkSize)
	{
		std::vector<int> small;
		std::vector<int> big;
		small.assign(_originVector.begin() + i, _originVector.begin() + i + blockSize);
		big.assign(_originVector.begin() + i + blockSize, _originVector.begin() + i + chunkSize);
		pairs.push_back(std::make_pair(small, big));
	}

	bool hasStragglerBlock = false;
	std::vector<int> straggler;
	if (i + blockSize <= _originVector.size())
	{
		hasStragglerBlock = true;
		straggler.assign(_originVector.begin() + i, _originVector.begin() + i + blockSize);
		i += blockSize;
	}

	std::vector<int> tail;
	if (i < _originVector.size())
		tail.assign(_originVector.begin() + i, _originVector.end());

	if (pairs.empty())
		return;

	std::vector<std::vector<int>> main;
	std::vector<std::vector<int>> pend;

	main.reserve(_originVector.size());
	main.push_back(pairs[0].first);
	main.push_back(pairs[0].second);

	for (std::size_t p = 1; p < pairs.size(); ++p)
	{
		main.push_back(pairs[p].second);
		pend.push_back(pairs[p].first);
	}
	if (hasStragglerBlock)
		pend.push_back(straggler);

	const std::vector<std::size_t> order = _jacobInsertionOrder(pend.size());
	for (std::size_t j = 0; j < order.size(); ++j)
	{
		std::size_t blockPos = order[j];
		auto curBlock = pend[blockPos];
		_insertJacobBlock(main, curBlock, blockPos + j);
	}

	std::vector<int> _tmp;
	for (auto v : main)
	{
		_tmp.insert(_tmp.end(), v.begin(), v.end());
	}
	if (!tail.empty())
		_tmp.insert(_tmp.end(), tail.begin(), tail.end());
	_originVector = _tmp;
}

void PmergeMe::_sortVector(int level)
{
	const std::size_t blockSize = (1u << (level - 1));
	const std::size_t chunkSize = blockSize << 1u;

	if (_originVector.size() < chunkSize)
		return ;

	Pairs pairs;
	pairs.reserve(_originVector.size() / chunkSize);

	std::size_t i = 0;
	for(; i + chunkSize <= _originVector.size(); i += chunkSize)
	{	
		std::vector<int> small;
		std::vector<int> big;

		// PairBlock bl;
		small.assign(_originVector.begin() + i, _originVector.begin() + i + blockSize);
		big.assign(_originVector.begin() + i + blockSize, _originVector.begin() + i + chunkSize);
		if (*small.rbegin() > *big.rbegin())
			_swapPair(small, big);
		pairs.push_back(std::make_pair(small, big));
	}
	std::vector<int> tail;
	tail.assign(_originVector.begin() + i, _originVector.end());

	_originVector.clear();
	for (i = 0; i < pairs.size(); ++i)
	{
		_originVector.insert(_originVector.end(), pairs[i].first.begin(), pairs[i].first.end());
		_originVector.insert(_originVector.end(), pairs[i].second.begin(), pairs[i].second.end());
	}
	_originVector.insert(_originVector.end(), tail.begin(), tail.end());
	

	// std::cout << "Pairs: ";
	// printVector();
	_sortVector(level + 1);
	_merging(level);
	// std::cout << "Merged: ";
	// printVector();
}

void PmergeMe::runSorting()
{
	_sortVector(1);
}