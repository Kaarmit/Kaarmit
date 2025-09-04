/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:27:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/29 13:13:32 by aarmitan         ###   ########.fr       */
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
        std::cout << "ADD, SEARCH or EXIT" << std::endl;
        std::cout << "> ";
        if (!std::getline(std::cin, input)){
            if(std::cin.eof()){
                std::cout << "Input interrupted. Exiting";
                return 0;
            }
            continue;
        }
        if (input == "ADD" /*|| input == "add"*/){
            if (directory.getCount() == 8)
                std::cout << "Oldest contact will be overwritten" << std::endl;
            directory.addContact();
        }       
        else if (input == "SEARCH")
        {
            directory.displayAll();
            if (directory.getCount() == 0)
            {
                std::cout << "Repertory is empty";
                std::cout << std::endl;
                continue;
            }
            while (true) 
            {
                if (!std::getline(std::cin, input)) 
                {
                    if (std::cin.eof()) {
                    std::cout << "Input interrupted. Exiting";
                    return 0;
                }
                continue;
                }
                std::stringstream ss(input);
                if ((ss >> index) && ss.eof() && index >= 0 && index < directory.getCount()) 
                {
                    directory.displayOne(index);
                    break;
                }
                std::cout << "Incorrect index. Try again:" << std::endl;
            }
        }       
        else if (input == "EXIT" /*|| input == "exit"*/)
            return 0;
    }
}



