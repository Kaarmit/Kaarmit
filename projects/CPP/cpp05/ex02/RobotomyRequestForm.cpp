/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:54:50 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/24 17:57:58 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("ShrubberyCreationForm", 72, 45), _target(target)
{
    std::srand(std::time(0));
    //std::cout << "Robotomy constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& rhs): AForm(rhs)
{
    _target = rhs._target;
    // std::cout << "Robotomycopy constructor called" << std::endl;    
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& rhs)
{
    if (this != &rhs)
    {
        AForm::operator=(rhs);
        _target = rhs._target;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
    // std::cout << "Robotomycopy destructor called" << std::endl;  
}

std::string const RobotomyRequestForm::getTarget() const
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


bool RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
    if (!isSigned())
        throw AForm::NotSignedException();

    if (executor.getGrade() > REQ_EXEC)
        throw AForm::GradeTooLowException();
        
    int result = std::rand() % 2;
    
    if (result == 1)
    {
        std::cout << "*Drilling noises*" << this->getTarget() << " has been robotomyzed succesfully." << std::endl;
        return (true);
    }
    std::cout << "The robotmy has failed." << std::endl;
    return (false);
}


