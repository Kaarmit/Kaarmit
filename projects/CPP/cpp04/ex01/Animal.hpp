/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:51:53 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 14:11:22 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
    public:
    
        Animal();
        Animal(const Animal& rhs);
        Animal operator=(const Animal& rhs);
        virtual ~Animal();
        
        virtual void    makeSound() const;
        std::string     getType() const;
    
    protected:
    
        std::string type;
};

#endif