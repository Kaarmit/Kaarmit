NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SRCS = srcs/ft_printf.c srcs/ft_print_hexa.c srcs/ft_print_id.c srcs/ft_print_ptr.c \
		srcs/ft_print_u.c \

OBJS = ${SRCS:.c=.o}

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c -I $(INCLUDES) $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@make -C libft
	@cp libft/libft.a .
	@mv libft.a ${NAME}
	${AR} ${NAME} ${OBJS}

clean:
	@make clean -C libft
	rm -f ${OBJS}

fclean:		clean
	rm -f libft/libft.a
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re libft
