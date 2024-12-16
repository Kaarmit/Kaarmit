NAME = philo

SRC = philo.c utils.c init.c monitor.c threads.c routine.c

MANPATH = $(addprefix ./srcs/, $(SRC))

FLAGS = -Wall -Wextra -Werror -O3 -pthread

HEADER = ./includes/philo.h

# SANITIZER = -fsanitize=thread

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: FLAGS += -g
debug: re

delay:
	python3 delay_o_meter.py
