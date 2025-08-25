# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 14:04:36 by aarmitan          #+#    #+#              #
#    Updated: 2025/08/25 11:54:06 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = intern
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98


SRC_DIRS = . Bureaucrat AForm Presidential Robotomy Shrubbery Intern
INCLUDES = $(addprefix -I, $(SRC_DIRS))


SRC = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJ = $(SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
