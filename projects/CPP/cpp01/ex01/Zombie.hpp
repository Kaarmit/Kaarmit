/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:58:18 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 14:10:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie
{
    
public:
    Zombie(void);
    ~Zombie(void);
    
    void    announce(void);
    void    setName(std::string name);
    
private:
    
    std::string    _name;
};

    Zombie* zombieHorde( int N, std::string name );

#endif

