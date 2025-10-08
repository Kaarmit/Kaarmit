/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:07:58 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 19:14:24 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{
    
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag& source) : array_bag(source)
{
    
}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
    if (this != &source)
    {
        array_bag::operator=(source);
    }
    return *this;
}

bool searchable_array_bag::has(int value) const
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i] == value)
            return true;
    }
    return false;
}

searchable_array_bag::~searchable_array_bag()
{
    
}