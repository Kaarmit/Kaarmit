/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:08:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/30 13:34:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
    public:
    
        ClapTrap();
        ClapTrap(std::string name, int hp, int energy, int damage);
        ClapTrap(const ClapTrap& rhs);
        ClapTrap& operator=(const ClapTrap& rhs);
        ~ClapTrap();
    
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
    
    protected:
    
        std::string    _name;
        int            _hitPoints;
        int            _energyPoints;
        int            _attackDamage;
};

#endif