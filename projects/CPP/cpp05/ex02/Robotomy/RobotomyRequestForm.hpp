/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:12:14 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 11:51:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM
#define ROBOTOMYREQUESTFORM


#include "../AForm/AForm.hpp"

class Bureaucrat;

class RobotomyRequestForm : public AForm
{
    public:
    
        enum {REQ_SIGN = 72, REQ_EXEC = 45};
    
        RobotomyRequestForm(std::string const);
        RobotomyRequestForm(const RobotomyRequestForm& rhs);
        RobotomyRequestForm& operator=(const RobotomyRequestForm& rhs);
        ~RobotomyRequestForm();
        
        std::string const getTarget() const;
        bool execute(Bureaucrat const & executor) const;
    
    private: 
        
        std::string _target;
        
};



#endif