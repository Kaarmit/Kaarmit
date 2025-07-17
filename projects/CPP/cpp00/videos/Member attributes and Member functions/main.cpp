/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:59:02 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 13:54:39 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sample.class.hpp"
#include <iostream>

int main(void) {
    Sample instance;
    // The constructor will be called automatically when the instance is created
    // The destructor will be called automatically when the instance goes out of scope
    instance.foo = 42; // Accessing the member variable
    std::cout << "instance foo: " << instance.foo << std::endl; // Output the value of foo
    
    instance.bar(); // Calling the member function bar

    return 0;
}