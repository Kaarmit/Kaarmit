#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
    BitcoinExchange(const std::string &dbFile);
    ~BitcoinExchange();
   

    void processInput(const std::string &inputFile) const;

private:
    std::map<std::string, double> _rates;

    void loadDatabase(const std::string &dbFile);
    static bool isValidDate(const std::string &date);
    static bool isValidNumber(const std::string &str, double &value);
    static std::string trim(const std::string &s);
    double getRateForDate(const std::string &date) const;
    
     BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    
};

#endif