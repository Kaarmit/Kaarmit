#include <cstddef>
#include <iostream>
#include <string>
#include <limits.h>
#include "PmergeMe.hpp"


long parse_long(std::string const& s)
{
    long result = 0;
    for (size_t i = 0; i < s.size(); ++i)
        result = result * 10 + (s[i] - '0');
    return result;
}


int validate(std::string arg)
{
    if (arg.empty())
        return -1;

    for (size_t i = 0; i < arg.size(); i++)
        if (!isdigit(arg[i]))
            return -1;

    if (arg.length() > 10)
        return -1;
    if (arg.length() == 10)
        if (arg > "2147483647")
            return -1;

    long n = parse_long(arg);

    if (n == 0)
        return -1;

    return static_cast<int>(n);
}




int main(int argc, char **argv)
{
    PmergeMe obj;

    if (argc <= 1)
    {
       std::cerr << "Error: Not enough arguments" << std::endl;
       return -1;
    }
       
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        int n;
            
        n = validate(arg);
            
        if (n < 0)
        {
            std::cerr << "Error: Invalid character in input" << std::endl;
            return -1;
        }
        obj.addNumber(n);
    }
    std::cout << "Vector before sorting : " << std::endl;
    std::cout << obj.getVector() << std::endl;
    std::cout << std::endl;
    
    std::cout << "Deque before sorting : " << std::endl;
    std::cout << obj.getDeque() << std::endl;
    std::cout << std::endl;
    
    clock_t startVec = clock();
    obj.sortVector();
    clock_t endVec = clock();
    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
    
    clock_t startDeq = clock();
    obj.sortDeque();
    clock_t endDeq = clock();
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;
    
    
    std::cout << "Vector after sorting : " << std::endl;
    std::cout << obj.getVector() << std::endl;
    std::cout << "Time to sort vector: " << timeVec << std::endl;
    std::cout << std::endl;
    
    std::cout << "Deque after sorting : " << std::endl;
    std::cout << obj.getDeque() << std::endl;
    std::cout << "Time to sort deque: " << timeDeq << std::endl;
    std::cout << std::endl;
    
    return 0;
}
    

