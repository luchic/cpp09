/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:54:43 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/20 11:55:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PMERGME_H
#define __PMERGME_H

class PmergeMe
{
private:
	/* data */
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe &operator=(const PmergeMe& other);
	~PmergeMe();
};


#endif