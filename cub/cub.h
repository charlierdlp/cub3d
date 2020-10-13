/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:47:46 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/13 13:47:50 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./minilibx/mlx.h"
# define WIDTH 15
# define HEIGHT 10
# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH 600
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

typedef struct	s_keys {
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

typedef struct	s_img {
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
	float		height;
}				t_walls;

typedef struct	s_textdata {
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
	int			leftangle;
	int			rightangle;
	int			relative;
	int			height;
	int			width;
	int			drawheight;
	int			drawwidth;
	int			pixels_per_degree;
	int			distance;
	float		x;
	float		y;
	t_textdata	texture;
}				t_sprite;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	float		x;
	float		y;
	int			raycount;
	int			dir;
	float		ray;
	t_player	player;
	t_walls		walls;
	t_img		data;
	t_textdata	texture;
	t_textdata	north;
	t_textdata	south;
	t_textdata	west;
	t_textdata	east;
	t_sprite	sprite;
	t_keys		keys;
}				t_vars;

extern int map[HEIGHT][WIDTH];
extern int bitmap[8][8];

void	ch_mlx_pixel_put(t_img *data, int x, int y, int color);
void	dda_algorithm(t_img *data, int x0, int y0, int x1, int y1, int color);
int		raycasting(t_vars *vars);
int		move(t_vars *vars);
int		drawtexture(t_vars *vars, int x);
int		textures(t_vars *vars, char *path, t_textdata *texture);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);

#endif
