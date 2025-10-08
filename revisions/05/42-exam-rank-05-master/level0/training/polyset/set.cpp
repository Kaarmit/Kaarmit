/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:07:50 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 19:32:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"
#include "searchable_array_bag.hpp"

set::set(searchable_bag& s_bag) : bag(s_bag)
{
    
}

bool set::has(int value) const
{
    return(bag.has(value));
}

void set::insert(int value)
{
    if (!(this->has(value)))
        bag.insert(value);
}

void set::insert(int *data, int size)
{
    for (int i = 0; i < size; i++)
        this->insert(data[i]);
}

void set::print() const
{
    bag.print();
}

void set::clear()
{
    bag.clear();
}

const searchable_bag& set::get_bag()
{
    return this->bag;
}

set::~set()
{
    
}