/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample1.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:42:44 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 14:09:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample1.class.hpp"

Sample1::Sample1(char p1, int p2, float p3){
    
    std::cout << "Constructor called" << std::endl;
    
    this->a1 = p1; // Initialize member variable a1 with p1
    std::cout << "this->a1 = : " << this->a1 << std::endl; // Output the value of a1
    
    this->a2 = p2; // Initialize member variable a2 with p2
    std::cout << "this->a2 = : " << this->a2 << std::endl; // Output the value of a2
    
    this->a3 = p3; // Initialize member variable a3 with p3
    std::cout << "this->a3 = " << this->a3 << std::endl; // Output the value of a3
    
    return;
} // Constructor definition

Sample1::~Sample1(void){
    
    std::cout << "Destructor called" << std::endl;
    return;
} // Destructor definition
