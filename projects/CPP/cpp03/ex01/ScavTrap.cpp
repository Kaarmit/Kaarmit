/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:51:14 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/30 13:55:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("default Scav", 100, 50, 20)
{
    std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name, 100, 50, 20)
{
    std::cout << "ScavTrap full constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& rhs) : ClapTrap(rhs)
{
    std::cout << "ScavTrap copy constructor called" << std::endl;
    *this = rhs;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& rhs) 
{
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    if (this != &rhs)
    {
        _name = rhs._name;
        _hitPoints = rhs._hitPoints;
        _energyPoints = rhs._energyPoints;
        _attackDamage = rhs._attackDamage;
    }
    return *this;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap destructor called" << std::endl;
}

void    ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->_name << " has entered Gate Keeper mode" << std::endl;

}

void ScavTrap::attack(const std::string& target)
{
    if (this->_energyPoints < 1)
    {
        std::cout << "ScavTrap does not enough Energy to attack" << std::endl;
        return;
    }
    if (this->_hitPoints < 1)
    {
        std::cout << "ScavTrap does not enough Health to attack" << std::endl;
        return;
    }
    std::cout << target << " lost " << this->_attackDamage << " HP. Damage inflicted by ScavTrap " << this->_name << std::endl;
    return;
}