/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:55:09 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:23:02 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    type = "Dog";
    std::cout << "Dog default constructor called" << std::endl; 
}

Dog::Dog(const Dog& rhs) 
{
    type = rhs.type;
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog Dog::operator=(const Dog& rhs)
{
    std::cout << "Dog copy assignment constructor called";
    if (this != &rhs)
        this->type = rhs.type;
    return *this; 
}

Dog::~Dog()
{
    std::cout << "Dog destructor called" << std::endl;
}

void    Dog::makeSound() const
{
    std::cout << "*WOOF*" << std::endl;
}