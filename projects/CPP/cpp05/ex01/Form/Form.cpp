/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:35:08 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/24 14:30:19 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"


Form::Form() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExec(1)
{
    //std::cout << "Form constructor called" << std::endl;
}

Form::Form(std::string const& name, int n, int n1) : _name(name), 
    _isSigned(false), 
    _gradeToSign(n),
    _gradeToExec(n1)
{
   // std::cout << "Form full constructor called" << std::endl;
}

Form::Form(const Form& rhs) : _name(rhs._name), 
    _isSigned(rhs._isSigned), 
    _gradeToSign(rhs._gradeToSign),
    _gradeToExec(rhs._gradeToExec)
{
   //std::cout << "Form copy constructor called" << std::endl;
}

Form Form::operator=(const Form& rhs)
{
    if (this != &rhs)
        this->_isSigned = rhs._isSigned;
    return *this;
    //std::cout << "Form copy assignement constructor called" << std::endl;
}

Form::~Form()
{
    //std::cout << "Form destructor called" << std::endl;
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
    os << rhs._name << ", form name  " << rhs._name;
    os << rhs._name << ", form signed  " << rhs._isSigned;
    os << rhs._name << ", form grade to sign  " << rhs._gradeToSign;
    os << rhs._name << ", form grade to exec " << rhs._gradeToExec;
    
    return os;
}