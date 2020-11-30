/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:03:15 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/30 12:42:51 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ch_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height) //screem height screen width
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	dda_algorithm(t_img *data, int x0, int y0, int x1, int y1, int color)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		steps;
	float	xinc;
	float	yinc;
	int		i;

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
		if (vars->map.map[(int)vars->y][(int)vars->x] == '1')
		{
			vars->dir = vars->rays.raycos < 0 ? 'W' : 'E';
			if (vars->dir == 'W')
				vars->texture = vars->west;
			else
				vars->texture = vars->east;
			vars->walls.wall = vars->map.map[(int)vars->y][(int)vars->x];
			break ;
		}
		vars->y += vars->rays.raysin;
		if (vars->map.map[(int)vars->y][(int)vars->x] == '1')
		{
			vars->dir = vars->rays.raysin < 0 ? 'N' : 'S';
			if (vars->dir == 'N')
				vars->texture = vars->north;
			else
				vars->texture = vars->south;
			vars->walls.wall = vars->map.map[(int)vars->y][(int)vars->x];
		}
	}
}

void	wall_dist_height(t_vars *vars)
{
	wall_check(vars);
	vars->walls.distance = sqrt(pow(vars->player.x - vars->x, 2) + pow(vars->player.y - vars->y, 2));
	vars->walls.dist[vars->raycount] = vars->walls.distance;
	vars->walls.distance = vars->walls.distance * cos((vars->rays.rayangle - vars->player.angle) * M_PI / 180);
	vars->walls.height = (int)((vars->parser.height / 2) / vars->walls.distance);
	vars->texture.texturepositionx = floor(fmod(vars->texture.width * (vars->x + vars->y), vars->texture.width));
}

void	paint(t_vars *vars)
{
	dda_algorithm(&vars->data, vars->raycount, 0, vars->raycount, vars->parser.height / 2 - vars->walls.height, vars->sky);
	drawtexture(vars, vars->raycount);
	dda_algorithm(&vars->data, vars->raycount, vars->parser.height / 2 + vars->walls.height, vars->raycount, vars->parser.height, vars->floor);
}

void	init_sprites(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->snumber)
	{
		calc_angles(vars, &vars->sprite[i]);
		i++;
	}
	sort_sarray(vars);
	i = 0;
	while (i < vars->snumber)
	{
		draw_sprites(vars, &vars->sprite[i]);
		i++;
	}
}

int	raycasting(t_vars *vars)
{
	vars->rays.rayangle = vars->player.angle - vars->player.fov / 2;
	vars->raycount = 0;
	move(vars);
	while (vars->raycount < vars->parser.width)
	{
		vars->x = vars->player.x;
		vars->y = vars->player.y;
		vars->rays.raycos = cos(vars->rays.rayangle * M_PI / 180) / 128;
		vars->rays.raysin = sin(vars->rays.rayangle * M_PI / 180) / 128;
		wall_dist_height(vars);
		paint(vars);
		vars->rays.rayangle += vars->player.fov / vars->parser.width;
		vars->raycount += 1;
	}
	init_sprites(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	return (0);
}
