/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:07:30 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/17 15:31:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>


template<typename T>

typename T::iterator easyFind(T & list, int n)
{
    typename T::iterator it = find(list.begin(). list.end(), n);
    if (it == list.end)
        throw std::out_of_range("NOT FOUND");
    return it;
}

#endif