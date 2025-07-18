/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:59:56 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 11:10:00 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

int main() {
    
    Sample instance;
    Sample * instancep = &instance;
    
    int Sample::*p = NULL;
    void    (Sample::*f)(void) const;
    
    p = &Sample::foo;
    
    std::cout << "Value of member foo: " << instance.foo << std::endl;
    instance.*p = 21;
    std::cout << "Value of member foo: " << instance.foo << std::endl;
    instancep->*p = 42;
    std::cout << "Value of member foo: " << instance.foo << std::endl;
    
    f = &Sample::bar;
    
    (instance.*f)();
    (instancep->*f)();
    
    return 0;
}