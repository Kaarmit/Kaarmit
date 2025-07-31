/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:55:09 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 13:27:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    _brain = new Brain();
    type = "Dog";
    std::cout << "Dog default constructor called" << std::endl; 
}

Dog::Dog(const Dog& rhs) 
{
    _brain = new Brain(*rhs._brain);
    type = rhs.type;
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& rhs)
{
    if (this != &rhs)
    {
        this->type = rhs.type;
        delete _brain;
        this->_brain = new Brain(*rhs._brain);
    }
    return *this; 
}

Dog::~Dog()
{
    delete _brain;
    std::cout << "Dog destructor called" << std::endl;
}

void    Dog::makeSound() const
{
    std::cout << "*WOOF*" << std::endl;
}

Brain* Dog::getBrain() const
{
    return _brain;
}