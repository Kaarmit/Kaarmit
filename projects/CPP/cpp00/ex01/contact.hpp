/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:39:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 15:48:20 by aarmitan         ###   ########.fr       */
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
    
    bool    Contact::setName(std::string input);
    bool    Contact::setSurname(std::string input);
    bool    Contact::setNickname(std::string input);
    bool    Contact::setPhoneNumber(std::string input);
    bool    Contact::setDarkestSecret(std::string input);
    
    
private:
    
    std::string    _Name;
    std::string    _Surname;
    std::string    _Nickname;
    std::string    _Darkest_Secret;
    std::string    _Phone_Number;
};

int is_digit(const std::string &str);
int is_alpha(const std::string &str);

#endif