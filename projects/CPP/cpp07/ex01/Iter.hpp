/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:56:28 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/04 07:22:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename t, typename f>

void    iter(t* array, std::size_t len, f const & func)
{
    if(!array)
        return;
        
    for (std::size_t i = 0; i < len; i++)
    {
        func(array[i]);
    }
}


#endif