NAME = libft
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rcs
HEADER = .../inc/libft.h
SRC_DIRS = Classification Lists Conversion GNL Memory Output Printf String
SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
