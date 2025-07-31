/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:51:27 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/31 13:22:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

int main() {
    const int size = 4;
    Animal* animals[size];

    // Remplir moitié Dog, moitié Cat
    for (int i = 0; i < size; ++i) {
        if (i < size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    // Remplir des idées dans un Dog
    Dog* dog = dynamic_cast<Dog*>(animals[0]);
    dog->getBrain()->setIdea(0, "chasser");
    dog->getBrain()->setIdea(1, "manger");
    std::cout << "Dog original ideas:\n";
    std::cout << "0: " << dog->getBrain()->getIdea(0) << "\n";
    std::cout << "1: " << dog->getBrain()->getIdea(1) << "\n";

    // Copier le dog
    Dog copy = *dog;
    std::cout << "Dog copy ideas before change:\n";
    std::cout << "0: " << copy.getBrain()->getIdea(0) << "\n";
    std::cout << "1: " << copy.getBrain()->getIdea(1) << "\n";

    // Modifier l'original, vérifier que la copie ne change pas
    dog->getBrain()->setIdea(0, "fuir");
    std::cout << "Dog original idea[0] after change: " << dog->getBrain()->getIdea(0) << "\n";
    std::cout << "Dog copy idea[0] remains: " << copy.getBrain()->getIdea(0) << "\n";

    // Supprimer tous les animaux
    for (int i = 0; i < size; ++i)
        delete animals[i];

    return 0;
}
