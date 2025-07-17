/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:59:02 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 14:42:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sample1.class.hpp"
#include "Sample2.class.hpp"
#include <iostream>

int main(void) {
   
    Sample1 instance1( 'a', 42, 4.2f ); // Create an instance of Sample1
    Sample2 instance2( 'z', 13, 3.15f);
    
    return 0;
}