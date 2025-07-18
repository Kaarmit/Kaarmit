/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sampe_class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:53:15 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:56:37 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

Sample::Sample(void){
    
    std::cout << "Constructor called" << std::endl;
    Sample::_NbInst += 1;
    
    return;
}

Sample::~Sample(void){
    
    std::cout << "Destructor called" << std::endl;
    Sample::_NbInst -= 1;
    
    return; 
}

int Sample::getNbInst(void){
    
    return Sample::_NbInst;
}

int Sample::_NbInst = 0;
    