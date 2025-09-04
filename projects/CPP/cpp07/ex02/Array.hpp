/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:17:41 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/03 16:47:16 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstring>
#include <exception>
#include <stdexcept>

template<typename t>
class Array
{
    public:

    
        Array();
        Array(unsigned int n);
        Array(const Array &rhs);
        Array &operator=(const Array &rhs);
        t& operator[](unsigned int i);
        const t& operator[](unsigned int i) const;
        ~Array();
        
        
        size_t size() const;
    
    
    private:
        
        size_t _len;
        t* _array;
    
};

#endif