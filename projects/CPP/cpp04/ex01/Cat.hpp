/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:54:51 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 13:26:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"


class Cat : public Animal, public Brain
{
    public :
    
        Cat();
        Cat(const Cat& rhs);
        Cat& operator=(const Cat& rhs);
        ~Cat();
        
        virtual void    makeSound() const;
        Brain* getBrain() const;

    
    private :
        
        Brain*  _brain;
};


#endif