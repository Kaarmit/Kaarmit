/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:11:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:55:10 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "../AForm/AForm.hpp"


class Bureaucrat;

class ShrubberyCreationForm : public AForm
{
    public:
    
        enum {REQ_SIGN = 145, REQ_EXEC = 137};
    
        ShrubberyCreationForm(std::string const);
        ShrubberyCreationForm(const ShrubberyCreationForm& rhs);
        ShrubberyCreationForm& operator=(const ShrubberyCreationForm& rhs);
        ~ShrubberyCreationForm();
        
        bool execute(Bureaucrat const & executor) const;
    
    private: 
        

        std::string _target;
        

};


#endif