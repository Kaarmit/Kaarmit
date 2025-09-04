/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:01:33 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/04 12:22:21 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("ALIVE")
{
    std::cout << "Default animal constructor called" << std::endl;
}

Animal::Animal(const Animal& rhs) : type(rhs.type)
{
    std::cout << "Animal copy constructor called" << std::endl;
}
Animal Animal::operator=(const Animal& rhs)
{
    std::cout << "Animal copy assignment constructor called" << std::endl;
    if (this != &rhs)
        this->type = rhs.type;
    return *this;    
}

Animal::~Animal()
{
    std::cout << "Animal destructor called" << std::endl;
}

void    Animal::makeSound() const
{
    std::cout << "*...*" << std::endl;
}

std::string Animal::getType() const
{
    return this->type;
}