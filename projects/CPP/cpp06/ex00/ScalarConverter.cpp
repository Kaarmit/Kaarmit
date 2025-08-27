/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverterer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:08:18 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 15:26:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
    
}

ScalarConverter::ScalarConverter(const ScalarConverter &rhs)
{
    (void)rhs;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &rhs)
{
    (void)rhs;
    return *this;
}

ScalarConverter::~ScalarConverter()
{
    
}

const char* ScalarConverter::ConversionFailed::what() const throw() 
{
    return "Conversion failed";
}


bool   ScalarConverter::isCharLiteral(const std::string& input)
{
    if (input.size() != 1) 
        return false;
    unsigned char c = static_cast<unsigned char>(input[0]);
    return !std::isdigit(c);
}

bool    ScalarConverter::isPseudoFloat(const std::string& input)
{
    if (input == "nanf" || input == "+inff" || input == "-inff")
        return true;
    return false;
}
bool    ScalarConverter::isPseudoDouble(const std::string& input)
{
    if (input == "nan" || input == "+inf" || input == "-inf")
        return true;
    return false;
    
}


bool ScalarConverter::isFloatLiteral(const std::string& input)
{
    if (input.size() < 2) 
        return false;
    const std::size_t f = input.size() - 1;
    if (input[f] != 'f') 
        return false;

    int dot = 0;
    int digits = 0;

    for (std::size_t i = 0; i < f; i++) 
    {
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (i == 0 && (c == '+' || c == '-')) 
            continue;
        if (c == '.') 
        { 
            if (dot > 1)
                return false;
            dot++;
            continue;
        }
        if (std::isdigit(c)) 
        {
            digits++; 
            continue; 
        }
        return false;
    }
    return (dot == 1 && digits >= 1);
}



bool ScalarConverter::isDoubleLiteral(const std::string& input)
{
    if (input.empty())
        return false;

    int dot = 0;
    int digits = 0;

    for (std::size_t i = 0; i < input.size(); i++) 
    {
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (i == 0 && (c == '+' || c == '-')) 
            continue;
        if (c == '.') 
        { 
            if (dot > 1)
                return false;
            dot++;
            continue;
        }
        if (std::isdigit(c)) 
        {
            digits++; 
            continue; 
        }
        return false;
    }
    return (dot == 1 && digits >= 1);
}

#include <cctype>

bool ScalarConverter::isIntLiteral(const std::string& input)
{
    if (input.empty()) 
        return false;

    std::size_t i = 0;
    if (input[0] == '+' || input[0] == '-') 
    {
        if (input.size() == 1) 
            return false;
        i = 1;
    }

    int digits = 0;
    for (; i < input.size(); i++) 
    {
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (!std::isdigit(c)) 
            return false;
        digits++;
    }
    return digits >= 1;
}

ScalarConverter::Lit    ScalarConverter::detect(const std::string& input)
{
    if (isPseudoFloat(input))  
        return T_PSEUDO_F;
    if (isPseudoDouble(input)) 
        return T_PSEUDO_D;
    if (isCharLiteral(input))  
        return T_CHAR;
    if (isFloatLiteral(input)) 
        return T_FLOAT;
    if (isDoubleLiteral(input))
        return T_DOUBLE;
    if (isIntLiteral(input))   
        return T_INT;
    return T_INVALID;
}
void    ScalarConverter::convert(std::string input)
{
    
    Lit t = detect(input);
    
    switch (t)
    {
    case T_PSEUDO_F:
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        if (input == "nanf")
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        else if (input == "+inff")
        {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        }
        else if (input == "-inff")
        {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        
        
        break;
        
    case T_PSEUDO_D:
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        if (input == "nan")
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        else if (input == "+inf")
        {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        }
        else if (input == "-inf")
        {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        
        break;
    }
    
    case T_CHAR:
    {
        char c = input[0];
        
        if(!isprint(input[0]))
            std::cout << "char: non displayable" << std::endl;
        else
            std::cout << "char: " << c << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << std::endl;
        std::cout << "double: " << static_cast<double>(c) << std::endl;
        break;
    }
     
    case T_INT:
    {    
        char *end = 0;
        long i = std::strtol(input.c_str(), &end, 10);
        char c = static_cast<char>(i);

        //char
        if (c < 0 || c > 255)
            std::cout << "char: impossible" << std::endl;
        if (!isprint(c))
            std::cout << "char: non displayble" << std::endl;
        else
            std::cout << "char: " << c << std::endl;
        
        //int
        if (i < INT_MIN || i > INT_MIN)
            std::cout << "int: impossible" << std::endl;
        else 
            std::cout << "int: " << static_cast<int>(i) << std::endl;
            
        //float
        std::cout << "float: " << static_cast<float>(i) << std::endl;
        
        //double
        std::cout << "double: " << static_cast<double>(i) << std::endl;
        break;
    }
     
    case T_FLOAT:
    {
        char *end = 0;
        double val = std::strtod(input.c_str(), &end);
        float f = static_cast<float>(val);
        char c = static_cast<char>(f);
        int i = static_cast<int>(f);
        
        if (*end != '\0')
            std::cout << "Conversion failed" << std::endl;
        
        if (val > FLT_MAX || val < -FLT_MAX)
            std::cout << "Conversion failed" << std::endl;
        
        //char
        if (input == "nanf" || input == "+inff" || c < 0 || c > 255)
            std::cout << "char: impossible" << std::endl;
        if (!isprint(c))
            std::cout << "char: non displayble" << std::endl;
        else
            std::cout << c << std::endl;
        
        //int
        if (input == "nanf" || input == "+inff" || i < INT_MIN || i > INT_MAX)
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << i << std::endl;
        
        //float
        std::cout << f << std::endl;
        
        //double 
        std::cout << static_cast<double>(f) << std::endl;
    
        break;
    }
        
    case T_DOUBLE:
    {
        char* end = 0;
        double val = std::strtod(input.c_str(), &end);
    }
        break;
        
        
 
        
    default:
        break;
    }
    
}

/*
   std::stringstream abc("");
    int out;
    abc >> out;*/