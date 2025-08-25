/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:30:56 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:54:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include "../AForm/AForm.hpp"
#include "../Bureaucrat/Bureaucrat.hpp"

class Bureaucrat;

class Intern
{
    public :
    
        Intern();
        Intern(const Intern &rhs);
        Intern operator=(const Intern &rhs);
        ~Intern();
        
        AForm*  makeForm(std::string form, std::string target);
    
    private :
    
};

#endif