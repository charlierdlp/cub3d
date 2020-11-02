/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:03:15 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/02 13:44:50 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ch_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	//recorrer el string de datos en forma de array
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	dda_algorithm(t_img *data, int x0, int y0, int x1, int y1, int color)
{
	int x;
	int y;
	int dx;
	int dy;
	int steps;
	float xinc;
	float yinc;
	int i;

	i = 0;
	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;
	x = x0;
	y = y0;
	while (i <= steps)
	{
		ch_mlx_pixel_put(data, x, y, color);
		x += xinc;
		y += yinc;
		i++;
	}
}

void	wall_check(t_vars *vars)
{
	vars->walls.wall = 0;
	while (vars->walls.wall == 0)
	{
		vars->x += vars->rays.raycos;
		if (map[(int)vars->y][(int)vars->x] == 1)
		{
			vars->dir = vars->rays.raycos < 0 ? 'W' : 'E';
			if (vars->dir == 'W')
				vars->texture = vars->west;
			else
				vars->texture = vars->east;
			break ;
		}
			vars->y += vars->rays.raysin;
			if (map[(int)vars->y][(int)vars->x] == 1)
			{
				vars->dir = vars->rays.raysin < 0 ? 'N' : 'S';
				if (vars->dir == 'N')
					vars->texture = vars->north;
				else
					vars->texture = vars->south;
			}
			vars->walls.wall = map[(int)vars->y][(int)vars->x];
		}
}

void	wall_dist_height(t_vars *vars)
{
	wall_check(vars);
	vars->walls.distance = sqrt(pow(vars->player.x - vars->x, 2) + pow(vars->player.y - vars->y, 2));
	vars->walls.dist[vars->raycount] = vars->walls.distance;
	vars->walls.distance = vars->walls.distance * cos((vars->rays.rayangle - vars->player.angle) * M_PI / 180);
	vars->walls.height = (int)((SCREEN_HEIGHT/2) / vars->walls.distance);
	vars->texture.texturepositionx = floor(fmod(vars->texture.width * (vars->x + vars->y), vars->texture.width));
			
}

void 	paint(t_vars *vars)
{
	dda_algorithm(&vars->data, vars->raycount, 0, vars->raycount, SCREEN_HEIGHT / 2 - vars->walls.height, 0x00A1DD);
	drawtexture(vars, vars->raycount);
	dda_algorithm(&vars->data, vars->raycount, SCREEN_HEIGHT / 2 + vars->walls.height, vars->raycount, SCREEN_HEIGHT, 0xA0A0A0);
}

int	raycasting(t_vars *vars)
{
	vars->rays.rayangle = vars->player.angle - vars->player.fov/2;
	vars->raycount = 0;
	move(vars);
	while (vars->raycount < SCREEN_WIDTH)
	{
		vars->x = vars->player.x;
		vars->y = vars->player.y;

		//degreetoradians = * M_PI / 180;
		vars->rays.raycos = cos(vars->rays.rayangle * M_PI / 180) / 128;
		vars->rays.raysin = sin(vars->rays.rayangle * M_PI / 180) / 128;

		wall_dist_height(vars);
		paint(vars);
		vars->rays.rayangle += vars->player.fov/SCREEN_WIDTH;
		vars->raycount += 1;
	}
	calc_angles(vars);
	draw_sprites(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	return (0);
}

