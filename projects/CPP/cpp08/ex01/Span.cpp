/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:43 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/17 11:48:54 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"


Span::Span() {}

Span::~Span() {}

Span::Span(int N) : _max(N), _length(0)
{}


Span::Span(const Span &rhs)
{
    this->_length = rhs._length;
    
    for (size_t i = 0; i < rhs._length; i++)
        this->_tab[i] = rhs._tab[i];
}


Span Span::operator=(const Span &rhs)
{
    if (this == &rhs)
        return (*this);
    
    this->_length = rhs._length;

    for (size_t i = 0; i < _length; i++)
        this->_tab[i] = rhs._tab[i];
    return (*this);
    
}


void    Span::addNumber(int n)
{
    if (_length == _max)
        throw std::length_error("SPAN IS FULL");
    else
    {
        _tab.push_back(n);
        _length += 1;
    }
    return;
}


void    Span::addMoreNumbers()
{
        std::vector<int>::const_iterator it;
        std::vector<int>::const_iterator ite = _tab.end() + _max ;
        
        for(it = _tab.begin(); it < ite; it++)
        {
            if (_length == _max)
                throw std::length_error("SPAN IS FULL");
            _tab.push_back(rand());
            _length += 1;
        }
}

int     Span::shortestSpan()
{
    if (_length <= 1)
        throw std::length_error("NOT ENOUGH INTEGERS TO GET SHORTEST SPAN");
    
    int span = INT_MAX;
    
    std::sort(_tab.begin(), _tab.end());
    
    for (size_t i = 0; i < _tab.size() - 1; i++) 
    {
      int diff = _tab[i + 1] - _tab[i];
      if (diff < span)
          span = diff;
    }
    return (span);
}


int     Span::longestSpan()
{
        if (_length <= 1)
            throw std::length_error("NOT ENOUGH INTEGERS TO GET LONGEST SPAN");
            
        int min = *min_element(_tab.begin(), _tab.end());
        int max = *max_element(_tab.begin(), _tab.end());
        
        return (max - min);
}