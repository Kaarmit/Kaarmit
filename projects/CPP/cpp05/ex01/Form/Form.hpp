/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:34:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:47:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <exception>
#include "../Bureaucrat/Bureaucrat.hpp"

class Bureaucrat;

class Form
{
    public:
    
    class GradeTooHighException : public std::exception 
    {
      public:
        virtual const char* what() const throw() { return "Grade too high!"; }
    };

    class GradeTooLowException : public std::exception 
    {
      public:
        virtual const char* what() const throw() { return "Grade too low!"; }
    };
    
    
    enum {MAX_GRADE = 1, MIN_GRADE = 150};
    
    
    Form();
    Form(std::string const& name, int n, int n1);
    Form(const Form& rhs);
    Form operator=(const Form& rhs);
    ~Form();
    
    std::string const& getFormName() const;
    bool const& isSigned() const;
    int const& gradeToSign() const;
    int const& gradeToExec() const;
    Form  beSigned(Bureaucrat &b);

    
    private:
    
        const std::string   _name;
        bool                _isSigned;
        const int           _gradeToSign;
        const int           _gradeToExec;
        
    friend std::ostream& operator<<(std::ostream& os, const Form& rhs);
    
};


#endif