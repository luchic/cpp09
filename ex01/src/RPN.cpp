/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:39:34 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/20 11:48:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.h"

RPN::RPN()
{	
}

RPN::RPN(const RPN& other) :_stash(other._stash)
{	
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stash = other._stash;
	return *this;	
}

RPN::~RPN()
{	
}

bool RPN::_isSign(char c)
{
	return c == '*' || c == '+' || c == '-' || c == '/'; 
}

void RPN::_execute(char c)
{
	double first = _stash.top();
	_stash.pop();
	double second = _stash.top();
	_stash.pop();

	double res = 0;
	switch (c)
	{
	case '+':
		res = second + first;
		break;
	case '-':
		res = second - first;
		break;
	case '*':
		res = second * first;
		break;
	case '/':
		res = second / first;
		break;
	}
	_stash.push(res);
}

std::optional<double> RPN::calculate(std::string input)
{
	for(int i = 0; input[i]; ++i)
	{
		if (std::isspace(input[i]))
			continue;
		else if (std::isdigit(input[i]))
			_stash.push(input[i] - '0');
		else if (_isSign(input[i]) && _stash.size() >= 2)
			_execute(input[i]);
		else
			return std::nullopt;
	} 
	if (_stash.size() != 1)
		return std::nullopt;
	return _stash.top();
}