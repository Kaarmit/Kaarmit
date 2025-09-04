/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:38 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 13:27:30 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    _brain = new Brain();
    type = "Cat";
    std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat& rhs)
{
    _brain = new Brain(*rhs._brain);
    type = rhs.type;
    std::cout << "Cat copy constructor called" << std::endl;
}
Cat& Cat::operator=(const Cat& rhs)
{
    std::cout << "Cat copy assignment constructor called";
    if (this != &rhs)
    {
        this->type = rhs.type;
        delete _brain;
        this->_brain = new Brain(*rhs._brain);
    }
    return *this; 
}

Cat::~Cat()
{
    delete _brain;;
    std::cout << "Cat destructor called" << std::endl;
}

void    Cat::makeSound() const
{
    std::cout << "*MEOWWW*" << std::endl;
}

Brain* Cat::getBrain() const
{
    return _brain;
}
