/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:57:49 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/21 14:15:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    int N = 5;
    Zombie* ptr;
    ptr = zombieHorde(N, "Bobby");
    for(int i = 0; i < N; i++)
        ptr->announce();
    delete[] ptr;
}