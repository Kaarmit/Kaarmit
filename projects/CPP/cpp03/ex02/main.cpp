/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:07:23 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/30 13:48:46 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
    ClapTrap    Bobby;
    ScavTrap    Billy("Billy");
    FragTrap    Jean("Jean");
    
    Bobby.attack("Alex");
    Bobby.beRepaired(5);
    Bobby.takeDamage(10);
    Bobby.attack("Alex");
    Billy.attack("jose");
    Jean.attack("jose");
    Jean.highFivesGuys();
}