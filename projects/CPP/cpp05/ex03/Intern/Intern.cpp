/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:30:49 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 12:54:06 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"


Intern::Intern()
{
    
}

Intern::Intern(const Intern &rhs)
{
    (void)rhs;
}

Intern Intern::operator=(const Intern &rhs)
{
    (void)rhs;
    return (*this);
}

Intern::~Intern()
{
    
}


AForm*  Intern::makeForm(std::string form, std::string target)
{
    std::string formList[] = {"shrubbery request", "robotomy request", "presidential request"};
    int index = -1;
    
    for (int i = 0; i < 3; i++)
    {
        if (form == formList[i])
        {
            index = i;
            break;
        }
    }
    
    switch (index)
    {
        case 0:
        {
            std::cout << "Intern creates " << form << std::endl;
            return (new ShrubberyCreationForm(target));
        }
        
        case 1:
        {
            std::cout << "Intern creates " << form << std::endl;
            return (new RobotomyRequestForm(target));
        }
        
        case 2:
        {
            std::cout << "Intern creates " << form << std::endl;
            return (new PresidentialPardonForm(target));
        }
    
        default:
        {
            std::cout << "Intern doesn't know the form " << form << std::endl;
            break;
        }
    }
    return (NULL);    
}
