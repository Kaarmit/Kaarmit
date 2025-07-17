/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:02:56 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/17 15:05:30 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H

class Sample {
    
    public:
    
        float const pi;
        int         qd;
        
        Sample( float const f ); 
        ~Sample( void );
        
        void    bar( void ) const;
};

#endif