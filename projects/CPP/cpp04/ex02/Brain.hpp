/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:33:44 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 13:24:37 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "Animal.hpp"
#include <iostream>

class Brain
{
    public: 
    
        Brain();
        Brain(const Brain& rhs);
        Brain operator=(const Brain& rhs);
        ~Brain();
        
        std::string getIdea(int index) const;
        void setIdea(int index, const std::string& idea);

        
    protected: 
    
        std::string _ideas[100];

};


#endif