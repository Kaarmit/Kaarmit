/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:12:57 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:27:46 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5), _target(target)
{

}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& rhs): AForm(rhs)
{
    _target = rhs._target;
  
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& rhs)
{
    if (this != &rhs)
    {
        AForm::operator=(rhs);
        _target = rhs._target;
    }
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{

}

std::string const PresidentialPardonForm::getTarget() const
{
    return(this->_target);
}


bool PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    if (!isSigned())
        throw AForm::NotSignedException();

    if (executor.getGrade() > REQ_EXEC)
        throw AForm::GradeTooLowException();
        
    std::cout << getTarget() << " Has beed pardoned by Zaphod Beeblebrox" << std::endl;
    return (true); 
}