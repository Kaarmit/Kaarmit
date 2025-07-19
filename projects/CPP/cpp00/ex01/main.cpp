/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:27:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/19 14:23:29 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"
#include "phonebook.hpp"

int main(void) 
{
    PhoneBook   directory;
    std::string input;
    int index;
    
    while (true) 
    {
        std::cout << "> ";
        if (!std::getline(std::cin, input)){
            if(std::cin.eof())
                return 0;
            return 1;
        }
        if (input == "ADD" || input == "add")
            directory.addContact();
                
        else if (input == "SEARCH" || input == "search")
        {
            directory.displayAll();
            if (!std::getline(std::cin, input)){
                if(std::cin.eof())
                    return 0;
                return 1;
            }
            std::stringstream ss(input);
            if (!(ss >> index) || !(ss.eof()))
                return 1;
            if (index < 0 || index >= directory.getCount())
                return 1;
            directory.displayOne(index);
        }
        else if (input == "EXIT" || input == "exit")
            return 0;
    }
}