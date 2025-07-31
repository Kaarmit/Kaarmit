/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:38 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:23:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    type = "Cat";
    std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat& rhs)
{
    type = rhs.type;
    std::cout << "Cat copy constructor called" << std::endl;
}
Cat Cat::operator=(const Cat& rhs)
{
    std::cout << "Cat copy assignment constructor called";
    if (this != &rhs)
        this->type = rhs.type;
    return *this; 
}

Cat::~Cat()
{
    std::cout << "Cat destructor called" << std::endl;
}

void    Cat::makeSound() const
{
    std::cout << "*MEOWWW*" << std::endl;
}
