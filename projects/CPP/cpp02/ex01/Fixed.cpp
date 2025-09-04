/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:49:21 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/28 11:36:47 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _nb(0)
{
    std::cout << "Default constructor called" << std::endl;
    
}

Fixed::Fixed(const int n) : _nb(n << _bits)
{
    std::cout << "Int constructor called" << std::endl;
}


Fixed::Fixed(const float f) : _nb(roundf(f * (1 << _bits)))
{
    std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& rhs) : _nb(rhs._nb)
{
    std::cout << "Copy constructor called" << std::endl;
    //*this = rhs;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& rhs)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_nb = rhs._nb;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fixed& f)
{
    os << f.toFloat();
    return os;
}


int     Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->_nb;
}

void    Fixed::setRawBits(int const raw)
{
        this->_nb = raw;
}

float   Fixed::toFloat(void) const
{
    return static_cast<float>(_nb) / (1 << _bits);
}

int     Fixed::toInt(void) const
{
        return _nb >> _bits;
}