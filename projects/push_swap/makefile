NAME =			push_swap
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
AR =			ar rcs
RM =			rm -f

LIBFT_PATH 	= ./libft/
LIBFT_NAME	= my_lib.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			= -I ./includes/\
			  -I ./libft/\

SRC_PATH	= ./src/
SRCS 		= $(shell find $(SRC_PATH) -name '*.c')
OBJ_PATH	= obj/
OBJS		= $(SRCS:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all:		$(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
				$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

$(LIBFT):
			@make -C $(LIBFT_PATH)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -lXext -lX11 -lm
			@echo "push_swap \033[1;32mOK\033[m"

clean:
			$(RM) -r $(OBJ_PATH)
			@make clean -C $(LIBFT_PATH)

fclean: clean
			$(RM) $(NAME)
			@make fclean -C $(LIBFT_PATH)

re:			fclean all

