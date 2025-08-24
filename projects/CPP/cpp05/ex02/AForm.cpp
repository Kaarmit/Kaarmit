/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:35:08 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/24 16:51:47 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"


AForm::AForm() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExec(1)
{
    //std::cout << "Form constructor called" << std::endl;
}

AForm::AForm(std::string const& name, int n, int n1) : _name(name), 
    _isSigned(false), 
    _gradeToSign(n),
    _gradeToExec(n1)
{
   // std::cout << "Form full constructor called" << std::endl;
}

AForm::AForm(const AForm& rhs) : _name(rhs._name), 
    _isSigned(rhs._isSigned), 
    _gradeToSign(rhs._gradeToSign),
    _gradeToExec(rhs._gradeToExec)
{
   //std::cout << "Form copy constructor called" << std::endl;
}

AForm &AForm::operator=(const AForm& rhs)
{
    if (this != &rhs)
        this->_isSigned = rhs._isSigned;
    return *this;
    //std::cout << "Form copy assignement constructor called" << std::endl;
}

AForm::~AForm()
{
    //std::cout << "Form destructor called" << std::endl;
}

std::string const& AForm::getFormName() const
{
    return (this->_name);
}

bool const& AForm::isSigned() const
{
    return (this->_isSigned);
}

int const& AForm::getGradeToSign() const
{
    return (this->_gradeToExec);
}

int const& AForm::getGradeToExec() const
{
    return (this->_gradeToExec);
}

AForm  &AForm::beSigned(Bureaucrat &b)
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

std::ostream& operator<<(std::ostream& os, const AForm& rhs)
{
    os << rhs.getFormName() << " AForm level for sign : "<< rhs.getGradeToSign() << " | Level for exec : " << rhs.getGradeToExec();
	if (rhs.isSigned())
		os << " is Signed !";
	else 
		os << " not Signed yet!";
	return os;
}