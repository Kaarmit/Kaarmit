/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:33:00 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/11 19:10:03 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define WIDTH 1280
# define HEIGHT 720
# define TILE 20
# define NB_TXTR 4
# define TXTR_NO 0
# define TXTR_SO 1
# define TXTR_WE 2
# define TXTR_EA 3

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <X11/keysym.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct s_play
{
	char	orientation;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_play;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_twod
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_twod;

typedef struct s_txtr
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_txtr;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		that_one;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		d;
	int		color;
}	t_ray;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**grid;
	char	*nopath;
	char	*sopath;
	char	*wepath;
	char	*eapath;
	char	*trim;
	int		fcolor;
	int		ccolor;
	int		errcolor;
	int		doublepath;
	int		map_height;
	int		map_width;
	t_txtr	texture[NB_TXTR];
	t_twod	m;
	t_keys	keys;
	t_play	p;
	t_ray	r;
}		t_game;

/*Fonctions parsing*/

void	map_parse(char *map, t_game *game, int argc);
void	init_value(t_game *game);
void	init_player(t_play *p, char dir);
void	get_player_pos(t_game *game, int i, int j);
void	split_check(char **split, t_game *game);
void	line_check(char *line, t_game *game);
void	height_value(t_game *game);
int		name_check(char *name);
int		name_check_texture(char *name);
int		each_line_check(char *getmap);
int		path_check(t_game *game);
int		color_check(char **split, int *r, int *g, int *b);
char	*get_map(char *map, t_game *game, char *temp);

/*Creation fenetre*/
void	start_mlx(t_game *game);

/* Game */
int		game_loop(t_game *game);

/*Minimap / 2D*/

int		minimap(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);

/*Raycasting*/

void	background(t_game *game);
void	raycasting(t_game *g);
void	render_texture(t_game *g, int x);

/*Mouvements*/

int		handle_keys(t_game *g);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_forward_bonus(t_play *p, char **map);
void	move_backward_bonus(t_play *p, char **map);
void	move_right_bonus(t_play *p, char **map);
void	move_left_bonus(t_play *p, char **map);

/*Fonctions erreur*/

void	error_game(char *message, t_game *game);
void	freegrid(char **grid);
void	game_over(t_game *game, int danger);
int		end(t_game *game);
void	destroy_all(t_game *game);

#endif
