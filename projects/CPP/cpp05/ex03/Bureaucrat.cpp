/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:29 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 10:29:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Jerry"), _grade(150)
{

}

Bureaucrat::Bureaucrat(std::string const& name, int grade) : _name(name)
{
    if (grade < MAX_GRADE)
        throw GradeTooHighException();
    if (grade > MIN_GRADE)
        throw GradeTooLowException();
    _grade = grade;

}
 
Bureaucrat::Bureaucrat(const Bureaucrat& rhs) : _name(rhs._name), _grade(rhs._grade)
{

}

Bureaucrat Bureaucrat::operator=(const Bureaucrat& rhs)
{
    if (this != &rhs)
        this->_grade = rhs._grade;
    return *this;
}

Bureaucrat::~Bureaucrat()
{

}

std::string const& Bureaucrat::getName() const
{
    return (this->_name);
}

int Bureaucrat::getGrade() const
{
    return (this->_grade);
}

void    Bureaucrat::betterGrade()
{
    if (this->getGrade() - 1 < 1)
    {
        std::cout << "Failed to augment " << this->getName() << " grade" << std::endl;
        throw GradeTooHighException();
        return;
    }
    else
    {
        std::cout << this->getName() << "s grade succefully augmented" << std::endl;
        this->_grade--;
        return;
    }
}

void    Bureaucrat::lesserGrade()
{
    if (this->getGrade() + 1 > 150)
    {
        std::cout << "Failed to lower " << this->getName() << " grade" << std::endl;
        throw GradeTooLowException();
        return;
    }
    else
    {
        std::cout << this->getName() << "s grade succefully lowered" << std::endl;
        this->_grade++;
        return;
    }
}

void  Bureaucrat::signForm(AForm &form)
{
    form.beSigned(*this);
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& rhs)
{
  os << rhs._name << ", burecrate grade " << rhs._grade;
  return os;
}

void Bureaucrat::executeForm(AForm const & form) const
{
    try 
    {
        form.execute(*this);
        std::cout << this->getName() << " executed " << form.getFormName() << std::endl;
    }
    catch (std::exception const& e) 
    {
        std::cout << this->getName() << " failed to execute " << form.getFormName()
                  << " because: " << e.what() << std::endl;
    }
}
