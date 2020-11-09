/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:47:46 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/09 13:50:48 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./minilibx/mlx.h"
# include <signal.h>
# include "pthread.h"
# define WIDTH 15
# define HEIGHT 15
# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH 600
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define SPEED 0.1

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct	s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			w;
	int			a;
	int			d;
	int			s;
}				t_keys;

typedef struct	s_player
{
	float		x;
	float		y;
	float		fov;
	float		angle;
	float		cos;
	float		sin;
	float		speed;
	float		rotation;
}				t_player;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_walls
{
	int			wall;
	float		distance;
	float		*dist;
	float		height;
}				t_walls;

typedef struct	s_textdata
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			texture;
	int			texturepositionx;
	int			color;
}				t_textdata;

typedef struct	s_sprite
{
	float		leftangle;
	float		rightangle;
	float		relative;
	float		angle;
	float		drawheight;
	float		drawwidth;
	float		distance;
	float		position;
	float		pixels_per_degree;
	float		x;
	float		y;
	t_textdata	texture;
}				t_sprite;

typedef struct	s_rays 
{
	float 		raycos;
	float		raysin;
	float		rayangle;
}				t_rays;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	float		x;
	float		y;
	float		ray;
	int			raycount;
	int			dir;
	int			snumber;
    int			pid; 
	t_map		map;
	t_player	player;
	t_walls		walls;
	t_img		data;
	t_textdata	texture;
	t_textdata	north;
	t_textdata	south;
	t_textdata	west;
	t_textdata	east;
	t_textdata	stexture;
	t_sprite	*sprite;
	t_keys		keys;
	t_rays		rays;
}				t_vars;

extern int map[HEIGHT][WIDTH];

void	ch_mlx_pixel_put(t_img *data, int x, int y, int color);
void	dda_algorithm(t_img *data, int x0, int y0, int x1, int y1, int color);
int		raycasting(t_vars *vars);
int		move(t_vars *vars);
int		drawtexture(t_vars *vars, int x);
int		textures(t_vars *vars, char *path, t_textdata *texture);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
int		x_close(t_vars *vars);
int		calc_angles(t_vars *vars, t_sprite *sprite);
void 	square(t_vars *vars, t_sprite *sprite, int x1, int y1, int x2, int y2);
int		draw_sprites(t_vars *vars, t_sprite *sprite);
void	find_sprites(t_vars *vars);
int 	sprite_array(t_vars *vars);
void	sort_sarray(t_vars *vars);


#endif
