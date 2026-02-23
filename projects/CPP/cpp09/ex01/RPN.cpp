#include "RPN.hpp"

RPN::RPN(std::string& input) : _input(input)
{
    
}

RPN::RPN(const RPN& other)
{
    (void)other;

}

RPN &RPN::operator=(const RPN & other)
{
    (void)other;
    return *this;
}

RPN::~RPN()
{
    
}
void    RPN::processInput()
{
    if (!isValidFormat(this->_input))
        throw std::invalid_argument("Not a polish notation format.");
    
    int res = 0;
    for(size_t i = 0; i < _input.size(); i++)
    {
        std::stringstream   ss(_input.substr(i, 1));
        int                 j;
        ss >> j;

        if (isdigit(_input[i]))
            this->_stack.push(j);
        else if (_input[i] == '+' || _input[i] == '-' || _input[i] == '*' || _input[i] == '/')
            this->applyOperator(_input[i]);
        else if (_input[i] == ' ')
            continue ;
        else
            throw std::invalid_argument("Invalid character in input");
        
        res = this->_stack.top();
    }
    std::cout << res << std::endl;
    return ;
}

bool    RPN::isValidFormat(const std::string &input) const
{
    if (input.empty())
        return false;
        
    for (size_t i = 0; i < input.size(); i++)
    {
        if (!isdigit(input[i]) && (input[i] != '+' && input[i] != '-' 
                && input[i] != '/' && input[i] != '*' && input[i] != ' '))
            return false;
            
        if (isdigit(input[i]) && i + 1 < input.size() && isdigit(input[i + 1]))
            return false;
    }
    
    char    last = input[input.length() - 1];
    if (last != '+' && last != '-' && last != '/' && last != '*')
        return false;
    
    return true;
}

void     RPN::applyOperator(char op)
{
    int n1 = this->_stack.top();
    this->_stack.pop();
    
    int n2 = this->_stack.top();
    this->_stack.pop();
    
    int res;
    
    if (op == '+')
        res = n2 + n1;
    else if (op == '-')
        res = n2 - n1;
    else if (op == '*')
        res = n2 * n1;
    else if (op == '/')
    {
        if (n1 == 0)
            throw std::runtime_error("Division by zero");
        res = n2 / n1;
    }
    
    this->_stack.push(res);
}
