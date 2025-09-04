/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:58:18 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/23 13:15:02 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie
{
    
public:
    Zombie(std::string name);
    ~Zombie(void);
    
    void    announce(void);
    
private:
    
    std::string    _name;
};

    void _randomChump(std::string name);
    Zombie *_newZombie(std::string name);

#endif

