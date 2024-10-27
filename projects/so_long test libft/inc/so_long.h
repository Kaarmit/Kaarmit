/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:33:10 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/29 18:39:36 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../minilibx/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// EVENTS
# define ON_DESTROY 17
# define KEY_PRESSED 2
# define KEY_RELEASED 3
# define EXIT_MASK 0
# define KEY_MASK 2

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
	void		*pac_img;
	void		*main_img_u;
	void		*main_img_d;
	void		*main_img_l;
	void		*main_img_r;
	void		*enemy_B_img;
	void		*enemy_G_img;
	void		*enemy_R_img;
	void		*enemy_P_img;
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
	int			b;
	int			r;
	int			g;
	int			v;
	int			x;
	int			y;
}				t_game_map;

enum			e_state
{
	event_end = -1,
	map_error = 2,
	file_error = 3,
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
