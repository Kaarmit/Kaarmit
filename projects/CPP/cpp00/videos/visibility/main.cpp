/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:27:49 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 16:32:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

int main() {
    Sample instance;
    
    instance.publicfoo = 42;
    std::cout << "instance.publicfoo: " << instance.publicfoo << std::endl;
    // instance._privatefoo = 42; // This line would cause a compilation error due to private access
    // std::cout << "instance._privatefoo: " << instance._privatefoo << std::endl; // This line would also cause a compilation error due to private access
    
    instance.publicbar();
    //instance._privatebar(); // This line would cause a compilation error due to private access
    return 0;
}