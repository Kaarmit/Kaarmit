/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:58:16 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 14:14:04 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void    Zombie::setName(std::string name)
{
    this->_name = name;
    std::cout << this->_name;
    std::cout << " is born";
    std::cout << std::endl;
}
Zombie::Zombie()
{
    
}
    
Zombie::~Zombie(void)
{
    std::cout << this->_name;
    std::cout << " died";
    std::cout << std::endl;
}
    
void    Zombie::announce(void)
{
    std::cout << this->_name;
    std::cout << ": BraiiiiiinnnzzzZ..." ;
    std::cout << std::endl;
}