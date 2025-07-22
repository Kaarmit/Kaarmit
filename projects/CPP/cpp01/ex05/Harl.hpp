/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:39:15 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/22 14:21:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP
#include <iostream>
#include <string>

class Harl
{
  public:
  
    Harl();
    ~Harl();
  
    void    complain(std::string level);
    
  private:
  
    void _debug( void );
    void _info( void );
    void _warning( void );
    void _error( void );
};


#endif