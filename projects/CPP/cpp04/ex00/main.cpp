/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:51:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 11:25:40 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

const WrongAnimal* meta1 = new WrongAnimal();
const WrongAnimal* i1 = new WrongCat();

std::cout << j->getType() << " " << std::endl;
std::cout << i->getType() << " " << std::endl;
std::cout << i1->getType() << " " << std::endl;

i->makeSound();
j->makeSound();
meta->makeSound();

std::cout << "Wrong Animals->" << std::endl;

std::cout << "Wrong Animal noise:";
i1->makeSound(); 
std::cout << "Wrong Cat noise:";
meta1->makeSound();

return 0;
}