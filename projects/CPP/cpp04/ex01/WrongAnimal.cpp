/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:56:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:25:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("ALIVE")
{
    std::cout << "Default WrongAnimal constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& rhs) : type(rhs.type)
{
    std::cout << "WrongAnimal copy constructor called" << std::endl;
}
WrongAnimal WrongAnimal::operator=(const WrongAnimal& rhs)
{
    std::cout << "WrongAnimal copy assignment constructor called";
    if (this != &rhs)
        this->type = rhs.type;
    return *this;    
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal destructor called" << std::endl;
}

void    WrongAnimal::makeSound() const
{
    std::cout << "*FORBIDDEN NOISE*" << std::endl;
}

std::string WrongAnimal::getType() const
{
    return this->type;
}