/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:56:39 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 10:59:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

Sample::Sample(void) : foo(0){
    
    std::cout << "Constructor called" << std::endl;
    return;
}

Sample::~Sample(void) {
    
    std::cout << "Destructor called" << std::endl;
    return;
}

void Sample::bar(void) const {
    
    std::cout << "Member function bar called" << std::endl;
    return;
}