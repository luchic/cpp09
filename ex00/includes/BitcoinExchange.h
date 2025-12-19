/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:02:33 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/19 16:10:09 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BITCOINEXCHANGE_H
#define __BITCOINEXCHANGE_H

#include <map>
#include <string>
#include <exception>
#include <vector>
#include <optional>

#define DATE_VALUE_DELIMITER '|'
#define STR_INPUT_FORMAT "date | value"
#define DATA_BASE "./data.csv"

typedef enum e_error_code {
    ERR_BAD_HEADER,
    ERR_BAD_INPUT,
    ERR_INVALID_DATE,
    ERR_NEGATIVE,
	ERR_NOT_NUMBER,
    ERR_LARGE_VALUE,
	ERR_NO_DATA,
	ERR_NO_FILE
} t_error_code;

class BitcoinExchange
{
private:
	std::map<std::string, unsigned int> _dataAccess;

	std::vector<std::string> _split(const std::string& str, char delim);
	std::string _trimSpace(std::string str);
	bool _isLeap(int year);
	void _initDataBase(std::string dataBase = "");
	bool _isValidDate(std::string date);
	bool _isValidFormat(std::string format);
	void _printErrorMessage(std::string value, t_error_code code);
	void _printErrorMessage(t_error_code code);
	void _printExchangeMessage(std::string date, float value);
	
	int _getValueByDate(std::string date);
	std::optional<float> _getCostByDate(std::string date);
	std::optional<float> _convertValue(std::string value);
	
	void _convertLine(std::string line);

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	BitcoinExchange(std::string dataBase);
	
	void convert(std::string input);

	class NoDataBaseException : public std::exception
	{
		const char *what() const noexcept override
		{
			return "Could open data base file.";
		} 
	};

	class EmptyDataBaseFileException : public std::exception
	{
		const char *what() const noexcept override
		{
			return "Empty data base file.";
		} 
	};
};


#endif