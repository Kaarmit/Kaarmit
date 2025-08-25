/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:13:11 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:51:02 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "../AForm/AForm.hpp"

class Bureaucrat;

class PresidentialPardonForm : public AForm
{
    public:
    
        enum {REQ_SIGN = 25, REQ_EXEC = 5};
    
        PresidentialPardonForm(std::string const);
        PresidentialPardonForm(const PresidentialPardonForm& rhs);
        PresidentialPardonForm& operator=(const PresidentialPardonForm& rhs);
        ~PresidentialPardonForm();
        
        std::string const getTarget() const;
        bool execute(Bureaucrat const & executor) const;
    
    private: 
        
        std::string _target;
        
};


#endif