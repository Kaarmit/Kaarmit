/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:07:23 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/30 13:49:04 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
    ClapTrap    Bobby;
    ScavTrap    Jean("Jean");
    
    Bobby.attack("Alex");
    Bobby.beRepaired(5);
    Bobby.takeDamage(10);
    Bobby.attack("Alex");
    Jean.attack("Billy");
    Jean.guardGate();
}