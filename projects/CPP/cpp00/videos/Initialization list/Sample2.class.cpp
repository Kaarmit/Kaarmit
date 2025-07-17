/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample2.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:06:00 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 14:44:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample2.class.hpp"

Sample2::Sample2(char p1, int p2, float p3) : a1(p1), a2(p2), a3(p3) {  // Member initializer list
    std::cout << "Constructor called" << std ::endl;
    std::cout << "this-> a1 = " << this->a1 << std::endl;
    std::cout << "this-> a2 = " << this->a2 << std::endl;
    std::cout << "this-> a3 = " << this->a3 << std::endl;
}

Sample2:: ~Sample2(void) {
    std::cout << "Destructor called" << std::endl;
    return;
}