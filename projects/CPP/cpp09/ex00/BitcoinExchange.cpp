#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>  

BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
    loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _rates(other._rates)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _rates = other._rates;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

static bool isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    int year ;
    int month;
    int day;
    
    {
        std::istringstream ss(date.substr(0, 4));
        if (!(ss >> year))
            return false;
    }
    {
        std::istringstream ss(date.substr(5, 2));
        if (!(ss >> month))
            return false;
    }
    {
        std::istringstream ss(date.substr(8, 2));
        if (!(ss >> day))
            return false;
    }

    if (month < 1 || month > 12)
        return false;
    if (day < 1)
        return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year))
    {
        if (day > 29)
            return false;
    }
    else
    {
        if (day > daysInMonth[month - 1])
            return false;
    }
    return true;
}

bool BitcoinExchange::isValidNumber(const std::string &str, double &value)
{
    if (str.empty())
        return false;

    char *endPtr = 0;
    const char *cstr = str.c_str();
    value = std::strtod(cstr, &endPtr);

    if (*endPtr != '\0')
        return false;
    return true;
}

std::string BitcoinExchange::trim(const std::string &s)
{
    std::string::size_type start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
        start++;

    std::string::size_type end = s.size();
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
        end--;

    return s.substr(start, end - start);
}

void BitcoinExchange::loadDatabase(const std::string &dbFile)
{
    std::ifstream file(dbFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    if (!std::getline(file, line))
        return;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::string::size_type commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;

        std::string date = line.substr(0, commaPos);
        std::string valueStr = line.substr(commaPos + 1);

        date = trim(date);
        valueStr = trim(valueStr);

        if (!isValidDate(date))
            continue;

        double rate;
        if (!isValidNumber(valueStr, rate))
            continue;

        _rates[date] = rate;
    }
}

double BitcoinExchange::getRateForDate(const std::string &date) const
{
    if (_rates.empty())
        throw std::runtime_error("database is empty");

    std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);

    if (it != _rates.end() && it->first == date)
        return it->second;

    if (it == _rates.begin())
        throw std::runtime_error("no rate for this date");

    --it;
    return it->second;
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        if (firstLine)
        {
            firstLine = false;
            if (line.find("date") != std::string::npos && line.find("value") != std::string::npos)
                continue;
        }

        std::string originalLine = line;

        std::string::size_type pipePos = line.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << originalLine << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 1));

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << originalLine << std::endl;
            continue;
        }

        double value;
        if (!isValidNumber(valueStr, value))
        {
            std::cerr << "Error: bad input => " << originalLine << std::endl;
            continue;
        }

        if (value < 0.0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double rate;
        try
        {
            rate = getRateForDate(date);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: bad input => " << originalLine << std::endl;
            continue;
        }

        double result = value * rate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}
