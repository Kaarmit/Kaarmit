/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:44:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/22 14:21:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
        
}

Harl::~Harl()
{
        
}

void Harl::_debug( void )
{
    std::cout << "DEBUG: ";
    std::cout << "I love having extra bacon for my ";
    std::cout << "7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!";
    std::cout << std::endl;
}
    
void Harl::_info( void )
{
    std::cout << "INFO: ";
    std::cout << "I cannot believe adding extra bacon costs more money. You didn't put ";
    std::cout << "enough bacon in my burger! If you did, I wouldn't be asking for more!";
    std::cout << std::endl;
}
    
    
void Harl::_warning( void )
{
    std::cout << "WARNING: ";
    std::cout << "I think I deserve to have some extra bacon for free. I've been coming for ";
    std::cout << "years, whereas you started working here just last month.";
    std::cout << std::endl;
}
    
void Harl::_error( void )
{
    std::cout << "ERROR: ";
    std::cout << "This is unacceptable! I want to speak to the manager now.";
    std::cout << std::endl;
}
   
void    Harl::complain(std::string level)
{
    typedef void   (Harl::*ptrToFunc)();
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    ptrToFunc   ptr[] = {&Harl::_debug, &Harl::_info, &Harl::_warning, &Harl::_error};
      
    for (int i = 0; i < 4; i++)
    {
        if (level == levels[i])
            (this->*ptr[i])();
    }
}
    