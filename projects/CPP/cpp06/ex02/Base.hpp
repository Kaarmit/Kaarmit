/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:08:20 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/28 15:57:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

class Base
{
    public:
    
        virtual ~Base();
            
    private:    
};

Base * generate(void);
void identify(Base* p);
void identify(Base& p);


#endif