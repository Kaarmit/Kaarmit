/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:11:55 by aarmitan          #+#    #+#             */
/*   Updated: 2025/08/25 12:52:05 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{

}


ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& rhs) : AForm(rhs)
{
    _target = rhs._target;

}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs)
{
    if (this != &rhs)
    {
        AForm::operator=(rhs);
        _target = rhs._target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{

}


bool ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    if (!isSigned())
        throw AForm::NotSignedException();

    if (executor.getGrade() >= REQ_EXEC)
        throw AForm::GradeTooLowException();
    std::ofstream ofs((_target + "_shrubbery").c_str());
    if (!ofs) throw std::runtime_error("cannot open file");

    ofs << 
"        *\n"
"       /\\\n"
"      /\\*\\\n"
"     /\\O\\*\\\n"
"    /*/\\/\\/\\\n"
"   /\\O\\/\\*\\/\\\n"
"  /\\*\\/\\*\\/\\/\\\n"
" /\\O\\/\\/*/\\/O/\\\n"
"        ||\n"
"        ||\n"
"        ||\n";

    std::cout << _target << " has been created." << std::endl;
    return (true);
}