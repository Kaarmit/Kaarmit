/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:55:21 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:22:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
    public : 
        Dog();
        Dog(const Dog& rhs);
        Dog operator=(const Dog& rhs);
        ~Dog();
        
        virtual void    makeSound() const;
};

#endif