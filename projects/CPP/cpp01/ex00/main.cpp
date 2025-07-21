/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:57:49 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 12:55:27 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    Zombie* ptr;
    ptr = newZombie("Bobby");
    ptr->announce();
    randomChump("Alain");
    delete(ptr);
}