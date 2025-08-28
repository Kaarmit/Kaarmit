/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:41:32 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/28 16:04:36 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"


Base::~Base()
{
    
}

Base* generate(void) 
{
    int r = rand() % 3;   
    if (r == 0)
        return new A;
    else if (r == 1)
        return new B;
    else
        return new C;
}


void identify(Base* p)
{
    A* a = dynamic_cast<A*>(p);
    B* b = dynamic_cast<B*>(p);
    C* c = dynamic_cast<C*>(p);
    
    if (a)
        std::cout << "A" << std::endl;

    else if (b)
        std::cout << "B" << std::endl;

    else    
        std::cout << "C" << std::endl;
 
    return;
}

void identify(Base& p) 
{
    try 
    { 
        (void)dynamic_cast<A&>(p); 
        std::cout << "A\n"; 
        return; 
    }
    catch (std::exception&) 
    {}
    
    try 
    { 
        (void)dynamic_cast<B&>(p); 
        std::cout << "B\n"; 
        return; 
    }
    catch (std::exception&) 
    {}
    
    try 
    { 
        (void)dynamic_cast<C&>(p); 
        std::cout << "C\n"; 
        return; 
    }
    catch (std::exception&) 
    {}
    
    std::cout << "Unknown\n";
}


