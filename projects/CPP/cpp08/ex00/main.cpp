/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:07:36 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/19 10:52:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Easyfind.hpp"
#include <iostream>
#include <vector>


int main(void)
{
    {
        std::vector<int> v;
        
        for(int i = 0; i < 10; i++)
            v.push_back(i);
            
        try
        {
            std::vector<int>::iterator it = easyFind(v, 1);
            (void)it;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
        std::cout << "FOUND" << std::endl;
    }
    
    {
        std::vector<int> v;
        
        for(int i = 0; i < 10; i++)
            v.push_back(i);
            
        try
        {
            std::vector<int>::iterator it = easyFind(v, 19);
            (void)it;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
        std::cout << "FOUND" << std::endl;
    }
    
}