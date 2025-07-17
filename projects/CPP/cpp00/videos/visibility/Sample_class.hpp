/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:10:17 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 16:22:00 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H

class Sample {
    
    public: 
    
        int     publicfoo;
        
        Sample(void);
        ~Sample(void);
        
        void    publicbar(void) const;
        
    private:
    
        int     _privatefoo;
        
        void    _privatebar(void) const;
        
};

#endif