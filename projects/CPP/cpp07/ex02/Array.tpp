/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:09:45 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/03 16:46:31 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"


template<typename t>
Array<t>::Array() : _len(0)
{
    this->_array = new t [this->_len];
}

template<typename t>
Array<t>::Array(unsigned int n) : _len(n)
{
    this->_array = new t [this->_len];
}

template<typename t>
Array<t>::Array(const Array &rhs)
{

    this->_len = rhs.size();
    this->_array = new t[this->_len];
        
    for (size_t i = 0; i < rhs.size(); i++)
        this->_array[i] = rhs._array[i];
}

template<typename t>
Array<t> &Array<t>::operator=(const Array &rhs)
{
    if (this == &rhs)
        return (*this);
    delete[] this->_array;
    
    this->_len = rhs.size();
    this->_array = new t[this->_len];
    
    for (size_t i = 0; i < this->_len; i++)
        this->_array[i] = rhs._array[i];
    return (*this);

}

template<typename t>
t& Array<t>::operator[](unsigned int i)
{
    if (i >= this->size())
        throw std::out_of_range("Index out of bounds");
    return this->_array[i];     
}

template<typename t>
const t& Array<t>::operator[](unsigned int i) const
{
    if (i >= this->size())
        throw std::out_of_range("Index out of bounds");
    return this->_array[i];     
}

template<typename t>
Array<t>::~Array()
{
    delete[] this->_array;
}

template<typename t>
size_t  Array<t>::size() const
{
    return (this->_len);
}
