/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:54:50 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 12:51:37 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target)
{
    std::srand(std::time(0));

}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& rhs): AForm(rhs)
{
    _target = rhs._target;
  
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

}

std::string const RobotomyRequestForm::getTarget() const
{
    return(this->_target);
}


bool RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
    if (!isSigned())
        throw AForm::NotSignedException();

    if (executor.getGrade() >= REQ_EXEC)
        throw AForm::GradeTooLowException();
        
    int result = std::rand() % 2;
    
    if (result == 1)
    {
        std::cout << "*Drilling noises* " << this->getTarget() << " has been robotomyzed succesfully." << std::endl;
        return (true);
    }
    std::cout << "The robotmy has failed." << std::endl;
    return (false);
}


