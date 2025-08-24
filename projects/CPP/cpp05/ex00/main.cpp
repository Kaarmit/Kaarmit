/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:04:33 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/24 13:57:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat  b1("Bob", 200);
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
        Bureaucrat  b2("Annie", 0);
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
        Bureaucrat  b3("Jimmy", 150);
        std::cout << "Bureaucrats name is " << b3.getName() << std::endl;
        std::cout << "Bureaucrats grade is " << b3.getGrade() << std::endl;
        
        b3.betterGrade(); // changed
        std::cout << "Bureaucrats grade is " << b3.getGrade() << std::endl;
        b3.lesserGrade(); // changed
        std::cout << "Bureaucrats grade is " << b3.getGrade() << std::endl;
        b3.lesserGrade(); // unchanged
        std::cout << "Bureaucrats grade is " << b3.getGrade() << std::endl;
                
   
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
        Bureaucrat b4 ("Howard", 1);
        std::cout << "Bureaucrats name is " << b4.getName() << std::endl;
        std::cout << "Bureaucrats grade is " << b4.getGrade() << std::endl;
        
        b4.lesserGrade(); // changed
        std::cout << "Bureaucrats grade is " << b4.getGrade() << std::endl;
        b4.betterGrade(); // changed
        std::cout << "Bureaucrats grade is " << b4.getGrade() << std::endl;
        b4.betterGrade(); // unchanged
        std::cout << "Bureaucrats grade is " << b4.getGrade() << std::endl;
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
    
    
