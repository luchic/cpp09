/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:54:43 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/31 13:26:07 by nluchini         ###   ########.fr       */
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
	std::vector<int> _tmpMainVector;
	std::vector<int> _tmpPendVector;

	void _swapPair(std::vector<int> &small, std::vector<int> &big);
	void _swap(std::size_t i, std::size_t j);
	
	void _fillMain(int level);
	void _fillPend(int level);
	void _preMerging(int level);
	void _insert(int value);
	void _merging(int level);
	int _getJacobsthalNumber(int level);

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
};

#endif