/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:16:34 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 15:17:46 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Sample_class.hpp"

int main() {
    
    Sample instance(3.14f); // Create an instance of Sample with pi initialized to 3.14
    
    instance.bar();
    
    return 0;
}