# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 14:04:36 by aarmitan          #+#    #+#              #
#    Updated: 2025/08/25 11:18:22 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = intern
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp \
		Bureaucrat.cpp \
		Intern.cpp \
		AForm.cpp \
		PresidentialPardonForm.cpp \
		ShrubberyCreationForm.cpp \
		RobotomyRequestForm.cpp \
		
		
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