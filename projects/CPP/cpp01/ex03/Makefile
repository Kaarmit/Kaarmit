# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 17:52:25 by aarmitan          #+#    #+#              #
#    Updated: 2025/07/21 17:55:25 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = attack
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iincludes/

SRC = main.cpp \
		HumanA.cpp \
		HumanB.cpp \
		Weapon.cpp \
		
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

