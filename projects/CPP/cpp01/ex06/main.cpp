/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:15:19 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/22 14:55:01 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <cstdlib>


int main(int argc, char **argv)
{
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    Harl    harl;
    int i = -1;
    
    for (int j = 0; j < 4; j++)
    {
        if (argv[1] == levels[j])
        {
            i = j + 1;
            break;
        }
    }
    
    if (argc == 2)
    {
        switch (i)
        {
            case 1 :
            {
                harl.complain("DEBUG");
                harl.complain("INFO");
                harl.complain("WARNING");
                harl.complain("ERROR");
                break;
            }
        
            case 2:
            {
                harl.complain("INFO");
                harl.complain("WARNING");
                harl.complain("ERROR");
                break;
            }
            
            case 3:
            {           
                harl.complain("WARNING");
                harl.complain("ERROR");
                break;
            }
            
            case 4:
                harl.complain("ERROR");
                break;
        }
    }
    else
        std::cout << "Wrong number of arguments" << std::endl; 
}