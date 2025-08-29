/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:42:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/28 18:07:18 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"


int main(int argc, char **argv)
{
    std::string input;
    
    if (argc == 2)
    {
        ScalarConverter::convert(argv[1]);
        std::cout << std::endl;
        std::cout << "'Exit' to end program" << std::endl;
    
        
        while (true) 
        {
            std::cout << std::endl;
            std::cout << "convert > " << std::flush;
            if (!std::getline(std::cin, input)) 
            {
                std::cout << "\nExiting." << std::endl;
                break;
            }
            if (input == "exit" || input == "Exit" || input == "EXIT")
                break;

            if (input.empty())
                continue;

            ScalarConverter::convert(input);
            std::cout << std::endl;
            std::cout << "'Exit' to end program" << std::endl;
        }
    }
    
    else 
    {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1;
    }
    return 0;
}
