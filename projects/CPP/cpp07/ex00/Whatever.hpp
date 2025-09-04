/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:05:03 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/02 15:29:27 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP


template<typename T>

void       swap(T &x, T &y)
{
    T   temp = x;
    
    x = y;
    y = temp;
}

template<typename T>   

T const  min(T const &x, T const &y)
{
    if ( x == y)
        return (y);
    return (x <= y ? x : y);
}

template<typename T>

T const  max(T const &x, T const &y)
{
    if ( x == y)
        return (y);
    return (x >= y ? x : y);
}

#endif