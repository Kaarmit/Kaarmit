/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:47:32 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/20 12:33:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/contact.hpp"

Contact::Contact(void) 
{
    //std::cout << "Constructor called" << std::endl;
    return;
}

Contact::~Contact(void)
{
   // std::cout << "Destructor called" << std::endl;
    return;   
}

int is_alpha(const std::string &str)
{
    if (str.empty())
        return 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
            return 0;
    }
    return 1;
}

int is_digit(const std::string &str)
{
    if (str.empty())
        return 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        int d = str[i];
        if ((d < '0' || d > '9'))
            return 0;
    }
    return 1;
}
bool   Contact::setName(std::string input){
    
    if (input.empty())
        return false;
    if (!is_alpha(input))
        return false;
    this->_Name = input;
    return true;
}

bool    Contact::setSurname(std::string input){
    
    if (input.empty())
        return false;
    if (!is_alpha(input))
        return false;
    this->_Surname = input;
    return true;
}

bool    Contact::setNickname(std::string input){
    
    if (input.empty())
        return false;
    this->_Nickname = input;
    return true;
}

bool    Contact::setPhoneNumber(std::string input){
    
    if (input.empty())
        return false;
    if (!is_digit(input))
        return false;
    if (input.length() != 10)
        return false;
    this->_Phone_Number = input;
    return true;
    
}

bool   Contact::setDarkestSecret(std::string input){
    
    if (input.empty())
        return false;
    this->_Darkest_Secret = input;
    return true;
}


std::string    Contact::getName(){
        
    if(this->_Name.empty())
        return "N/A";
    return this->_Name;      
}
    
std::string    Contact::getSurname(){
        
    if(this->_Surname.empty())
        return "N/A";
    return this->_Surname;
}
    
std::string    Contact::getNickname(){
        
    if(this->_Nickname.empty())
        return "N/A";
    return this->_Nickname; 
}
    
std::string    Contact::getPhoneNumber(){
        
    if(this->_Phone_Number.empty())
        return "N/A";
    return this->_Phone_Number; 
}

std::string    Contact::getDarkestSecret(){
        
    if(this->_Name.empty())
        return "N/A";
    return this->_Darkest_Secret; 
}
