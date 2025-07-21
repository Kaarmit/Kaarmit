/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:58:47 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 18:05:47 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class   HumanB
{

    public:
    
        HumanB(std::string str);
        ~HumanB();
        
        void    attack();
        void    setWeapon(Weapon &weapon);
              
    private:
    
        std::string _name;
        Weapon*      _weapon;
        
        
};

#endif