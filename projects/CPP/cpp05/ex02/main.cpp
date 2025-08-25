/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:33 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:52:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat/Bureaucrat.hpp"
#include "AForm/AForm.hpp"
#include "Presidential/PresidentialPardonForm.hpp"
#include "Robotomy/RobotomyRequestForm.hpp"
#include "Shrubbery/ShrubberyCreationForm.hpp"

int main(void)
{
    AForm* f1 = new ShrubberyCreationForm("home");
    AForm* f2 = new RobotomyRequestForm("home");
    AForm* f3 = new PresidentialPardonForm("home");
    
    try
    {
        Bureaucrat  b1("Peon", 146);
        
        b1.betterGrade();
        b1.signForm(*f1);
        b1.executeForm(*f1);
        std::cout << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::NotSignedException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    try
    {
        Bureaucrat  b1("Peon++", 135);
        
        b1.signForm(*f1);
        b1.executeForm(*f1);
        std::cout << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::NotSignedException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    
    try
    {
        Bureaucrat  b2("Peon Mid", 73);
        
        b2.betterGrade();
        b2.signForm(*f2);
        b2.executeForm(*f2);
        std::cout << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::NotSignedException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    try
    {
        Bureaucrat  b2("Peon Mid", 45);
        
        b2.signForm(*f2);
        b2.executeForm(*f2);
        std::cout << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::NotSignedException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    
        try
    {
        Bureaucrat  b3("Big Boss", 26);
        
        b3.betterGrade();
        b3.signForm(*f3);
        b3.executeForm(*f3);
        std::cout << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::NotSignedException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    try
    {
        Bureaucrat  b3("Big Boss", 1);
        
        b3.signForm(*f3);
        b3.executeForm(*f3);
        std::cout << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch(const AForm::NotSignedException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    delete f1;
    delete f2;
    delete f3;
    
    return 0;
}

    
    
