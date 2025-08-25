/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:34:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:50:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include<fstream>
#include <exception>
#include <string>
#include <ctime>
#include <cstdlib>
#include "../Bureaucrat/Bureaucrat.hpp"

class Bureaucrat;

class AForm
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
    
     class NotSignedException : public std::exception 
    {
      public:
        virtual const char* what() const throw() { return "Form not signed!"; }
    };
    
    AForm &operator=(const AForm& rhs);
    virtual ~AForm();
    
    std::string const& getFormName() const;
    bool const& isSigned() const;
    int const& getGradeToSign() const;
    int const& getGradeToExec() const;
    AForm  &beSigned(Bureaucrat &b);
    virtual bool execute(Bureaucrat const & executor) const = 0;

    
    enum {MAX_GRADE = 1, MIN_GRADE = 150};
  
    
    protected:
    
      AForm();
      AForm(std::string const& name, int n, int n1);
      AForm(const AForm& rhs);
  
    
    private:
    
        const std::string   _name;
        bool                _isSigned;
        const int           _gradeToSign;
        const int           _gradeToExec;
        
    friend std::ostream& operator<<(std::ostream& os, const AForm& rhs);
    
};


#endif