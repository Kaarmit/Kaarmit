/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:27:45 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 18:31:06 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string str, Weapon& weapon) : _weapon(weapon)
{
        _name = str;
}
HumanA::~HumanA()
{
                
}
        
void    HumanA::attack()
{
        std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;    
}