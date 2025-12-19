/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:24:16 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/19 16:14:23 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string> 

BitcoinExchange::BitcoinExchange()
{
	_initDataBase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _dataAccess(other._dataAccess)
{
}


BitcoinExchange::BitcoinExchange(std::string dataBase)
{
	_initDataBase(dataBase);
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _dataAccess = other._dataAccess;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::vector<std::string> BitcoinExchange::_split(const std::string& str, char delim)
{
	std::vector<std::string> out;
	std::stringstream ss(str);
	std::string part;

	while (std::getline(ss, part, delim))
		out.push_back(part);

	return out;	
}

std::string BitcoinExchange::_trimSpace(std::string s)
{
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };

	s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
	s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
	return s;
}

void BitcoinExchange::_initDataBase(std::string dataBase)
{
    const std::string path = dataBase.empty() ? std::string(DATA_BASE) : dataBase;

	std::ifstream db(path);
	if (!db.is_open())
		throw BitcoinExchange::NoDataBaseException();

	std::string line;
	if (!std::getline(db, line))
		throw BitcoinExchange::EmptyDataBaseFileException();

	if (line != "date,exchange_rate")
	{
		std::cout << "Error: bad database header." << std::endl;
		return;
	}

	while (std::getline(db, line))
    {
		if (line.empty())
			continue;

		std::vector<std::string> fields = _split(line, ',');
		if (fields.size() != 2)
			continue;

		std::string date = _trimSpace(fields[0]);
		std::string rateStr = _trimSpace(fields[1]);

		if (!_isValidDate(date))
            continue;

		std::optional<float> rate = _convertValue(rateStr);
		if (!rate.has_value())
			continue;

		_dataAccess[date] = rate.value();
	}
}

void BitcoinExchange::_printErrorMessage(std::string value, t_error_code code)
{
	std::cout << "Error: ";
	switch (code)
	{
	case ERR_BAD_HEADER:
		std::cout << "Bad header error: " << value
			<< " expected: data | value" << std::endl;
		break;
	case ERR_BAD_INPUT:
		std::cout << "Bad input data => " << value  << "" << std::endl; 
		break;
	case ERR_INVALID_DATE:
		std::cout << "Invalid data: " << value << " expected: YYYY-MM-DD"
			<< std::endl;
 		break;
	case ERR_NEGATIVE:
		std::cout << "Not a positive number." << std::endl;
		break;
	case ERR_NOT_NUMBER:
		std::cout << "Not a number: " << value << std::endl;
		break;
	case ERR_LARGE_VALUE:
		std::cout << "Too largae a number." << std::endl;
		break;
	case ERR_NO_DATA:
		std::cout << "No data found." << std::endl;
		break;
	default:
		std::cout << "no expected error" << std::endl;
		break;
	}	
}

std::optional<float> BitcoinExchange::_convertValue(std::string value)
{
	try
	{
		std::size_t pos;
		float number = std::stof(value, &pos);
		if (value[pos] != '\0')
			return std::nullopt;
		return number;
	}
	catch(...)
	{
		return std::nullopt;
	}
}

bool BitcoinExchange::_isLeap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


bool BitcoinExchange::_isValidDate(std::string date)
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int year  = (date[0]-'0')*1000 + (date[1]-'0')*100 +
		(date[2]-'0')*10 + (date[3]-'0');
	int month = (date[5]-'0')*10   + (date[6]-'0');
	int day   = (date[8]-'0')*10   + (date[9]-'0');
	
	if (month < 1 || month > 12)
		return false;
	
	int daysLimits[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int maxDay = daysLimits[month - 1];
	if (month == 2 && _isLeap(year))
		maxDay = 29;
		
	return day >= 1 && day <= maxDay;
}

bool BitcoinExchange::_isValidFormat(std::string format)
{
	std::string origin_format = std::string(STR_INPUT_FORMAT);
	return format.compare(origin_format) == 0;
}

void BitcoinExchange::_printExchangeMessage(std::string date, float value)
{
	auto optional_cost = _getCostByDate(date);
	if (!optional_cost.has_value())
	{
		_printErrorMessage(date, ERR_NO_DATA);
		return;
	}

	float cost = optional_cost.value();
	std::cout << date << " => " << value << " = " << value * cost << std::endl;
}

void BitcoinExchange::_convertLine(std::string line)
{
	auto tokens = _split(line, DATE_VALUE_DELIMITER);
	if(tokens.size() != 2)
	{
		_printErrorMessage(ERR_BAD_INPUT);
		return;
	}
	std::string date = _trimSpace(tokens[0]);
	if(!_isValidDate(date))
	{
		_printErrorMessage(date, ERR_INVALID_DATE);
		return;
	}
	
	std::optional<float> opt_value = _convertValue(tokens[1]);
	if (!opt_value.has_value())
	{
		_printErrorMessage(tokens[1], ERR_NOT_NUMBER);
		return;
	}
	float value = opt_value.value();
	if (value < 0)
	{
		_printErrorMessage(ERR_NEGATIVE);
		return;
	}
	if (value > 1000)
	{
		_printErrorMessage(ERR_LARGE_VALUE);
		return;
	}
	_printExchangeMessage(date, value);
}

void BitcoinExchange::convert(std::string input)
{
	std::ifstream infile(input);
	std::string line = "";

	if(!infile.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return;
	}

	std::getline(infile, line);
	if (line[line.size() - 1] == '\n')
		line = line.substr(0, line.size() - 1);
	if(!_isValidFormat(line))
	{
		_printErrorMessage(ERR_BAD_HEADER);
		return;
	}
	
	while (std::getline(infile, line))
	{
		_convertLine(line);
	}
}
