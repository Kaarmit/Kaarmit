/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:07:54 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 19:24:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{
    
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& source) : tree_bag(source)
{
    
}

searchable_tree_bag searchable_tree_bag::operator=(const searchable_tree_bag& source)
{
    if (this != &source)
    {
        tree_bag::operator=(source);
    }
    return *this;
}

bool    searchable_tree_bag::search(node * node, const int value) const
{
    if (node == nullptr)
        return false;
    if (node->value == value)
        return true;
    else if (value < node->value)
        return(search(node->l, value));
    else
        return(search(node->r, value));
}

bool    searchable_tree_bag::has(int value) const
{
    return (search(this->tree, value));
}

searchable_tree_bag::~searchable_tree_bag()
{
    
}
