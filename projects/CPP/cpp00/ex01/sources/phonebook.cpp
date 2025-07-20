/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:24:11 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/20 14:33:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phonebook.hpp"

PhoneBook::PhoneBook(void) : _index(0), _count(0)
{
    //std::cout << "Constructor called" << std::endl;
    return;
}

PhoneBook::~PhoneBook(void)
{
    //std::cout << "Destructor called" << std::endl;
    return;
}

std::string truncate(const std::string& str) 
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void    drawLine(void)
{
    std::cout << "+";
    for (int i = 0; i < 4; i++){
        std::cout << "----------+";
    }
        
}

int PhoneBook::getCount() const 
{
    return this->_count;
}

bool PhoneBook::promptAndSetField(const std::string& prompt, bool (Contact::*setter)(std::string)) 
{
    std::string input;
    bool valid = false;

    do {
        std::cout << prompt;
        if (!std::getline(std::cin, input))
            return false;
        valid = (this->contacts[this->_index].*setter)(input);
        if (!valid)
        {
            std::cout << "Invalid input. Can't be blank ";
            std::cout << "Name/Surname are letters only. Phone number is 10 digits ";
            std::cout << "Please try again.";
            std::cout<< std::endl;
        }
    } while (!valid);
    return true;
}

bool    PhoneBook::addContact()
{
    std::string input;
   
    if (!promptAndSetField("First Name: ", &Contact::setName)) 
        return false;
    if (!promptAndSetField("Last Name: ", &Contact::setSurname)) 
        return false;   
    if (!promptAndSetField("Nickname: ", &Contact::setNickname)) 
        return false;   
    if (!promptAndSetField("Phone Number: ", &Contact::setPhoneNumber)) 
        return false;
    if (!promptAndSetField("Darkest secret: ", &Contact::setDarkestSecret)) 
        return false;    
    this->_index = (this->_index + 1) % 8;
    if (_count < 8)
        _count++;
    return true;
}

// bool    PhoneBook::addContact()
// {
//     std::string input;      
//     bool valid = false;

//     do {
//         std::cout << "First Name: ";
//         if (!std::getline(std::cin, input))
//             return false;
//         valid = this->contacts[this->_index].setName(input);
//         if (!valid)
//             std::cout << "A name is composed of letters only" << std::endl;
//     } while (!valid);
//     valid = false;
                
//     do  {
//         std::cout << "Last Name: ";
//         if (!std::getline(std::cin, input))
//             return false;
//         valid = this->contacts[this->_index].setSurname(input);
//         if (!valid)
//             std::cout << "A surname is composed of letters only" << std::endl;
//     } while (!valid);
//         valid = false;
            
//     std::cout << "Nickname: ";
//     if (!std::getline(std::cin, input))
//             return false;
//     if (!this->contacts[this->_index].setNickname(input))
//         return false;
    
//     do  {
//         std::cout << "Phone Number: ";
//         if (!std::getline(std::cin, input))
//             return false;
//         valid = this->contacts[this->_index].setPhoneNumber(input);
//         if (!valid)
//             std::cout << "A phone number is composed of 10 digits" << std::endl;
//     } while (!valid);
     
//     std::cout << "Darkest secret: ";
//     if (!std::getline(std::cin, input))
//             return false;
//     if (!this->contacts[this->_index].setDarkestSecret(input))
//         return false;
            
//     this->_index = (this->_index + 1) % 8;
//     if (_count < 8)
//         _count++;
//     return true;
// }

void    PhoneBook::displayAll()
{
    
    #if defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
    drawLine();
    std::cout << std::endl;
    std::cout << "|";
    std::cout << std::right << std::setw(10) << "Index" << "|";
    std::cout << std::right << std::setw(10) << "First Name" <<  "|";
    std::cout << std::right << std::setw(10) << "Last Name" << "|";
    std::cout << std::right << std::setw(10) << "Nickname" << "|" << std::endl;
    drawLine();
    std::cout << std::endl;
        
    for (int i = 0; i < _count; i++)
    {
        std::cout << "|";
        std::cout << std::right << std::setw(10) << i << "|";
        std::cout << std::right << std::setw(10) << truncate(contacts[i].getName()) << "|";
        std::cout << std::right << std::setw(10) << truncate(contacts[i].getSurname()) << "|";
        std::cout << std::right << std::setw(10) << truncate(contacts[i].getNickname()) << "|";
        std::cout << std::endl;
        drawLine();
        std::cout << std::endl;
    }
    std::cout << "> ";
}

void    PhoneBook::displayOne(int index)
{
    std::cout << std::endl;
    std::cout << "First Name:     "     << contacts[index].getName() << std::endl;
    std::cout << "Last Name:      "      << contacts[index].getSurname() << std::endl;
    std::cout << "Nickname:       "       << contacts[index].getNickname() << std::endl;
    std::cout << "Phone Number:   "   << contacts[index].getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contacts[index].getDarkestSecret() << std::endl;
    std::cout << std::endl;
}
