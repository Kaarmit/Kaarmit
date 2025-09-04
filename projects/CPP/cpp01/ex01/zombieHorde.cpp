/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:59:54 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/23 13:16:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* _zombieHorde(int N, std::string name)
{
    Zombie* ptr = new Zombie[N];
    
    for (int i = 0; i < N; i++)
        ptr[i].setName(name);
    return ptr;
}