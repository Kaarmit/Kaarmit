/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:09:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:15:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

Sample::Sample(int v) : _foo(v) {
    
    std::cout << "Constructor called" << std::endl;
    return;
}

Sample::~Sample(void){
    
    std::cout << "Destructor called" << std::endl;
    return;
}

int Sample::getFoo(void) const {
    
    return this->_foo;
}

int Sample::compare(Sample * other) const {
    
    if (this->_foo < other->getFoo())
        return -1;
    else if (this->_foo > other->getFoo())
        return 1;
    
    return 0;
}