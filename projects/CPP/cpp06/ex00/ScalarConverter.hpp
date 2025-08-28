/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter
.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:08:28 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 15:27:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include <cmath>

class ScalarConverter

{
    public:
    
    class ConversionFailed : public std::exception 
    {
      public:
        virtual const char* what() const throw();
    };
    
    enum Lit 
    { 
        T_PSEUDO_F, 
        T_PSEUDO_D,
        T_CHAR, 
        T_INT, 
        T_FLOAT, 
        T_DOUBLE,
        T_INVALID 
    };

           
    static bool            isCharLiteral(const std::string& input);
    static bool            isPseudoFloat(const std::string& input);
    static bool            isPseudoDouble(const std::string& input);
    static bool            isFloatLiteral(const std::string& input);
    static bool            isDoubleLiteral(const std::string& input);
    static bool            isIntLiteral(const std::string& input);
    static Lit             detect(const std::string& input);
    static void            convert(std::string input);
    
    
    
    private:
    
    ScalarConverter();
    ScalarConverter(const ScalarConverter &rhs);
    ScalarConverter& operator=(const ScalarConverter &rhs);
    virtual ~ScalarConverter();
    
    

};





#endif