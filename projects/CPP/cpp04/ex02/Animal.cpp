/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:01:33 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/04 12:21:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

AAnimal::AAnimal() : type("ALIVE")
{
    std::cout << "Default animal constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& rhs) : type(rhs.type)
{
    std::cout << "Animal copy constructor called" << std::endl;
}
AAnimal& AAnimal::operator=(const AAnimal& rhs)
{
    std::cout << "Animal copy assignment constructor called" << std::endl;
    if (this != &rhs)
        this->type = rhs.type;
    return *this;    
}

AAnimal::~AAnimal()
{
    std::cout << "Animal destructor called" << std::endl;
}

void    AAnimal::makeSound() const
{
    std::cout << "*...*" << std::endl;
}

std::string AAnimal::getType() const
{
    return this->type;
}