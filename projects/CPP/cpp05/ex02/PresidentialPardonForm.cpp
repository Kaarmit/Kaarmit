/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:12:57 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/24 18:01:26 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("ShrubberyCreationForm", 25, 5), _target(target)
{
    //std::cout << "Presidential  constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& rhs): AForm(rhs)
{
    _target = rhs._target;
    // std::cout << "Presidential copy constructor called" << std::endl;    
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
    // std::cout << "Presidential copy destructor called" << std::endl;  
}

std::string const PresidentialPardonForm::getTarget() const
{
    return(this->_target);
}

std::ostream& operator<<(std::ostream& os, const AForm& rhs)
{
    os << rhs.getFormName() << " AForm level for sign : "<< rhs.getGradeToSign() << " | Level for exec : " << rhs.getGradeToExec();
	if (rhs.isSigned())
		os << " is Signed !";
	else 
		os << " not Signed yet!";
	return os;
}
bool PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    if (!isSigned())
        throw AForm::NotSignedException();

    if (executor.getGrade() > REQ_EXEC)
        throw AForm::GradeTooLowException();
        
    std::cout << getTarget() << " Has beed pardoned by Zaphod Beeblebrox." << std::endl;
        
}