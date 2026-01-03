/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:54:43 by nluchini          #+#    #+#             */
/*   Updated: 2026/01/03 17:20:55 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PMERGME_H
#define __PMERGME_H

#include <vector>
#include <queue>

struct PairBlock
{
	std::vector<int> small;
	std::vector<int> big;
};


template <typename _Seq=std::vector<int>>
class PmergeMe
{
private:
	_Seq _origin;
	std::deque<int> _originQueue;
	typedef std::vector<std::pair<_Seq, _Seq>> Pairs;

	std::size_t _jacobsthalNumber(std::size_t n);
	std::vector<std::size_t> _jacobInsertionOrder(std::size_t pairCount);
	void _insertJacobBlock(
		std::vector<_Seq>& mainFlat,
		_Seq value,
		std::size_t index);

	void _swapPair(_Seq &small, _Seq &big);
	void _merging(const std::size_t blockSize, const std::size_t chunkSize);
	void _sortPairs(const std::size_t blockSize, const std::size_t chunkSize);
	void _sortVector(int level);
	void _sortQueue();

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe &operator=(const PmergeMe& other);
	~PmergeMe();

	PmergeMe(_Seq values);

	void runSorting();
	void print();
	void printFirst(std::size_t first = 4);
	bool isSorted() const;
};

#endif