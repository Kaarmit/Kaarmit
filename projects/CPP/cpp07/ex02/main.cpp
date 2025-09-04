/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:17:31 by aarmitan          #+#    #+#             */
/*   Updated: 2025/09/04 07:39:29 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include "Array.tpp"
#include <cstdlib>
#include <string>
#include <iostream>

#define MAX_VAL 10

template <typename T> void print(const T &x)
{
	std::cout << x << std::endl;
}

int main(int, char**)
{
	{
		std::cout << "\n\n---FIRST MAIN---\n" << std::endl;

		std::cout << "\nCreating array of int..." << std::endl;
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];

		std::cout << "\nFilling the arrays..." << std::endl;
		srand(time(NULL));
		for (int i = 0; i < MAX_VAL; i++)
		{
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}

		std::cout << "\nChecking if arrays are equal..." << std::endl;
		for (int i = 0; i < MAX_VAL; i++)
		{
			if (mirror[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				return 1;
			}
		}
		std::cout << "\nThey are." << std::endl;
		std::cout << "\nTrying some exception..." << std::endl;
		try
		{
			numbers[-2] = 0;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Exception 1: " << e.what() << '\n';
		}
		try
		{
			numbers[MAX_VAL] = 0;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Exception 2: " <<e.what() << '\n';
		}

		delete [] mirror;
	}


	{
		std::cout << "\n\n---SECOND MAIN---\n" << std::endl;

		std::cout << "\nCreating array of int..." << std::endl;
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];

		std::cout << "\nFilling the arrays..." << std::endl;
		srand(time(NULL));
		for (int i = 0; i < MAX_VAL; i++)
		{
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}

		std::cout << "\nCreating arrays by copy..." << std::endl;
		Array<int> tmp = numbers;
        Array<int> test(tmp);

		std::cout << "\nChecking if arrays are equal..." << std::endl;
		std::cout << "\n" << std::endl;
		for (int i = 0; i < MAX_VAL; i++)
		{
			if (tmp[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				::print(tmp[i]);
				::print(numbers[i]);
			}
		}
		for (int i = 0; i < MAX_VAL; i++)
		{
			if (test[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				::print(test[i]);
				::print(numbers[i]);
			}
		}
		std::cout << "\nThey are." << std::endl;

		std::cout << "\nChanging value inside arrays..." << std::endl;
		tmp[5] = 89796;
		test[3] = 8465;

			for (int i = 0; i < MAX_VAL; i++)
		{
			if (tmp[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				::print(tmp[i]);
				::print(numbers[i]);
			}
		}
		for (int i = 0; i < MAX_VAL; i++)
		{
			if (test[i] != numbers[i])
			{

				std::cerr << "didn't save the same value!!" << std::endl;
				::print(test[i]);
				::print(numbers[i]);
			}
		}

		delete[] mirror;
    }

	{
		std::cout << "\n\n---THIRD MAIN---\n" << std::endl;

		Array<std::string> strings;          

		std::cout << strings.size() << std::endl;

		try
		{
			std::cout << strings[0] << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

    return 0;
}