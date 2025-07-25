# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 11:48:48 by aarmitan          #+#    #+#              #
#    Updated: 2024/10/16 16:07:21 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= so_long
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g

MLX_PATH    = minilibx-linux/
MLX_NAME    = libmlx.a
MLX         = $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH 	= libft/
LIBFT_NAME	= libft
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			= -I ./includes/\
			-I ./libft/\
			-I ./minilibx-linux/

SRC_PATH	= ./srcs/
SRC			= so_long.c \
			close_me.c \
			init_map.c \
			init_map_utils.c \
			check_map.c \
			check_map_utils.c \
			init_game.c \
			move_to.c \
			put_text.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all:		$(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
			@mkdir $(OBJ_PATH)

$(MLX):
			@make -sC $(MLX_PATH) --no-print-directory
			@echo "MiniLibX \033[1;32mOK\033[m"

$(LIBFT):
			@make -sC $(LIBFT_PATH) --no-print-directory
			@echo "Libft \033[1;32mOK\033[m"

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm
			@echo "So Long \033[1;32mOK\033[m"

clean:
			@rm -rf $(OBJ_PATH)
			@make clean -C $(MLX_PATH) --no-print-directory
			@make clean -C $(LIBFT_PATH) --no-print-directory

fclean:
			@rm -rf $(NAME)
			@rm -rf $(LIBFT_PATH)$(LIBFT_NAME)

re:			fclean all
