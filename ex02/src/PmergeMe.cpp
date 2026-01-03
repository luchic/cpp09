/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:02:28 by nluchini          #+#    #+#             */
/*   Updated: 2026/01/03 17:31:13 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.h"
#include <cmath>
#include <iostream>
#include <algorithm>

template <typename _Seq>
std::size_t PmergeMe<_Seq>::_jacobsthalNumber(std::size_t n)
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

template <typename _Seq>
std::vector<std::size_t> PmergeMe<_Seq>::_jacobInsertionOrder(std::size_t pairCount)
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

template <typename _Seq>
void PmergeMe<_Seq>::_insertJacobBlock(
	std::vector<_Seq>& mainFlat,
	_Seq value,
	std::size_t index)
{
	auto insertValue = *(value.rbegin());
	auto pos = std::upper_bound(mainFlat.begin(),
			mainFlat.begin() + index + 2, 
			insertValue,
			[](int v, const _Seq& block) {
				return v < block.back();
			});
	mainFlat.insert(pos, value);
}

template <typename _Seq>
bool PmergeMe<_Seq>::isSorted() const
{
	return std::is_sorted(_origin.begin(), _origin.end());
}

template <typename _Seq>
PmergeMe<_Seq>::PmergeMe()
{}

template <typename _Seq>
PmergeMe<_Seq>::PmergeMe(const PmergeMe& other) :
	_origin(other._origin),
	_originQueue(other._originQueue)
{
}

template <typename _Seq>
PmergeMe<_Seq>& PmergeMe<_Seq>::operator=(const PmergeMe<_Seq>& other)
{
	if (this != &other)
	{
		_originQueue = other._originQueue;
		_origin = other._origin;
	}
	return *this;
}

template <typename _Seq>
PmergeMe<_Seq>::~PmergeMe()
{
}

template <typename _Seq>
PmergeMe<_Seq>::PmergeMe(_Seq values)
{
	for (int element : values)
	{
		_origin.push_back(element);
	}
}

template <typename _Seq>
void PmergeMe<_Seq>::print()
{
	if (_origin.size() == 0)
	{
		std::cout << "Empty." << std::endl;
		return;
	}
	std::cout << _origin[0];
	for(std::size_t i = 1; i < _origin.size(); ++i)
	{
		std::cout << " " << _origin[i];
	}
	std::cout << std::endl;
}

template <typename _Seq>
void PmergeMe<_Seq>::printFirst(std::size_t first)
{
	if (_origin.size() == 0)
	{
		std::cout << "Empty." << std::endl;
		return;
	}
	std::cout << _origin[0];
	for(std::size_t i = 1; i < _origin.size() && i < first; ++i)
	{
		std::cout << " " << _origin[i];
	}
	if (first < _origin.size())
		std::cout << " [..]";
	std::cout << std::endl;
}

template <typename _Seq>
void PmergeMe<_Seq>::_swapPair(_Seq &small, _Seq &big)
{
	auto tmp = small;
	small = big;
	big = tmp;
}

template <typename _Seq>
void PmergeMe<_Seq>::_merging(
	const std::size_t blockSize,
	const std::size_t chunkSize)
{
	if (blockSize == 0 || _origin.size() < chunkSize)
		return;

	Pairs pairs;
	pairs.reserve(_origin.size() / chunkSize);

	std::size_t i = 0;
	for (; i + chunkSize <= _origin.size(); i += chunkSize)
	{
		_Seq small;
		_Seq big;
		small.assign(_origin.begin() + i,
			_origin.begin() + i + blockSize);
		big.assign(_origin.begin() + i + blockSize,
			_origin.begin() + i + chunkSize);
		pairs.push_back(std::make_pair(small, big));
	}

	if (pairs.empty())
		return;

	bool hasStragglerBlock = false;
	_Seq straggler;
	if (i + blockSize <= _origin.size())
	{
		hasStragglerBlock = true;
		straggler.assign(_origin.begin() + i,
			_origin.begin() + i + blockSize);
		i += blockSize;
	}

	_Seq tail;
	if (i < _origin.size())
		tail.assign(_origin.begin() + i, _origin.end());

	std::vector<_Seq> main;
	std::vector<_Seq> pend;

	main.reserve(_origin.size());
	main.push_back(pairs[0].first);
	main.push_back(pairs[0].second);

	for (std::size_t p = 1; p < pairs.size(); ++p)
	{
		main.push_back(pairs[p].second);
		pend.push_back(pairs[p].first);
	}
	if (hasStragglerBlock)
		pend.push_back(straggler);
	
	if (pend.empty())
		return;

	const std::vector<std::size_t> order = _jacobInsertionOrder(pend.size());
	for (std::size_t j = 0; j < order.size(); ++j)
	{
		std::size_t blockPos = order[j];
		auto curBlock = pend[blockPos];
		_insertJacobBlock(main, curBlock, blockPos + j);
	}

	_Seq _tmp;
	for (auto v : main)
	{
		_tmp.insert(_tmp.end(), v.begin(), v.end());
	}
	if (!tail.empty())
		_tmp.insert(_tmp.end(), tail.begin(), tail.end());
	_origin = _tmp;
}

template <typename _Seq>
void PmergeMe<_Seq>::_sortPairs(
	const std::size_t blockSize,
	const std::size_t chunkSize)
{
	if (_origin.size() < chunkSize)
		return ;

	Pairs pairs;
	pairs.reserve(_origin.size() / chunkSize);

	std::size_t i = 0;
	for(; i + chunkSize <= _origin.size(); i += chunkSize)
	{	
		_Seq small;
		_Seq big;

		small.assign(_origin.begin() + i,
			_origin.begin() + i + blockSize);
		big.assign(_origin.begin() + i + blockSize,
			_origin.begin() + i + chunkSize);
		if (*small.rbegin() > *big.rbegin())
			_swapPair(small, big);
		pairs.push_back(std::make_pair(small, big));
	}
	_Seq tail;
	tail.assign(_origin.begin() + i, _origin.end());

	_origin.clear();
	for (i = 0; i < pairs.size(); ++i)
	{
		_origin.insert(_origin.end(),
			pairs[i].first.begin(), pairs[i].first.end());
		_origin.insert(_origin.end(),
			pairs[i].second.begin(), pairs[i].second.end());
	}
	_origin.insert(_origin.end(), tail.begin(), tail.end());
}

template <typename _Seq>
void PmergeMe<_Seq>::_sortVector(int level)
{
	const std::size_t blockSize = (1u << (level - 1));
	const std::size_t chunkSize = blockSize << 1u;

	if (_origin.size() < chunkSize)
		return ;
	
	_sortPairs(blockSize, chunkSize);
	_sortVector(level + 1);
	_merging(blockSize, chunkSize);
}

template <typename _Seq>
void PmergeMe<_Seq>::runSorting()
{
	_sortVector(1);
}

template class PmergeMe<std::vector<int>>;
template class PmergeMe<std::deque<int>>;