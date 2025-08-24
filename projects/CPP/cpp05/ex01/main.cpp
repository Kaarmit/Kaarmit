/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:33 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/24 14:29:24 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat  b1("Bob", 150);
        Form        f1("f1", 0, 1);
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    
    
    try
    {
        Bureaucrat  b2("Bob", 150);
        Form        f2("f2", 151, 1);
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    
    
    try
    {
        Bureaucrat  b3("Bob", 150);
        Form        f3("f3", 1, 0);
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    
    try
    {
        Bureaucrat  b4("Bob", 150);
        Form        f4("f4", 1, 151);
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    
    
    
    try
    {
        Bureaucrat  b5("Bob", 21);
        Form        f5("f5", 20, 1);
        
        b5.signForm(f5);
        b5.betterGrade();
        b5.signForm(f5);
        b5.signForm(f5);
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    return 0;
}

    
    
