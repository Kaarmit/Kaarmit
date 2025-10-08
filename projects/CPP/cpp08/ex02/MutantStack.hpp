/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:36:29 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/16 14:25:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque> 

template <typename T, typename Container = std::deque<T>>

class MutantStack : public std::stack<T, Container>
{
    
    public: 
    
        MutantStack() {};
        ~MutantStack() {};
        MutantStack(const MutantStack &rhs) : std::stack<T, Container>(rhs){};
        MutantStack operator=(const MutantStack &rhs) {
            if (this != rhs)
                std::stack<T, Container>::operator=(rhs);
            return this;    
        };
        
        typedef typename std::stack<T>::container_type::iterator   iterator;
        typedef typename std::stack<T>::container_type::iterator   const_iterator;
        
        iterator    begin() {return (this->c.begin());};
        iterator    end() {return (this->c.end());};
        
        const_iterator  begin()const {return (this->c.begin());};
        const_iterator  end()const {return (this->c.end());};
        
         
}
;
#endif