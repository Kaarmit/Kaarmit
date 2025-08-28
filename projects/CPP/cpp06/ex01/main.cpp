/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:47:23 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/28 13:47:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

int main() 
{
    Data d;
    d.s = "hello";
    d.n = 42;

    uintptr_t raw = Serializer::serialize(&d);
    Data* p = Serializer::deserialize(raw);

    std::cout << std::boolalpha << (&d == p) << "\n";
    std::cout << p->s << " " << p->n << "\n";
}
