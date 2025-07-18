/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 08:55:30 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:02:47 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_CLASS_HPP
#define SAMPLE_CLASS_HPP

class Sample {
    
    public:
    
        Sample(void);
        ~Sample(void);
        
        int     getFoo(void) const;
        void    setFoo(int v);
        
    private:
    
        int _foo;
};

#endif