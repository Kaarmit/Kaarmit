/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:10:20 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:12:47 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_CLASS_HPP
#define SAMPLE_CLASS_HPP

class   Sample {
    
    public:
        Sample(int v);
        ~Sample(void);
        
        int getFoo(void) const;
        int compare(Sample * other) const;
        
    private:
    
        int _foo;        
    
};

#endif