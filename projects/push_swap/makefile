NAME = push_swap
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj/
SRC_DIR = srcs/

SRC = srcs/algorithm.c \
	srcs/back_to_A.c \
	srcs/big_three.c \
	srcs/cheapest.c \
	srcs/init.c \
	srcs/main.c \
	srcs/o_push.c \
	srcs/o_reverse_rotate.c \
	srcs/o_rotate.c \
	srcs/o_swap.c \

OBJ = ${SRC:.c=.o}

.c.o:
	${CC} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJ} ${NAME}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
