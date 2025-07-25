/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:18:13 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:23:08 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

int main() {
    
    Sample instance1(42);
    Sample instance2(42);
    
    if (&instance1 == &instance1)
        std::cout << "instance1 and instance1 are physically equal" << std::endl;
    else
        std::cout << "instance1 and instance1 are not physically equal" << std::endl;
    
    if (&instance1 == &instance2)
        std::cout << "instance1 and instance1 are physically equal" << std::endl;
    else if (&instance1 == &instance2)
        std::cout << "instance1 and instance1 are not physically equal" << std::endl;
    
    if (instance1.compare(&instance1) == 0)
        std::cout << "instance1 and instance1 are structurally equal" << std::endl;
    else
        std::cout << "instance1 and instance1 are not structurally equal" << std::endl;
    
        if (instance1.compare(&instance2) == 0)
        std::cout << "instance1 and instance2 are structurally equal" << std::endl;
    else
        std::cout << "instance1 and instance2 are not structurally equal" << std::endl;
    
    return 0;
}
