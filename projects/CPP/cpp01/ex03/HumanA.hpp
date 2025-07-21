/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:20:20 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 17:43:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class   HumanA
{

    public:
    
        HumanA(std::string str, Weapon& weapon);
        ~HumanA();
        
        void    attack();
              
    private:
    
        std::string _name;
        Weapon&      _weapon;
        
        
};

#endif