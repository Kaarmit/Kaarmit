/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:33 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:24:35 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
    Bureaucrat b1("Peon++", 130);
    Bureaucrat b2("Peon", 45);
    Bureaucrat b3("Big Boss", 1);
    Intern MegaPeon;
    AForm* srf;
    AForm* rrf;
    AForm* ppf;
    
    srf = MegaPeon.makeForm("shrubbery request", "Tree");
    rrf = MegaPeon.makeForm("robotomy request", "Bender");
    ppf = MegaPeon.makeForm("presidential request", "Outlaw");
    
    std::cout << std::endl;
    
    b1.signForm(*srf);
    b1.executeForm(*srf);
    
    std::cout << std::endl;
    
    b2.signForm(*rrf);
    b2.executeForm(*rrf);
    
    std::cout << std::endl;
    
    b3.signForm(*ppf);
    b3.executeForm(*ppf);
        
    return 0;
}

    
    
