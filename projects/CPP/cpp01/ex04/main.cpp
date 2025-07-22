/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:41:07 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/22 11:04:25 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    std::string s1;
    std::string s2;
    std::string line;
    std::string infile;
    
    if (argc == 4)
    {
        infile = argv[1];
        s1 = argv[2];
        s2 = argv[3];
        
        std::ifstream in(infile.c_str());
        if (!in)
        {
            std::cout << "Infile doesn't exist" << std::endl;
            return 1;
        }
        std::ofstream outfile((infile + ".replace").c_str());
        if (!outfile)
        {
            std::cout << "Outfile couldn't be created" << std::endl;
            return 1;
        }
        while (std::getline(in, line))
        {
            size_t  pos = 0;
            while ((pos = line.find(s1, pos)) != std::string::npos)
            {
                line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
                pos += s2.length();        
            }
            outfile << line << '\n';
        } 
    }
    else
    {
        std::cout << "wrong number of arguments" << std::endl;
    }      
}


