/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:49:21 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/28 12:58:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _nb(0)
{
    //std::cout << "Default constructor called" << std::endl;
    
}

Fixed::Fixed(const int n) : _nb(n << _bits)
{
    //std::cout << "Int constructor called" << std::endl;
}


Fixed::Fixed(const float f) : _nb(roundf(f * (1 << _bits)))
{
    //std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& rhs) : _nb(rhs._nb)
{
    //std::cout << "Copy constructor called" << std::endl;
    //*this = rhs;
}

Fixed::~Fixed()
{
    //std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& rhs)
{
    //std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_nb = rhs._nb;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fixed& f)
{
    os << f.toFloat();
    return os;
}

bool Fixed::operator>(const Fixed& rhs) const
{
    return this->_nb > rhs._nb;
}

bool Fixed::operator<(const Fixed& rhs) const
{
    return this->_nb < rhs._nb;
}

bool Fixed::operator>=(const Fixed& rhs) const
{
    return this->_nb >= rhs._nb;
}

bool Fixed::operator<=(const Fixed& rhs) const
{
    return this->_nb <= rhs._nb;
}

bool Fixed::operator==(const Fixed& rhs) const
{
    return this->_nb == rhs._nb;
}

bool Fixed::operator!=(const Fixed& rhs) const
{
    return this->_nb != rhs._nb;
}
    
Fixed Fixed::operator+(const Fixed& rhs) const
{
    return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(const Fixed& rhs) const
{
    return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(const Fixed& rhs) const
{
    return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed& rhs) const
{
    return Fixed(this->toFloat() / rhs.toFloat());
}

Fixed& Fixed::operator++()
{
    ++this->_nb;
    return *this;
}

Fixed& Fixed::operator--()
{
    --this->_nb;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);
    ++this->_nb;
    return (tmp);
}

Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    --this->_nb;
    return (tmp);
}
    
int     Fixed::getRawBits(void) const
{
    //std::cout << "getRawBits member function called" << std::endl;
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

Fixed&        Fixed::min(Fixed& a, Fixed& b)
{
    return (a < b) ? a : b;
    /*if (a < b)
        return a;
      else
        return b;*/
}
const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b) ? a : b;
}

Fixed&  Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b) ? a : b;
}