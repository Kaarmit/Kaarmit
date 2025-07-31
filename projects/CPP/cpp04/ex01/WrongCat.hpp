/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:57:21 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:22:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"


class WrongCat : public WrongAnimal
{
    public :
    
        WrongCat();
        WrongCat(const WrongCat& rhs);
        WrongCat operator=(const WrongCat& rhs);
        ~WrongCat();
        
        void    makeSound() const;
        
};


#endif