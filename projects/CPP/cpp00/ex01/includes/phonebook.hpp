/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:45:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/19 13:35:07 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "contact.hpp"

class PhoneBook {
        
public:
    
  
    PhoneBook(void);
    ~PhoneBook(void);
    bool    addContact();
    void    displayAll();
    void    displayOne(int i);
    
private:

    Contact contacts[8];
    int _index;
    int _count;
    
    
};


#endif
