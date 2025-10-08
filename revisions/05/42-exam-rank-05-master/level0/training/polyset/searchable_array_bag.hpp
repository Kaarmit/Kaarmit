/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:07:56 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 19:13:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag
{
    public :
        searchable_array_bag();
        searchable_array_bag(const searchable_array_bag& source);
        searchable_array_bag& operator=(const searchable_array_bag& source);
        bool has(int value) const;
        ~searchable_array_bag();
};