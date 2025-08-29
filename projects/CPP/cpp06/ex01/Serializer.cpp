/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:16:34 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/28 18:11:24 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer()
{
    
}

Serializer::Serializer(const Serializer &rhs)
{
    
}

Serializer Serializer::operator=(const Serializer &rhs)
{
    return *this;
}

Serializer::~Serializer()
{
    
}

uintptr_t Serializer::serialize(Data* ptr)
{
    if (ptr == 0)
        throw std::invalid_argument("Serializer::serialize: null pointer");
    return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return (reinterpret_cast<Data*>(raw));
}