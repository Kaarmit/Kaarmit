/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:36 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/09 12:15:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <exception>
#include <climits>
#include <algorithm>

class Span
{
    
    public:
    
        
        Span(int N);
        Span(const Span &rhs);
        Span operator=(const Span &rhs);
        ~Span();
        
        
        void    addNumber(int n);
        void    addMoreNumbers();
        int     shortestSpan();
        int     longestSpan();
    
    private:
    
        Span();
        int _max;
        size_t      _length;
        std::vector<int> _tab;
        
    
};

#endif