/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:54:43 by nluchini          #+#    #+#             */
/*   Updated: 2026/01/03 16:09:36 by nluchini         ###   ########.fr       */
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

typedef std::vector<std::pair<std::vector<int>, std::vector<int>>> Pairs;

class PmergeMe
{
private:
	std::vector<int> _originVector;
	std::queue<int> _originQueue;

	std::size_t _jacobsthalNumber(std::size_t n);
	std::vector<std::size_t> _jacobInsertionOrder(std::size_t pairCount);
	void _insertJacobBlock(
		std::vector<std::vector<int>>& mainFlat,
		std::vector<int> value,
		std::size_t index);

	void _swapPair(std::vector<int> &small, std::vector<int> &big);
	void _merging(const std::size_t blockSize, const std::size_t chunkSize);
	void _sortPairs(const std::size_t blockSize, const std::size_t chunkSize);
	void _sortVector(int level);
	void _sortQueue();

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe &operator=(const PmergeMe& other);
	~PmergeMe();

	PmergeMe(std::vector<int> values);

	void runSorting();
	void printVector();
	void printPendCurrentState();
	void printMainCurrentState();
	bool isSorted() const;
};

#endif