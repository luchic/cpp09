/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:39:02 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/20 11:48:21 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RPN_H
#define __RPN_H

#include <stack>
#include <string>
#include <optional>

class RPN
{
private:
	std::stack<double> _stash;

	bool _isSign(char c);
	void _execute(char c);
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	std::optional<double> calculate(std::string input);
};

#endif