/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:35:08 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 13:07:57 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"


Form::Form() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExec(1)
{

}

Form::Form(std::string const& name, int n, int n1) : _name(name), 
    _isSigned(false), 
    _gradeToSign(n),
    _gradeToExec(n1)
{

}

Form::Form(const Form& rhs) : _name(rhs._name), 
    _isSigned(rhs._isSigned), 
    _gradeToSign(rhs._gradeToSign),
    _gradeToExec(rhs._gradeToExec)
{

}

Form Form::operator=(const Form& rhs)
{
    if (this != &rhs)
        this->_isSigned = rhs._isSigned;
    return *this;
}

Form::~Form()
{

}

std::string const& Form::getFormName() const
{
    return (this->_name);
}

bool const& Form::isSigned() const
{
    return (this->_isSigned);
}

int const& Form::gradeToSign() const
{
    return (this->_gradeToExec);
}

int const& Form::gradeToExec() const
{
    return (this->_gradeToExec);
}

const char*Form::GradeTooHighException::what() const throw() 
{
    return "Grade too high!";
}

const char*Form::GradeTooLowException::what() const throw() 
{
    return "Grade too low!";
}

Form  Form::beSigned(Bureaucrat &b)
{
    if (_isSigned)
    {
        std::cout << b.getName() << " couldn't sign form because form is already signed" << std::endl;
        return *this;
    }
    if (b.getGrade() <= this->_gradeToSign)
    {
        this->_isSigned = true;
        std::cout << b.getName() << " signed " << _name << " form "<< std::endl;
        return *this;
    }
    std::cout << b.getName() << " couldn't sign form because grade is too low" << std::endl;  
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Form& rhs)
{
    os << rhs.getFormName() << ", form name  " << rhs.getFormName();
    os << rhs.getFormName() << ", form signed  " << rhs.isSigned();
    os << rhs.getFormName() << ", form grade to sign  " << rhs.gradeToSign();
    os << rhs.getFormName() << ", form grade to exec " << rhs.gradeToExec();
    
    return os;
}