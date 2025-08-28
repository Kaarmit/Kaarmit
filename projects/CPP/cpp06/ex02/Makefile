# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/28 14:07:51 by aarmitan          #+#    #+#              #
#    Updated: 2025/08/28 14:08:01 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = base
C++ = c++
C++FLAGS = -Wall -Wextra -Werror -std=c++98


SRC_DIRS = . 
INCLUDES = $(addprefix -I, $(SRC_DIRS))


SRC = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJ = $(SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^
	@echo "Executable $(NAME) created."

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "Executable $(NAME) removed."

re: fclean all