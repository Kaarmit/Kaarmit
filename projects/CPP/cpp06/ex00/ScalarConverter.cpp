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
    return (digits >= 1);
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

static inline void printFloatFinite(float f)
{
    // Toujours une décimale + suffixe f
    std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
}

static inline void printDoubleFinite(double d)
{
    // Toujours une décimale
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

void ScalarConverter::convert(std::string input)
{
    Lit t = detect(input);

    switch (t)
    {
    case T_PSEUDO_F:
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        if (input == "nanf") {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        } else if (input == "+inff") {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        } else { // -inff
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        break;

    case T_PSEUDO_D:
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        if (input == "nan") {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        } else if (input == "+inf") {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        } else { // -inf
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        break;

    case T_CHAR:
    {
        char c = input[0];
        unsigned char uc = static_cast<unsigned char>(c);

        // char
        if (!std::isprint(uc))
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << c << "'" << std::endl;

        // int
        std::cout << "int: " << static_cast<int>(c) << std::endl;

        // float
        printFloatFinite(static_cast<float>(c));

        // double
        printDoubleFinite(static_cast<double>(c));
        break;
    }

    case T_INT:
    {
        errno = 0;
        char* end = 0;
        long l = std::strtol(input.c_str(), &end, 10);

        // consommation totale + borne int
        if (*end != '\0' || errno == ERANGE || l < INT_MIN || l > INT_MAX) {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
            break;
        }

        int i = static_cast<int>(l);

        // char
        if (i < 0 || i > 127) {
            std::cout << "char: impossible" << std::endl;
        } else {
            unsigned char c = static_cast<unsigned char>(i);
            if (!std::isprint(c))
                std::cout << "char: Non displayable" << std::endl;
            else
                std::cout << "char: '" << static_cast<char>(c) << "'" << std::endl;
        }

        // int
        std::cout << "int: " << i << std::endl;

        // float
        printFloatFinite(static_cast<float>(i));

        // double
        printDoubleFinite(static_cast<double>(i));
        break;
    }

case T_FLOAT:
{
    std::string core = input.substr(0, input.size() - 1);

    errno = 0;
    char* end = 0;
    double d = std::strtod(core.c_str(), &end);
    if (*end != '\0' || errno == ERANGE) 
    {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
        break;
    }

    // char
    if (std::isnan(d) || std::isinf(d) || d < 0.0 || d > 127.0) 
    {
        std::cout << "char: impossible\n";
    } else 
    {
        char c = static_cast<char>(static_cast<int>(d));
        if (!std::isprint(static_cast<unsigned char>(c)))
            std::cout << "char: Non displayable\n";
        else
            std::cout << "char: '" << c << "'\n";
    }

    // int
    if (std::isnan(d) || std::isinf(d) || d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX))
        std::cout << "int: impossible\n";
    else
        std::cout << "int: " << static_cast<int>(d) << "\n";

    // float
    if (std::isnan(d)) {
        std::cout << "float: nanf\n";
    } else if (std::isinf(d)) {
        std::cout << "float: " << (d > 0.0 ? "+inff\n" : "-inff\n");
    } else if (d > static_cast<double>(std::numeric_limits<float>::max())) {
        std::cout << "float: +inff\n";
    } else if (d < -static_cast<double>(std::numeric_limits<float>::max())) {
        std::cout << "float: -inff\n";
    } else {
        float f = static_cast<float>(d);
        printFloatFinite(f);
    }

    // double
    printDoubleFinite(d);
    break;
}

    case T_DOUBLE:
    {
        errno = 0;
        char* end = 0;
        double d = std::strtod(input.c_str(), &end);
        if (*end != '\0' || errno == ERANGE || d > std::numeric_limits<double>::max() || d < -std::numeric_limits<double>::max()) 
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
            break;
        }

        // char
        if (std::isnan(d) || std::isinf(d)) {
            std::cout << "char: impossible" << std::endl;
        } 
        else 
        {
            long l = static_cast<long>(d);
            if (l < 0 || l > 127) {
                std::cout << "char: impossible" << std::endl;
            } else {
                unsigned char c = static_cast<unsigned char>(l);
                if (!std::isprint(c))
                    std::cout << "char: Non displayable" << std::endl;
                else
                    std::cout << "char: '" << static_cast<char>(c) << "'" << std::endl;
            }
        }

        // int
        if (std::isnan(d) || std::isinf(d) || d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX))
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(d) << std::endl;

        // float (double -> float MANQUANT, ajouté)
        if (std::isnan(d)) {
            std::cout << "float: nanf" << std::endl;
        } else if (std::isinf(d)) {
            std::cout << "float: " << (d > 0 ? "+inff" : "-inff") << std::endl;
        } else if (d > static_cast<double>(FLT_MAX)) {
            std::cout << "float: +inff" << std::endl;
        } else if (d < -static_cast<double>(FLT_MAX)) {
            std::cout << "float: -inff" << std::endl;
        } else {
            float f = static_cast<float>(d);
            printFloatFinite(f);
        }

        // double
        printDoubleFinite(d);
        break;
    }

    default:
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        break;
    }
}

    

/*
   std::stringstream abc("");
    int out;
    abc >> out;*/