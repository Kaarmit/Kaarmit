/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sample_class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:50:31 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/18 09:52:14 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_CLASS_HPP
#define SAMPLE_CLASS_HPP

class Sample {
  
    public:
    
        Sample(void);
        ~Sample(void);
        
        static int  getNbInst(void);
        
    private:
    
        static int  _NbInst;
};

#endif