/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample2.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:04:55 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 14:05:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE2_CLASS_H
#define SAMPLE2_CLASS_H


class Sample2 {

public:

    char   a1;
    int    a2;
    float  a3;
    
    Sample2(char p1, int p2, float p3); // Constructor declaration
    ~Sample2(void); // Destructor declaration
    
    void    bar(void); // Example member function declaration
};


#endif