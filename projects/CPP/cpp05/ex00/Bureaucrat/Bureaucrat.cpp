/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:29 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 13:00:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Jerry"), _grade(150)
{
    std::cout << "Bureaucrat constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string const& name, int grade) : _name(name)
{
    if (grade < MAX_GRADE)
        throw GradeTooHighException();
    if (grade > MIN_GRADE)
        throw GradeTooLowException();
    _grade = grade;
    std::cout << "Bureaucrat full constructor called" << std::endl;
}
 
Bureaucrat::Bureaucrat(const Bureaucrat& rhs) : _name(rhs._name), _grade(rhs._grade)
{
    std::cout << "Bureaucrat copy constructor called" << std::endl;
}

Bureaucrat Bureaucrat::operator=(const Bureaucrat& rhs)
{
    std::cout << "Bureaucrat copy assignement constructor called" << std::endl;
    if (this != &rhs)
    {
        this->_grade = rhs._grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "Bureaucrat destructor called" << std::endl;
}

std::string const& Bureaucrat::getName() const
{
    return (this->_name);
}

int Bureaucrat::getGrade() const
{
    return (this->_grade);
}

const char*Bureaucrat::GradeTooHighException::what() const throw() 
{
    return "Grade too high!";
}

const char*Bureaucrat::GradeTooLowException::what() const throw() 
{
    return "Grade too low!";
}

void    Bureaucrat::betterGrade()
{
    if (this->getGrade() - 1 < MAX_GRADE)
    {
        throw GradeTooHighException();
        return;
    }
    else
    {
        this->_grade--;
        return;
    }
}

void    Bureaucrat::lesserGrade()
{
    if (this->getGrade() + 1 > MIN_GRADE)
    {
        throw GradeTooLowException();
        return;
    }
    else
    {
        this->_grade++;
        return;
    }
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& rhs)
{
  os << rhs.getName() << ", burecrats grade " << rhs.getGrade();
  return os;
}