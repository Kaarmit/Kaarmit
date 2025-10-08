/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:36:15 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/16 14:47:25 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() 
{
    {
        /*------STACK MAIN------*/
        MutantStack<int> mstack;
        mstack.push(5);
        mstack.push(17);
        std::cout << "the top of the stack is " << mstack.top() << std::endl;
        mstack.pop();
        std::cout << "the size of the stack is " << mstack.size() << std::endl;
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        //[...]
        mstack.push(0);
        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
        std::stack<int> s(mstack);
    }
    {
        /*------LIST MAIN------*/
        std::list<int> l;
        l.push_back(5);
        l.push_back(17);
        std::cout << "the top of the list is " << l.back() << std::endl;
        l.pop_back();
        std::cout << "the size of the list is " <<l.size() << std::endl;
        l.push_back(3);
        l.push_back(5);
        l.push_back(737);
        //[...]
        l.push_back(0);
        std::list<int>::iterator it = l.begin();
        std::list<int>::iterator ite = l.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
        return 0;
        }
}    