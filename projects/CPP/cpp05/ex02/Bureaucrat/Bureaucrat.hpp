/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:31 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:50:51 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <exception>
#include "../AForm/AForm.hpp"

class AForm;

class Bureaucrat
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
    
    
    Bureaucrat();
    Bureaucrat(std::string const& name, int n);
    Bureaucrat(const Bureaucrat& rhs);
    Bureaucrat operator=(const Bureaucrat& rhs);
    ~Bureaucrat();
    
    
    std::string const& getName() const;
    int         getGrade() const;
    void        betterGrade();
    void        lesserGrade();
    void        signForm(AForm &form);
    void        executeForm(AForm const & form) const;
    

  
  private:
  
    const std::string   _name;
    int                 _grade;
    
  friend std::ostream& operator<<(std::ostream& os, const Bureaucrat& rhs);
    
};


#endif