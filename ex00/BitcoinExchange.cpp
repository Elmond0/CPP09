#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// ----- small parsing helpers ------------------------------------------------

// Trims spaces and tabs from both ends of a string (in place via copy).
static std::string trim(const std::string& s)
{
	std::string::size_type start = s.find_first_not_of(" \t");
	if (start == std::string::npos)
		return "";
	std::string::size_type end = s.find_last_not_of(" \t");
	return s.substr(start, end - start + 1);
}

// Checks that every character in [begin, end) of s is a digit.
static bool allDigits(const std::string& s, size_t begin, size_t end)
{
	for (size_t i = begin; i < end; ++i)
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return false;
	return true;
}

// True for years divisible by 4, except centuries that aren't divisible by 400.
static bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const std::string& date)
{
	// Expected layout: YYYY-MM-DD (exactly 10 characters).
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	if (!allDigits(date, 0, 4) || !allDigits(date, 5, 7) || !allDigits(date, 8, 10))
		return false;

	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12 || day < 1)
		return false;

	// Reject impossible days like 2011-02-31, accounting for leap years.
	const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && isLeapYear(year))
		maxDay = 29;
	return day <= maxDay;
}

bool parseValue(const std::string& str, float& out)
{
	if (str.empty())
		return false;

	// Reject anything that is not a plain number (no extra characters, no
	// thousands separators, no trailing letters). strtod handles the parse,
	// then we make sure it consumed the whole string.
	char* end = 0;
	double value = std::strtod(str.c_str(), &end);
	if (*end != '\0')
		return false;

	out = static_cast<float>(value);
	return true;
}

// ----- database -------------------------------------------------------------

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database file.");

	std::string line;
	std::getline(file, line); // skip the "date,exchange_rate" header

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		std::string date = trim(line.substr(0, comma));
		std::string rate = trim(line.substr(comma + 1));
		_rates[date] = static_cast<float>(std::atof(rate.c_str()));
	}

	if (_rates.empty())
		throw std::runtime_error("database is empty.");
}

float BitcoinExchange::getRate(const std::string& date) const
{
	// lower_bound gives the first entry >= date.
	std::map<std::string, float>::const_iterator it = _rates.lower_bound(date);

	// Exact match.
	if (it != _rates.end() && it->first == date)
		return it->second;

	// Otherwise we need the closest *earlier* date: step back one.
	if (it == _rates.begin())
		throw std::out_of_range("no earlier date in database.");
	--it;
	return it->second;
}

// ----- input processing -----------------------------------------------------

void BitcoinExchange::processInput(const std::string& path) const
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file.");

	std::string line;
	std::getline(file, line); // skip the "date | value" header

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::string::size_type bar = line.find('|');
		if (bar == std::string::npos)
		{
			std::cout << "Error: bad input => " << trim(line) << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, bar));
		std::string rawValue = trim(line.substr(bar + 1));

		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}

		float value;
		if (!parseValue(rawValue, value))
		{
			std::cout << "Error: bad input => " << rawValue << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		try
		{
			float rate = getRate(date);
			std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: no data for date => " << date << std::endl;
		}
	}
}
