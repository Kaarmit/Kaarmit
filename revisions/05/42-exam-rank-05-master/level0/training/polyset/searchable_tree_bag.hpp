/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:07:52 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 19:17:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag
{
    private:
        bool    search(node* node, const int value) const;
        
    public:
        searchable_tree_bag();
        searchable_tree_bag(const searchable_tree_bag& source);
        searchable_tree_bag operator=(const searchable_tree_bag& source);
        bool has(int value) const;
        ~searchable_tree_bag();
};