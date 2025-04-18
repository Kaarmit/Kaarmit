/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:36:10 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/13 14:26:08 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
