/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:40:10 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 13:24:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H


class Sample {

public:

    int    foo;  // Example member variable
    
    Sample(void); // Constructor declaration
    ~Sample(void); // Destructor declaration
    
    void    bar(void); // Example member function declaration
};


#endif