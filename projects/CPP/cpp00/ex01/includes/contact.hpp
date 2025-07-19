/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:39:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/19 14:19:29 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>

class Contact{
    
public: 
    
    Contact(void);
    ~Contact(void);
    
    bool            setName(std::string input);
    bool            setSurname(std::string input);
    bool            setNickname(std::string input);
    bool            setPhoneNumber(std::string input);
    bool            setDarkestSecret(std::string input);
    
    std::string     getName();
    std::string     getSurname();
    std::string     getNickname();
    std::string     getPhoneNumber();
    std::string     getDarkestSecret();
    
    
private:
    
    std::string    _Name;
    std::string    _Surname;
    std::string    _Nickname;
    std::string    _Darkest_Secret;
    std::string    _Phone_Number;
};

#endif