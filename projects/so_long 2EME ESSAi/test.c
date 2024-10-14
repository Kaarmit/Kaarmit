
#ifndef SO_LONG_H
# define SO_LONG_H

// EVENTS
# define ON_DESTROY 17
# define KEY_PRESSED 2
# define KEY_RELEASED 3
# define EXIT_MASK 0
# define KEY_MASK 2
# define ERRPLAYER "This is a single player game"
# define ERRBER "Wrong file type"
# define ERRELEM "Wrong number of elements (Exit / Collectibles)"
# define ERRARG "Too many files"
# define ERRARG0 "Missing .ber file"
# define ERRFILE "Please specify file name"
# define ERRFILE1 "this file is empty"
# define WINNER "Winner, winner, chicken dinner"
# define ERRPOINTER "Invalid pointer(s) passed to mlx_put_image_to_window\n"
# define ERRECT "This map is not rectangular"
# define ERRWALLS "The map is not surronded by walls"
# define UNKNOWN "Unknown element"
# define ERRSAVE "An error occured while saving the map"
# define ERRSAVE1 "Could not save the map"
# define ERRMAP "The map is unplayable! Closing the game"
# define ERRMLX "Fail init MLX"
# define ERRWIN "Fail creating the window"
# define ERROPEN "Error trying to open the map"
# define ERRASSET "Error while retrieving assets"

// INCLUDES
# include "../includes/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// STRUCTURES

typedef struct s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			x_p;
	int			y_p;
	void		*wall_img;
	void		*collec_img;
	void		*pac_img_u;
	void		*pac_img_d;
	void		*pac_img_l;
	void		*pac_img_r;
	void		*exit_img;
	void		*bg_img;
	t_vector	img_size;
	char		**map;
	t_vector	map_size;
	t_vector	p_pos;
	int			nb_c;
	int			moves;
}				t_game;

typedef struct s_game_map
{
	int			c;
	int			p;
	int			e;
	int			x;
	int			y;
}				t_game_map;

// TOOLS
enum			e_state
{
	event_end = -1,
	map_error = 2,
	file_error = 3,
	asset_error = 4,
};

// FUNCTIONS
// exit game
void			free_map(char **map);
void			destroy_the(t_game *game);
void			end_game(char *msg, t_game *game, enum e_state state,
					char *free_me);
int				exit_event(t_game *game);

// init game
void			init_game(t_game *game, char *map_file);

// init map && init map utils
char			**get_map(char *map_file, t_game *game, int err);
void			render_map(t_game *game);

// check map
void			check_map_rect(t_game *game);
void			check_map_walls(t_game *game);
void			check_map_elem(t_game *game, t_game_map *map);
void			is_map_playable(t_game *game, char *map_file, int err);
void			show_table(char **map);

// check map utils
int				get_height(char **map);
int				check_line(char *line);
void			check_map_valid(t_game *game, char *map_file, int err);
int				to_find(char *str, char c);
int				is_out(int x, int y, int size_x, int size_y);

// move to
void			move_to(int x, int y, void *dir, t_game *game);
int				is_wall(t_game *game, int y, int x);
void			*save_that_img(char *img_path, t_game *game);
void			put_that_img(void *img, int x, int y, t_game *game);

// put_text
void			put_text(t_game *game);

#endif

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// LIBFT
int		ft_atoi_base(const char *str, const char *base, size_t len_base);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_convert_base(const char *str, const char *base_from,
			const char *base_to);
void	*ft_free_strs(char **strs, int size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_ischarset(int c, const char *charset);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
char	*ft_itoa_base(int n, const char *base, size_t len_base);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_nbrlen(int n);
size_t	ft_nbrlen_base(int n, size_t len_base);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char *s, char c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
size_t	ft_strclen(const char *s, const char *charset);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(char *str1, char *str2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strsjoin(const char **strs, const char *sep);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_toupper(int c);
int		ft_tolower(int c);

// PRINTF
int		ft_printf(const char *str, ...);
int		search_str(const char *string, int searchedChar);
char	*p_nbr(int nbr);
char	*p_uint(unsigned int n, char format);
int		p_char(char c);
int		p_str(char *str, int *res_l);
int		p_ptr(unsigned long long ptr);

// GNL
# define BUFFER_SIZE 42

typedef struct s_gnl
{
	char					*content;
	struct s_gnl			*next;
}	t_gnl;

char	*get_next_line(int fd, int *err);
t_gnl	*get_last(t_gnl *str);
void	create_line(t_gnl *str, char **line);
void	free_str(t_gnl *str);
int		is_newline(t_gnl *s);
int		ft_len(const char *str);

#endif

NAME		= so_long
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g

MLX_PATH    = minilibx/
MLX_NAME    = libmlx.a
MLX         = $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH 	= libft/
LIBFT_NAME	= libft
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			= -I ./includes/\
			-I ./libft/\
			-I ./minilibx/

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


#include "../../includes/libft.h"

int	ft_len(const char *str)
{
	int	n;

	n = 0;
	while (str[n])
		++n;
	return (n);
}

int	is_newline(t_gnl *s)
{
	int		i;
	t_gnl	*curr;

	i = 0;
	if (!s)
		return (0);
	curr = get_last(s);
	while (curr->content[i])
	{
		if (curr->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_gnl	*get_last(t_gnl *str)
{
	t_gnl	*s;

	s = str;
	while (s && s->next)
		s = s->next;
	return (s);
}

void	create_line(t_gnl *str, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (str)
	{
		// if (str->content == NULL)
		// 	break;
		i = 0;
		while (str->content[i])
		{
			if (str->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		str = str->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (!(*line))
	{
		free_str(str);
		str = NULL;
	}
}

void	free_str(t_gnl *str)
{
	t_gnl	*s;
	t_gnl	*tmp;

	s = str;
	while (s)
	{
		free(s->content);
		tmp = s->next;
		free(s);
		s = tmp;
	}
}

void	clean_me(t_gnl **str)
{
	t_gnl	*last;
	t_gnl	*clear;
	int		i;
	int		j;

	clear = malloc(sizeof(t_gnl));
	if (!clear || !str)
		return ;
	clear->next = NULL;
	last = get_last(*str);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clear->content = malloc(sizeof(char) * ((ft_len(last->content) - i) + 1));
	if (!(clear->content))
		return ;
	j = 0;
	while (last->content[i])
		clear->content[j++] = last->content[i++];
	clear->content[j] = '\0';
	free_str(*str);
	*str = clear;
}

void	extract_me(t_gnl *str, char **line)
{
	int	i;
	int	j;

	create_line(str, line);
	if (!(*line))
		return ;
	j = 0;
	while (str)
	{
		i = 0;
		while (str->content[i])
		{
			if (str->content[i] == '\n')
			{
				(*line)[j++] = str->content[i];
				break ;
			}
			(*line)[j++] = str->content[i++];
		}
		str = str->next;
	}
	(*line)[j] = '\0';
}

void	add_to_str(t_gnl **str, char *buffer, int size)
{
	int		i;
	t_gnl	*last;
	t_gnl	*new;

	new = malloc(sizeof(t_gnl));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (size + 1));
	if (!(new->content))
		return ;
	i = 0;
	while (buffer[i] && i < size)
	{
		new->content[i] = buffer[i];
		i++;
	}
	new->content[i] = '\0';
	if (!(*str))
	{
		*str = new;
		return ;
	}
	last = get_last(*str);
	last->next = new;
}

void	read_me(int fd, t_gnl **str)
{
	char	*buffer;
	int		size_readed;

	size_readed = 1;
	while (!is_newline(*str) && size_readed != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		size_readed = (int)read(fd, buffer, BUFFER_SIZE);
		if ((size_readed == 0 && !(*str)) || size_readed == -1)
		{
			free(buffer);
			return ;
		}
		buffer[size_readed] = '\0';
		add_to_str(str, buffer, size_readed);
		free(buffer);
	}
}

char	*get_next_line(int fd, int *err)
{
	static t_gnl	*str = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_me(fd, &str);
	if (!str)
		return (NULL);
	extract_me(str, &line);
	if (!line)
	{
		*err = 1;
		return (NULL);
	}
	if (!line[0])
	{
		free(line);
		free_str(str);
		str = NULL;
		return (NULL);
	}
	clean_me(&str);
	return (line);
}

int	words_count(const char *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++count;
		while (*s && *s != sep)
			++s;
	}
	return (count);
}

static int	give_to(char **tab, char const *s, char sep)
{
	char		**res;
	char const	*tmp;

	tmp = s;
	res = tab;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		while (*tmp && *tmp != sep)
			++tmp;
		if (*tmp == sep || tmp > s)
		{
			*res = ft_substr(s, 0, tmp - s);
			if (!(*res))
				return (1);
			s = tmp;
			++res;
		}
	}
	*res = NULL;
	return (0);
}

char	**ft_split(char *s, char sep)
{
	char	**res;
	int		err;

	if (!s)
		return (NULL);
	err = 0;
	res = (char **)malloc((words_count(s, sep) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	err = give_to(res, s, sep);
	free(s);
	if (err)
		return (NULL);
	return (res);
}
size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
		++n;
	return (n);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	check_map_valid(t_game *game, char *map_file, int err)
{
	t_game_map	map;

	map.p = 0;
	map.e = 0;
	map.y = game->map_size.y - 1;
	check_map_rect(game);
	check_map_walls(game);
	check_map_elem(game, &map);
	is_map_playable(game, map_file, err);
}

int	to_find(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	is_out(int x, int y, int size_x, int size_y)
{
	return (y < 0 || y >= size_y || x < 0 || x >= size_x);
}

int	fill(char **map, t_vector size, t_vector cur, char *e)
{
	static int	elem_count = 0;

	if (is_out(cur.x, cur.y, size.x, size.y)
		|| !to_find(e, map[cur.y][cur.x]))
		return (elem_count);
	if (map[cur.y][cur.x] == e[0])
		elem_count++;
	map[cur.y][cur.x] = 'X';
	fill(map, size, (t_vector){cur.x - 1, cur.y}, e);
	fill(map, size, (t_vector){cur.x + 1, cur.y}, e);
	fill(map, size, (t_vector){cur.x, cur.y - 1}, e);
	fill(map, size, (t_vector){cur.x, cur.y + 1}, e);
	return (elem_count);
}

void	is_map_playable(t_game *game, char *map_file, int err)
{
	char	**map_clone;
	int		collected;

	map_clone = get_map(map_file, game, err);
	if (!map_clone)
		end_game(ERRSAVE, game, map_error, NULL);
	collected = fill(map_clone, game->map_size, game->p_pos, "CP0");
	free_map(map_clone);
	if (collected == game->nb_c)
	{
		map_clone = get_map(map_file, game, err);
		if (!map_clone)
			end_game(ERRSAVE1, game, map_error, NULL);
		collected = fill(map_clone, game->map_size, game->p_pos, "ECP0");
		free_map(map_clone);
	}
	if (collected != game->nb_c + 1)
		end_game(ERRMAP, game, map_error, NULL);
	return ;
}

void	check_map_rect(t_game *game)
{
	int	y;
	int	x;
	int	height;
	int	temp;

	y = 0;
	temp = 0;
	height = game->map_size.y;
	while (y != height)
	{
		x = 0;
		while (game->map[y][x] != '\0')
			x++;
		y++;
		if (temp != 0)
		{
			if (temp != x)
				end_game(ERRECT, game, map_error, NULL);
		}
		else
			temp = x;
	}
}

void	check_map_walls(t_game *game)
{
	int	i;
	int	end;

	if (check_line(game->map[0]))
		end_game(ERRWALLS, game, map_error, NULL);
	i = game->map_size.y - 1;
	while (i)
	{
		end = ft_strlen(game->map[i]) - 1;
		if (!is_wall(game, i, 0) || !is_wall(game, i, end))
			end_game(ERRWALLS, game, map_error, NULL);
		i--;
	}
	if (check_line(game->map[game->map_size.y - 1]))
		end_game(ERRWALLS, game, map_error, NULL);
}

void	check_map_elem(t_game *game, t_game_map *map)
{
	while (map->y--)
	{
		map->x = 0;
		while (game->map[map->y][map->x] != '\0')
		{
			if (game->map[map->y][map->x] == 'E')
				map->e++;
			else if (game->map[map->y][map->x] == 'P')
			{
				map->p++;
				game->p_pos.x = map->x;
				game->p_pos.y = map->y;
			}
			else if (game->map[map->y][map->x] == 'C')
				game->nb_c++;
			else if (game->map[map->y][map->x] != '1')
				if (game->map[map->y][map->x] != '0')
					end_game(UNKNOWN, game, map_error, NULL);
			map->x++;
		}
	}
	if (game->nb_c < 1 || map->e != 1)
		end_game(ERRELEM, game, map_error, NULL);
	else if (map->p != 1)
		end_game(ERRPLAYER, game, map_error, NULL);
}

int	exit_event(t_game *game)
{
	end_game("", game, event_end, NULL);
	return (0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}

void	destroy_the(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx_ptr, game->wall_img);
	if (game->bg_img)
		mlx_destroy_image(game->mlx_ptr, game->bg_img);
	if (game->pac_img_u)
		mlx_destroy_image(game->mlx_ptr, game->pac_img_u);
	if (game->pac_img_d)
		mlx_destroy_image(game->mlx_ptr, game->pac_img_d);
	if (game->pac_img_l)
		mlx_destroy_image(game->mlx_ptr, game->pac_img_l);
	if (game->pac_img_r)
		mlx_destroy_image(game->mlx_ptr, game->pac_img_r);
	if (game->collec_img)
		mlx_destroy_image(game->mlx_ptr, game->collec_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx_ptr, game->exit_img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game->map)
		free_map(game->map);
}

void	end_game(char *msg, t_game *game, enum e_state state, char *free_me)
{
	if (state == event_end)
	{
		ft_printf("%s\n", msg);
		destroy_the(game);
		exit(0);
	}
	else if (state == file_error)
	{
		ft_printf("Error\n__FILE_ERROR__ : %s\n", msg);
		if (free_me != NULL)
			free(free_me);
		exit(1);
	}
	else if (state == map_error)
	{
		ft_printf("Error\n__MAP_ERROR__ : %s\n", msg);
		free_map(game->map);
		if (free_me != NULL)
			free(free_me);
		exit(2);
	}
	ft_printf("Error\n%s\n", msg);
	destroy_the(game);
	exit(3);
}

static void	init_vars(t_game *game)
{
	game->map_size.x = ft_strlen(game->map[0]);
	game->map_size.y = get_height(game->map);
	game->nb_c = 0;
	game->moves = 0;
}

int	key_check(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->p_pos.x;
	y = game->p_pos.y;
	if (keycode == XK_Escape)
		end_game("", game, event_end, NULL);
	else if (keycode == XK_a && !is_wall(game, y, x - 1))
		move_to(x - 1, y, game->pac_img_l, game);
	else if (keycode == XK_d && !is_wall(game, y, x + 1))
		move_to(x + 1, y, game->pac_img_r, game);
	else if (keycode == XK_w && !is_wall(game, y - 1, x))
		move_to(x, y - 1, game->pac_img_u, game);
	else if (keycode == XK_s && !is_wall(game, y + 1, x))
		move_to(x, y + 1, game->pac_img_d, game);
	return (0);
}

void	init_game(t_game *game, char *map_file)
{
	int	x;
	int	y;
	int	err;

	(void)map_file;
	err = 0;
	game->map = get_map(map_file, game, err);
	if (game->map == NULL)
		end_game(ERRSAVE, game, file_error, NULL);
	init_vars(game);
	check_map_valid(game, map_file, err);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		end_game(ERRMLX, game, map_error, NULL);
	y = game->map_size.y;
	x = game->map_size.x;
	game->mlx_win = mlx_new_window(game->mlx_ptr, x * 50, y * 50, "GAME");
	if (!game->mlx_win)
		end_game(ERRWIN, game, map_error, game->mlx_ptr);
	render_map(game);
	mlx_hook(game->mlx_win, KEY_RELEASED, KEY_MASK, key_check, game);
	mlx_hook(game->mlx_win, ON_DESTROY, EXIT_MASK, exit_event, game);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 10, 0xff0000, "Move: 0");
	mlx_loop(game->mlx_ptr);
	return ;
}

void	join_me(char **lines, char **curr, t_game *game)
{
	char	*tmp;

	tmp = *lines;
	*lines = ft_strjoin(*lines, *curr);
	free(tmp);
	free(*curr);
	if (!(*lines))
		end_game(ERRSAVE, game, file_error, NULL);
}

void	pass_empty_lines(char **lines, int *fd, t_game *game, int *err)
{
	*lines = get_next_line(*fd, err);
	if (!(*lines))
		end_game(ERRFILE1, game, file_error, NULL);
	while (*lines && *lines[0] == '\n')
	{
		free(*lines);
		*lines = get_next_line(*fd, err);
	}
	return ;
}

char	**get_map(char *map_file, t_game *game, int err)
{
	char	*curr;
	char	*lines;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		end_game(ERROPEN, game, file_error, NULL);
	pass_empty_lines(&lines, &fd, game, &err);
	curr = get_next_line(fd, &err);
	if (!curr)
		free(lines);
	while (curr)
	{
		if (curr[0] == '\n')
		{
			free(curr);
			break ;
		}
		join_me(&lines, &curr, game);
		curr = get_next_line(fd, &err);
		if (err == 1)
			end_game(ERRSAVE, game, file_error, NULL);
	}
	close (fd);
	return (ft_split(lines, '\n'));
}


void	img_on_map(char p, int x, int y, t_game *g)
{
	if (!g->mlx_ptr || !g->mlx_win)
	{
		ft_printf(ERRPOINTER);
		return ;
	}
	if (p == '1')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->wall_img, x, y);
	else if (p == 'C')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->collec_img, x, y);
	else if (p == 'E')
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->exit_img, x, y);
	else if (p == 'P')
	{
		g->y_p = y;
		g->x_p = x;
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->pac_img_d, x, y);
	}
	else
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, g->bg_img, x, y);
}

void	init_img(t_game *game)
{
	game->wall_img = save_that_img("./assets/wall.xpm", game);
	game->pac_img_d = save_that_img("./assets/pac_img_d.xpm", game);
	game->pac_img_u = save_that_img("./assets/pac_img_u.xpm", game);
	game->pac_img_l = save_that_img("./assets/pac_img_l.xpm", game);
	game->pac_img_r = save_that_img("./assets/pac_img_r.xpm", game);
	game->exit_img = save_that_img("./assets/exit.xpm", game);
	game->collec_img = save_that_img("./assets/collec.xpm", game);
	game->bg_img = save_that_img("./assets/ground.xpm", game);
	if (!game->wall_img || !game->pac_img_d || !game->pac_img_d || !game->pac_img_r || !game->pac_img_u || !game->exit_img || !game->collec_img || !game->bg_img)
		end_game("__ASSET_ERROR__ : Error while retrieving assets", game, asset_error, NULL);

}

void	update_values(int *map_x, int *x, int *map_size_x)
{
	(*map_x)++;
	*x += 50;
	(*map_size_x)--;
}

void	render_map(t_game *game)
{
	int	y;
	int	x;
	int	map_y;
	int	map_x;
	int	tmp_w;

	y = 0;
	map_y = 0;
	tmp_w = game->map_size.x;
	init_img(game);
	while (game->map_size.y > 0)
	{
		x = 0;
		map_x = 0;
		while (game->map_size.x > 0)
		{
			img_on_map(game->map[map_y][map_x], x, y, game);
			update_values(&map_x, &x, &game->map_size.x);
		}
		game->map_size.x = tmp_w;
		map_y++;
		y += 50;
		game->map_size.y--;
	}
}


void	put_that_img(void *img, int x, int y, t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, img, x * 50, y * 50);
}

int	is_wall(t_game *game, int y, int x)
{
	return (game->map[y][x] == '1');
}

void	*save_that_img(char *img_path, t_game *game)
{
	int	img_x;
	int	img_y;

	img_x = game->img_size.x;
	img_y = game->img_size.y;
	return (mlx_xpm_file_to_image(game->mlx_ptr, img_path, &img_x, &img_y));
}

void	move_to(int x, int y, void *dir, t_game *game)
{
	if (game->map[y][x] == 'E' && game->nb_c != 0)
		return ;
	put_that_img(game->bg_img, game->p_pos.x, game->p_pos.y, game);
	game->map[game->p_pos.y][game->p_pos.x] = '0';
	game->p_pos.y = y;
	game->p_pos.x = x;
	if (game->map[y][x] == 'C')
		game->nb_c--;
	put_that_img(dir, game->p_pos.x, game->p_pos.y, game);
	game->moves++;
	put_text(game);
	if (game->map[y][x] == 'E' && game->nb_c == 0)
		end_game(WINNER, game, event_end, NULL);
	game->map[y][x] = 'P';
}
char	*ft_join_strings(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	unsigned int	i;
	char			*ptr;

	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1_len-- != 0)
		ptr[i++] = *s1++;
	while (s2_len-- != 0)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

void	put_text(t_game *game)
{
	char	*text;
	char	*number;

	number = ft_itoa(game->moves);
	text = ft_join_strings("Move: ", number);
	put_that_img(game->wall_img, 0, 0, game);
	put_that_img(game->wall_img, 1, 0, game);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 10, 0xff0000, text);
	ft_printf("moves : %d\n", game->moves);
	free(text);
	free(number);
}
static int	is_ber_file(const char *av)
{
	char	*string;

	string = ft_strrchr(av, '.');
	if (string)
		return (ft_strcmp(string, ".ber") == 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2 && (is_ber_file(av[1])))
		init_game(&game, av[1]);
	else if (ac == 2 && !(is_ber_file(av[1])))
		end_game(ERRBER, &game, file_error, NULL);
	else if (ac > 2)
		end_game(ERRARG, &game, file_error, NULL);
	else if (ac < 2)
		end_game(ERRARG0, &game, file_error, NULL);
	else
		end_game(ERRFILE, &game, file_error, NULL);
	return (0);
}
