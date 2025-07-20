/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:23:12 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/20 12:21:05 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
   if (argc == 1)
   {
      std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
      std::cout << std::endl;
      return 0;
   }
   else if (argc > 1)
   {
      for (int i = 1; i < argc; ++i)
      {
         for (char *c = argv[i]; *c; ++c)
         {
            *c = toupper(*c);
         }
         std::cout << argv[i];
         if (i < argc - 1)
            std::cout << " ";
      }
      std::cout << std::endl;
   }
}