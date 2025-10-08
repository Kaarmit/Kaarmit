/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:50:45 by aarmitan          #+#    #+#             */
/*   Updated: 2025/10/08 18:28:21 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>


class vect2
{
    private: 
        
        int x;
        int y;

    
    public :
    
        vect2();
        vect2(int num1, int num2);
        vect2(const vect2& rhs);
        vect2& operator=(const vect2& rhs);
        
        
        int operator[](int index)const;
        int& operator[](int index);
        
        vect2 operator-()const ;
        vect2 operator*(int num) const;
        
        vect2& operator *=(int num);
        
        vect2& operator+=(const vect2& rhs);
        vect2& operator-=(const vect2& rhs);
        vect2& operator*=(const vect2& rhs);
        
        vect2 operator+(const vect2& rhs) const;
        vect2 operator-(const vect2& rhs) const;
        vect2 operator*(const vect2& rhs) const;
        

        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);
        
        bool operator!=(const vect2& rhs) const;
        bool operator==(const vect2& rhs) const;
        
 
    
        ~vect2();
};

vect2   operator*(int num, const vect2& rhs);
std::ostream&    operator<<(std::ostream os, const vect2& rhs);

#endif

