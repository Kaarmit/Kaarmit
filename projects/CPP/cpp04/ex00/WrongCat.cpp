/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:58:01 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:22:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    type = "Cat";
    std::cout << "Cat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& rhs)
{
    type = rhs.type;
    std::cout << "WrongCat copy constructor called" << std::endl;
}
WrongCat WrongCat::operator=(const WrongCat& rhs)
{
    std::cout << "WrongCat copy assignment constructor called";
    if (this != &rhs)
        this->type = rhs.type;
    return *this; 
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructor called" << std::endl;
}

void    WrongCat::makeSound() const
{
    std::cout << "*MEOWWW*" << std::endl;
}