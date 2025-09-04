/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:49:13 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/28 12:48:00 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <math.h>

class Fixed
{

public:

    Fixed();
    Fixed(const int n);
    Fixed(const float f);
    Fixed(const Fixed& rhs);
    ~Fixed();
    
    Fixed&              operator=(const Fixed& rhs);
        
    bool                operator>(const Fixed& rhs) const;
    bool                operator<(const Fixed& rhs) const;
    bool                operator>=(const Fixed& rhs) const;
    bool                operator<=(const Fixed& rhs) const;
    bool                operator==(const Fixed& rhs) const;
    bool                operator!=(const Fixed& rhs) const;
        
    Fixed               operator+(const Fixed& rhs) const;
    Fixed               operator-(const Fixed& rhs) const;
    Fixed               operator*(const Fixed& rhs) const;
    Fixed               operator/(const Fixed& rhs) const;
        
    Fixed&              operator++();
    Fixed&              operator--();
    Fixed               operator++(int);
    Fixed               operator--(int);
        
        
    int                 getRawBits(void) const;
    void                setRawBits(int const raw);
    float               toFloat(void) const;
    int                 toInt(void) const;
    
    static Fixed&       min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed&       max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
    
private:
    
    int                 _nb;
    static int const    _bits = 8;
    
};

std::ostream& operator<<(std::ostream& os, const Fixed& f);

#endif