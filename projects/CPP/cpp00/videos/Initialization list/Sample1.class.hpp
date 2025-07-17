/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:40:10 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 14:05:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE1_CLASS_H
#define SAMPLE1_CLASS_H


class Sample1 {

public:

    char   a1;
    int    a2;
    float  a3;
    
    Sample1(char p1, int p2, float p3); // Constructor declaration
    ~Sample1(void); // Destructor declaration
    
    void    bar(void); // Example member function declaration
};


#endif