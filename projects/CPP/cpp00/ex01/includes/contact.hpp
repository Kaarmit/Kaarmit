/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:39:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/19 13:09:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>
#include "phonebook.hpp"

class Contact{
    
public: 
    
    Contact(void);
    ~Contact(void);
    
    bool            Contact::setName(std::string input);
    bool            Contact::setSurname(std::string input);
    bool            Contact::setNickname(std::string input);
    bool            Contact::setPhoneNumber(std::string input);
    bool            Contact::setDarkestSecret(std::string input);
    
    std::string     Contact::getName();
    std::string     Contact::getSurname();
    std::string     Contact::getNickname();
    std::string     Contact::getPhoneNumber();
    std::string     Contact::getDarkestSecret();
    
    
private:
    
    std::string    _Name;
    std::string    _Surname;
    std::string    _Nickname;
    std::string    _Darkest_Secret;
    std::string    _Phone_Number;
};

#endif