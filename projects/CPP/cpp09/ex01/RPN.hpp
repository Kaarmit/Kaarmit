#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <list>

class RPN
{
    public:
        RPN(std::string& input);
        ~RPN();

        void    processInput();

    private:
        std::string const       _input;
        std::stack<int, std::list<int> > _stack;

        bool    isValidFormat(const std::string &) const;
        void     applyOperator(char op);

        RPN(const RPN& other);
        RPN &operator=(const RPN & other);
};

#endif