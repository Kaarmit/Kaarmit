/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:40:31 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 13:26:31 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
    for (int i = 0; i < 100; ++i)
        _ideas[i] = "empty";
    std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& rhs)
{
    for (int i = 0; i < 100; ++i)
    _ideas[i] = rhs._ideas[i];
    std::cout << "Brain copy construcotr called" << std::endl;
}

Brain Brain::operator=(const Brain& rhs)
{
    if (this != &rhs) 
    {
    for (int i = 0; i < 100; ++i)
        _ideas[i] = rhs._ideas[i];
    }
return *this;

    std::cout << "Brain copy assignment called" << std::endl;
}

Brain::~Brain()
{
    std::cout << "Brain destructor called" << std::endl;
}

std::string Brain::getIdea(int index) const
{
    return _ideas[index];
}
void Brain::setIdea(int index, const std::string& idea)
{
    _ideas[index] = idea;
}