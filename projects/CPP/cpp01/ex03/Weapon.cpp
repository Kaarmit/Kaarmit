/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:19:49 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 18:21:55 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string str) : _type(str)
{
    
}

Weapon::~Weapon()
{
}

std::string const& Weapon::getType() const
{
    return (_type);
}
    
void    Weapon::setType(std::string type)
{
        _type = type;
}