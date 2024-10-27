# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 14:22:12 by ilymegy           #+#    #+#              #
#    Updated: 2023/07/18 11:09:01 by ilymegy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft
CC			=	gcc
INCLUDE		=	../inc
SRCS_DIR	=	src/
OBJS_DIR	=	obj/
FLAGS		=	-Wall -Wextra -Werror -g3 -I
SRC_FILES	=	$(shell find $(SRCS_DIR) -name '*.c' | cut -d/ -f2 | cut -d. -f1)

SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJSF		=	.cache_exists
NORME_ME	=	norminette -R CheckForbiddenSourceHeader

#RAINBOOOW
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all:		$(NAME)

$(NAME): $(OBJS)
			ar -rcs $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo "$(GREEN)My Libft compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJSF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJSF):
			@mkdir -p $(OBJS_DIR)

clean:
			rm -rf $(OBJS_DIR)
			@$(RM) -f $(OBJSF)
			@echo "$(BLUE)libft objects files cleaned!$(DEF_COLOR)"

fclean:		clean
			rm -rf $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
			$(NORME_ME) $(SRCS) $(INCLUDE) | grep -v Norme -B1 || true
