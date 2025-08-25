/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:31 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 13:00:05 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <exception>

class Bureaucrat
{
  public:
  
  
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
    
 
    
    class GradeTooHighException : public std::exception 
    {
      public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception 
    {
      public:
        const char* what() const throw();
    };
  
  private:
  
    const std::string   _name;
    int                 _grade;
    
    
  };
  
std::ostream& operator<<(std::ostream& os, const Bureaucrat& rhs);

#endif