/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:03:15 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/02 11:24:30 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	t_dda coords;
	coords = dda_coor(vars->raycount, 0, vars->raycount, vars->parser.height / 2 - vars->walls.height);
	//dda_algorithm(&vars->data, vars->raycount, 0, vars->raycount, vars->parser.height / 2 - vars->walls.height, vars->sky);
	dda_algorithm(&vars->data, coords, (unsigned int)vars->sky);
	drawtexture(vars, vars->raycount);
	//drawtexture(vars, vars->raycount);
	coords = dda_coor(vars->raycount, vars->parser.height / 2 + vars->walls.height, vars->raycount, vars->parser.height);
	//dda_algorithm(&vars->data, vars->raycount, vars->parser.height / 2 + vars->walls.height, vars->raycount, vars->parser.height, vars->floor);
	dda_algorithm(&vars->data, coords, vars->floor);
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

int		raycasting(t_vars *vars)
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
