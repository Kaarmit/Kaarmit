# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:57:56 by abastian          #+#    #+#              #
#    Updated: 2025/07/11 17:04:25 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CCF = clang -Wall -Wextra -Werror -g

LIBFT_PATH = libft/
LIBFT_FILE = libft.a
LIBFT_LIB = $(LIBFT_PATH)$(LIBFT_FILE)

MLX_PATH = minilibx-linux/
MLX_FILE = libmlx.a
MLX_LIB = $(MLX_PATH)$(MLX_FILE)

SRC_PATH = sources/
SRC = $(wildcard $(SRC_PATH)*.c)
OBJ = $(SRC:.c=.o)

BONUS_PATH = sources_bonus/
BONUS = $(wildcard $(BONUS_PATH)*.c)
BONUS_OBJ = $(BONUS:.c=.o)

INC = -I includes/ -I $(MLX_PATH) -I $(LIBFT_PATH)

$(BONUS_PATH)%.o: $(BONUS_PATH)%.c
	$(CCF) $(INC) -I includes_bonus/ -c $< -o $@

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(LIBFT_LIB):
	@echo "COMPILING libft..."
	@make -sC $(LIBFT_PATH)
	@echo "LIBFT compiled"

$(MLX_LIB):
	@echo "COMPILING $(MLX_PATH)..."
	@make -sC $(MLX_PATH)
	@echo "MLX_lib created"

$(NAME): $(OBJ)
	@echo "COMPILING cub3D..."
	$(CCF) -o $(NAME) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(INC) -lX11 -lXext -lm
	@echo "./cub3D created"

bonus: INC += -I includes_bonus/
bonus: $(LIBFT_LIB) $(MLX_LIB) $(BONUS_OBJ)
	@echo "COMPILING BONUS..."
	$(CCF) -o $(NAME) $(BONUS_OBJ) $(LIBFT_LIB) $(MLX_LIB) $(INC) -lX11 -lXext -lm
	@echo "./cub3D bonus created"

clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJ) $(BONUS_OBJ)
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH)
	@echo "Done"

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "Full clean done"

re: fclean all

.PHONY: all clean fclean re bonus
