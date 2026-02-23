#include "BitcoinExchange.hpp"
#include <iostream>

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1;
    }
    
    
    try 
    {
        BitcoinExchange btc("data.csv");
        btc.processInput(argv[1]);
    } 
    catch (std::exception &e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}