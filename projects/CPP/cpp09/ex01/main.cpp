#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: wrong number of arguments." << std::endl;
        return 1;
    }
    
    std::string input = argv[1];
    RPN rpn(input);
    
    try
    {
        rpn.processInput();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    
    return 0;
}