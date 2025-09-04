/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:02:32 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/30 13:51:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("Default Scav", 100, 100, 30)
{
    std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name, 100, 100, 30)
{
    std::cout << "FragTrap full constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& rhs) : ClapTrap(rhs)
{
    std::cout << "FragTrap copy constructor called" << std::endl;
    *this = rhs;
}

FragTrap& FragTrap::operator=(const FragTrap& rhs) 
{
    std::cout << "FragTrap copy assignment operator called" << std::endl;
    if (this != &rhs)
    {
        _name = rhs._name;
        _hitPoints = rhs._hitPoints;
        _energyPoints = rhs._energyPoints;
        _attackDamage = rhs._attackDamage;
    }
    return *this;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap destructor called" << std::endl;
}

void    FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap " << this->_name << " says 'gimme five'" << std::endl;
}

void FragTrap::attack(const std::string& target)
{
    if (this->_energyPoints < 1)
    {
        std::cout << "FragTrap does not enough Energy to attack" << std::endl;
        return;
    }
    if (this->_hitPoints < 1)
    {
        std::cout << "FragTrap does not enough Health to attack" << std::endl;
        return;
    }
    std::cout << target << " lost " << this->_attackDamage << " HP. Damage inflicted by FragTrap " << this->_name << std::endl;
    return;
}