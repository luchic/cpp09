/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:02:28 by nluchini          #+#    #+#             */
/*   Updated: 2026/01/02 18:46:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.h"
#include <cmath>
#include <iostream>
#include <algorithm>


// ===================== For tests ===============================
namespace
{
	static std::size_t jacobsthalNumber(std::size_t n)
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

	static std::vector<std::size_t> jacobInsertionOrder(std::size_t pairCount)
	{
		std::vector<std::size_t> order;
		if (pairCount == 0)
			return order;

		for(std::size_t k = 3;;k++)
		{
			std::size_t prev = jacobsthalNumber(k - 1); 
			std::size_t cur = jacobsthalNumber(k);
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

    // upper_bound on "block maxima" within [0, boundBlocks)
	static std::vector<std::vector<int>>::const_iterator insertJacobBlock(
		std::vector<std::vector<int>>& mainFlat,
		std::vector<int> value,
		std::size_t index)
	{
		auto insertValue = *(value.rbegin());
		auto pos = std::upper_bound(mainFlat.begin(),
				mainFlat.begin() + index,
				insertValue,
				[](int v, const std::vector<int>& block) {
        			return v < block.back();
    			});
		mainFlat.insert(pos, value);
		return pos;
	}
}

// ===================== For tests ===============================


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

void PmergeMe::printPendCurrentState()
{
	std::cout << "Pend: ";
	if (_tmpPendVector.size() == 0)
	{
		std::cout << "Empty." << std::endl;
		return;
	}
	std::cout  << _tmpPendVector[0];
	for(std::size_t i = 1; i < _tmpPendVector.size(); ++i)
	{
		std::cout << " " << _tmpPendVector[i];
	}
	std::cout << std::endl;	
}

void PmergeMe::printMainCurrentState()
{
	std::cout << "Main: ";
	if (_tmpMainVector.size() == 0)
	{
		std::cout << "Empty." << std::endl;
		return;
	}
	std::cout  << _tmpMainVector[0];
	for(std::size_t i = 1; i < _tmpMainVector.size(); ++i)
	{
		std::cout << " " << _tmpMainVector[i];
	}
	std::cout << std::endl;	
}

int PmergeMe::_getJacobsthalNumber(int level)
{
	if (level <= 0)
		return 0;
	if (level == 1)
		return 1;

	long long j0 = 0;
	long long j1 = 1;

    for (int i = 2; i <= level; ++i)
    {
		long long j = j1 + 2 * j0; // J(i)
		j0 = j1;
		j1 = j;
	}
	return static_cast<int>(j1);
}

void PmergeMe::_fillPend(int level)
{
	_tmpPendVector.clear();
	int pair = static_cast<int>(std::pow(2, level)) >> 1;
	for(int i = pair << 1; i + pair <= static_cast<int>(_originVector.size());
		i += pair)
	{    
		for(int j = 0, base = i; j < pair; ++i, ++j)
		{
			_tmpPendVector.push_back(_originVector[base + j]);
		}
	}
}

void PmergeMe::_fillMain(int level)
{
	_tmpMainVector.clear();

	int pair = static_cast<int>(std::pow(2, level)) >> 1;
	
	int i = 0;
	for (; i < pair << 1 && i < static_cast<int>(_originVector.size()); i++)
	{
		_tmpMainVector.push_back(_originVector[i]);
	}
	for(i += pair; i + pair <= static_cast<int>(_originVector.size()); i += pair)
	{
		for(int j = 0, base = i; j < pair; ++i, ++j)
		{    
			_tmpMainVector.push_back(_originVector[base + j]);
		}
	}
}

void PmergeMe::_preMerging(int level)
{
	_fillPend(level);
	_fillMain(level);
	// printVector();
	// printPendCurrentState();
	// printMainCurrentState();
}	

void PmergeMe::_swap(std::size_t i, std::size_t j)
{
	std::size_t tmp = _originVector[j];
	_originVector[j] = _originVector[i];
	_originVector[i] = tmp;
}

void PmergeMe::_swapPair(std::vector<int> &small, std::vector<int> &big)
{
	auto tmp = small;
	small = big;
	big = tmp;
}

void PmergeMe::_insert(int value)
{
	std::vector<int>::iterator pos = std::upper_bound(_tmpMainVector.begin(), _tmpMainVector.end(), value);

    _tmpMainVector.insert(pos, value);
}

void PmergeMe::_merging(int level)
{
	const std::size_t blockSize = (1u << (level - 1));
    const std::size_t chunkSize = blockSize << 1u;

    if (blockSize == 0 || _originVector.size() < chunkSize)
        return;

    // Build (small,big) blocks from current _originVector layout
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

    // Handle a possible straggler block of size blockSize (odd number of blocks)
    bool hasStragglerBlock = false;
    std::vector<int> straggler;
    if (i + blockSize <= _originVector.size())
    {
        hasStragglerBlock = true;
        straggler.assign(_originVector.begin() + i, _originVector.begin() + i + blockSize);
        i += blockSize;
    }

    // Keep any remaining tail (< blockSize) as-is (simplest safe handling)
    std::vector<int> tail;
    if (i < _originVector.size())
        tail.assign(_originVector.begin() + i, _originVector.end());

    if (pairs.empty())
        return;

    // Main chain: [small0][big0][big1]...[big(n-1)]
    std::vector<std::vector<int>> main;
	std::vector<std::vector<int>> pend;
	std::vector<int> rest;
    main.reserve(_originVector.size());

    std::vector<std::size_t> bigPosBlocks(pairs.size());

	main.push_back(pairs[0].first);
	main.push_back(pairs[0].second);


    for (std::size_t p = 1; p < pairs.size(); ++p)
    {
		main.push_back(pairs[p].second);
		pend.push_back(pairs[p].first);
    }
	if (hasStragglerBlock)
		pend.push_back(straggler);

    // Insert pending small blocks in Jacobsthal order, bounded before their paired big block
    const std::vector<std::size_t> order = jacobInsertionOrder(pend.size());
    for (std::size_t j = 0; j < order.size(); ++j)
    {
        std::size_t blockPos = order[j];
		auto curBlock = pend[blockPos];
        insertJacobBlock(main, curBlock, blockPos + j);
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
	

	std::cout << "Pairs: ";
	printVector();
	_sortVector(level + 1);
	_merging(level);
	std::cout << "Merged: ";
	printVector();
}

void PmergeMe::runSorting()
{
	_sortVector(1);
}