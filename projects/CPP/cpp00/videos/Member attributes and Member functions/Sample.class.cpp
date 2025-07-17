/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:42:44 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 13:54:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample.class.hpp"

Sample::Sample(void){
    
    std::cout << "Constructor called" << std::endl;
    
    return;
} // Constructor definition

Sample::~Sample(void){
    
    std::cout << "Destructor called" << std::endl;
    return;
} // Destructor definition

void Sample::bar(void){
    std::cout << "Member function bar called" << std::endl;
    return;
} // Member function definition
  // This function, even if void, takes a parameter implicitly, which is a pointer to the instance of the class (this).