/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:16:04 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/28 14:09:04 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <cstdint>
#include <iostream>




class Serializer
{


    public:

        static uintptr_t    serialize(Data* ptr);
        static Data*        deserialize(uintptr_t raw);
        
    private:

        Serializer();
        Serializer(const Serializer &rhs);
        Serializer operator=(const Serializer &rhs);
        ~Serializer();


};



#endif