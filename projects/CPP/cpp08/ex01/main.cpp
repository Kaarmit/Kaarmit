/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:49 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/09 11:30:11 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main(void)
{
    srand (time(NULL));
    
    /*MAIN DU SUJET*/
    
    std::cout << "---SUJET---" << std::endl;
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    std::cout << "\n";    
        
    /*TEST 10000 INTEGERS */
    
    std::cout << "---10000 INT---" << std::endl;
    Span sp2 = Span(10000);
    sp2.addMoreNumbers();
    std::cout << sp2.shortestSpan() << std::endl;
    std::cout << sp2.longestSpan() << std::endl;
    std::cout << "\n";    
    
    /*TEST 20000 INTEGERS */
    
    std::cout << "---20000 INT---" << std::endl;
    Span sp3 = Span(20000);
    sp3.addMoreNumbers();
    std::cout << sp3.shortestSpan() << std::endl;
    std::cout << sp3.longestSpan() << std::endl;
    std::cout << "\n";
    
    /*TEST CONTAINER VIDE*/
    
    std::cout << "---CONTAINER VIDE---" << std::endl;
    try
    {
        Span vide = Span(10);
        
        std::cout << vide.shortestSpan() << std::endl;
        std::cout << vide.longestSpan() << std::endl;
        

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "\n";
    
    /*TEST 1 ELEMENT*/
    
    std::cout << "---ELEMENT UNIQUE---" << std::endl;
    try
    {
        
        Span un = Span(10);
        
        un.addNumber(1);
        
        std::cout << un.shortestSpan() << std::endl;
        std::cout << un.longestSpan() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "\n";
    
        /*TEST CONTAINER FULL*/
        
    std::cout << "---CONTAINER PLEIN---" << std::endl;
    try
    {
        
        Span full = Span(10);
        
        full.addMoreNumbers();
        full.addNumber(3);
        
        std::cout << full.shortestSpan() << std::endl;
        std::cout << full.longestSpan() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "\n";
    
    return 0;

}