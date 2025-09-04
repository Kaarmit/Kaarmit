/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:56:56 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/04 07:26:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iter.hpp"
#include <string>
#include <iostream>
#include <iomanip>



template <typename t>

void    print(t const &x)
{
    //std::cout << x << std::endl;
    std::cout << std::fixed << std::setprecision(1) << x << std::endl;
}

template<typename t>

void add1(t& x) 
{ 
    x = x + 1; 
}

int main(void)
{
    std::cout << "---STRING---" << std::endl;
    std::string str[] = {"A", "B", "C"};
    ::iter(str, 3, print<std::string>);
    
    std::cout << "---INT---" << std::endl;
    int tab[] = {42, 420, 4200};
    ::iter(tab, 3, print<int>);
    
    std::cout << "---FLOAT---" << std::endl;
    float tab2[] = {42.0f, 420.0f, 420.0f};
    ::iter(tab2, 3, print<float>);
    
    std::cout << "---DOUBLE---" << std::endl;
    double tab3[] = {42.0, 420.0, 4200.0};
    ::iter(tab3, 3, print<double>);
    
    
    std::cout << std::endl;   
    
    // ----- TESTS CONST -----
    std::cout << "---CONST STRING---\n";
    const std::string cstr[] = {"A", "B", "C"};
    ::iter(cstr, 3, print<std::string const>);   

    std::cout << "---CONST INT---\n";
    const int ctab[] = {1, 2, 3};
    ::iter(ctab, 3, print<int const>);           
    //::iter(ctab, 3, add1<int>);               // DOIT ÉCHOUER À LA COMPILATION (mutation interdite)

    std::cout << "---CONST FLOAT---\n";
    const float ctab2[] = {1.f, 2.f, 3.f};
    ::iter(ctab2, 3, print<float const>);       

    std::cout << "---CONST DOUBLE---\n";
    const double ctab3[] = {1.0, 2.0, 3.0};
    ::iter(ctab3, 3, print<double const>);  
    
    std::cout << "---MUTATION SUR NON-CONST---\n";
    ::iter(tab, 3, add1<int>);                  
    ::iter(tab, 3, print<int>);
    
    std::cout << std::endl;
    
    std::cout << "---EMPTY TABS---" << std::endl;
    std::string* nullStr = 0;                   
    ::iter(nullStr, 3, print<std::string>);
}

