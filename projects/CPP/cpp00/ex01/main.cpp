/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:27:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 15:51:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"
#include "phonebook.hpp"

int main(void) 
{
    PhoneBook   directory;
    std::string input;
    
    while (true) 
    {
        std::getline(std::cin, input);
        if (input == "ADD" || input == "add")
            addContact();
                
        else if (input == "SEARCH" || input == "search")
        {
            std::cout << 
        }
        
        else if (input == "EXIT" || input == "exit")
        
    }

}