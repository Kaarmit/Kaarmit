/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:17:13 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/23 13:26:34 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon
{
    
public:
    Weapon(std::string type);
    ~Weapon();
    
    std::string const& getType() const;
    void setType(std::string str);
    
private:

    std::string  _type;
};

#endif