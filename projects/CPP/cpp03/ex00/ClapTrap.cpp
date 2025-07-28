/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:07:34 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/28 15:08:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name(""), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "Default ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
    std::cout << "Name ClapTrap constructor called" << std::endl;
    this->_name = name;
}

ClapTrap::ClapTrap(const ClapTrap& rhs)  : _name(rhs._name), _hitPoints(rhs._hitPoints),
      _energyPoints(rhs._energyPoints), _attackDamage(rhs._attackDamage)
{
    std::cout << "ClaTrap copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& rhs)
{
    std::cout << "Copy assignement operator called" << std::endl;
     if (this != &rhs)
    {
        _name = rhs._name;
        _hitPoints = rhs._hitPoints;
        _energyPoints = rhs._energyPoints;
        _attackDamage = rhs._attackDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap desctructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->_energyPoints < 1)
    {
        std::cout << "not enough Energy to attack" << std::endl;
        return;
    }
    if (this->_hitPoints < 1)
    {
        std::cout << "not enough Health to attack" << std::endl;
        return;
    }
    std::cout << target << " lost " << this->_attackDamage << " HP" << std::endl;
    return;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    this->_hitPoints -= amount;
    std::cout << "ClapTrap lost " << amount << " HP. " << this->_hitPoints << " HP remaining." << std::endl;
    return;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_energyPoints < 1)
    {
        std::cout << "not enough Energy to repair" << std::endl;
        return;
    }
    if (this->_hitPoints < 1)
    {
        std::cout << "not enough Health to repair" << std::endl;
        return;
    }
    this->_hitPoints += amount;
    this->_energyPoints -= 1;
    std::cout << "ClapTrap repaired recovered " << amount << " HP. " << this->_hitPoints << " HP remaining.";
    std::cout << " Cost of healing is 1 energy point. " <<  this->_energyPoints << " energy remaing" << std::endl;
    return;
}
