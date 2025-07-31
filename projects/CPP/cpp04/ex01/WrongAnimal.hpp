/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:56:51 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:22:50 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal
{
    public:
    
        WrongAnimal();
        WrongAnimal(const WrongAnimal& rhs);
        WrongAnimal operator=(const WrongAnimal& rhs);
        ~WrongAnimal();
        
        void    makeSound() const;
        std::string     getType() const;
    
    protected:
    
        std::string type;
};

#endif