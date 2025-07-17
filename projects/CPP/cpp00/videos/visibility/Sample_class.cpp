/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:14:41 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 16:27:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

Sample::Sample(void){
    
    std::cout << "Constructor called" << std::endl;
    
    this->publicfoo = 0;
    std::cout << "ths->publicfoo: " << this->publicfoo << std::endl;
    this->_privatefoo = 0;
    std::cout << "this->_privatefoo: " << this->_privatefoo << std::endl;\
    
    this->publicbar();
    this->_privatebar();
    
    return;    
}

Sample::~Sample(void){
    
    std::cout << "Destructor called" << std::endl;
    
    return;
}

void Sample::publicbar(void) const {
    
    std::cout << "Member function publicbar called" << std::endl;
    
    return;
}

void Sample::_privatebar(void) const {
    
    std::cout << "Member function _privatebar called" << std::endl;
    
    return;
}