/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:51:53 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/04 12:21:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class AAnimal
{
    public:
    
        AAnimal();
        AAnimal(const AAnimal& rhs);
        AAnimal& operator=(const AAnimal& rhs);
        virtual ~AAnimal();
        
        virtual void    makeSound() const = 0;
        std::string     getType() const;
    
    protected:
    
        std::string type;
};

#endif