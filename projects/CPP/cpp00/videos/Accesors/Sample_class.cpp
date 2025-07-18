/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:57:48 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:04:27 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

Sample::Sample(void){
    
    std::cout << "Constructor called" << std::endl;
    
    this->setFoo(0);
    std::cout << "this->getFoo(): " << this->getFoo() << std::endl;
    
    return;
}

Sample::~Sample(void){
    
    std::cout << "Destructor called" << std::endl;
    return;
}

int Sample::getFoo(void) const {
    
    return this->_foo;
}

void    Sample::setFoo(int v) {
    
    if (v >= 0)
        this->_foo = v;
        
    return;
}