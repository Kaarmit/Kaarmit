/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:07:47 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 19:28:30 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "searchable_bag.hpp"

class set
{
    private:
        searchable_bag& bag;
    public:
        set() = delete;
        set(const set& source) = delete;
        set& operator=(const set& source) = delete;
        set(searchable_bag& s_bag);
        
        bool has(int) const;
        void insert(int);
        void insert(int *, int);
        void print() const;
        void clear();
        
        const searchable_bag& get_bag();
        
        ~set();
};